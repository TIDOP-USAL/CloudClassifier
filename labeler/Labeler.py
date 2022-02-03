FORMAT_ASCII = 'format ascii'
FORMAT_BINARY = 'format binary'
PROPERTY = 'property'
PROPERTY_RED = 'property uchar red'
END_HEADER = 'end_header'
DELIMITER = str(chr(0x20))

class Labeler():

    global FORMAT_BINARY
    global FORMAT_ASCII
    global PROPERTY
    global PROPERTY_RED
    global END_HEADER
    global DELIMITER

    def __init__(self, filePath, propertyType, label):
        # Init vars
        self.filePath = filePath
        self.propertyType = propertyType
        self.label = label

        if(filePath == "" or filePath == ''):
            raise IOError
        
        # Point cloud
        self.lines = []
        self.header = []
        self.points = []
        self.binary = False

        # Properties
        self.propertyCount = 0
        self.redIndex = 0

        # Labels
        self.colorLines = []
        self.labels = {}
        self.labelIndex = 0
        self.unclassifiedColor = ''

        # Load file
        self.file = open(filePath, 'r')
        self.__checkBinary()
        self.__readLines()
        self.file.close()

    def __checkBinary(self):
        found = False
        while(not found):
            line = self.file.readline()
            if(line.startswith(FORMAT_BINARY)):
                self.binary = True
                found = True
            elif(line.startswith(FORMAT_ASCII)):
                found = True
            self.lines.append(line)

    def __readLinesASCII(self):
        self.lines += self.file.readlines()

    def __readLinesBinary(self):
        pass

    def __readLines(self):
        if(not self.binary):
            self.__readLinesASCII()
        else:
            self.__readLinesBinary()

    def __initBuffersASCII(self):
        header = True
        for line in self.lines:
            if(header):
                self.header.append(line)
                if(line.startswith(END_HEADER)):
                    header = False
                elif(line.startswith(PROPERTY) and not line.startswith(PROPERTY_RED)):
                    self.propertyCount += 1
                elif(line.startswith(PROPERTY_RED)):
                    self.redIndex = self.propertyCount
                    self.propertyCount += 1
            else:
                self.points.append(line)

    def __initBuffersBinary(self):
        pass

    def __initBuffers(self):
        if(not self.binary):
            self.__initBuffersASCII()
        else:
            self.__initBuffersBinary()

    def __exists(self, colorLine):
        for color in self.colorLines:
            if(colorLine == color):
                return True
        return False

    def __substr(self, line, beginIndex, endIndex):
        newLine = ''
        for i in range(beginIndex, endIndex):
            newLine += line[i]
        return newLine

    def __generateLabelsASCII(self):
        for pointLine in self.points:
            pointLineSplitted = pointLine.split(DELIMITER)
            red = pointLineSplitted[self.redIndex]
            green = pointLineSplitted[self.redIndex + 1]
            blue = pointLineSplitted[self.redIndex + 2]
            colorLine = red + DELIMITER + green + DELIMITER + blue
            if(not self.__exists(colorLine) and colorLine != self.unclassifiedColor):
                self.colorLines.append(colorLine)
                self.labels[colorLine] = self.labelIndex
                self.labelIndex += 1

    def __generateLabelsBinary(self):
        pass

    def __generateLabels(self):
        self.__initBuffers()
        if(not self.binary):
            self.__generateLabelsASCII()
        else:
            self.__generateLabelsBinary()

    def __createLineASCII(self, line, type, index):
        # Clean line
        newLine = ''
        for c in line:
            if(c != '\n'):
                newLine += c
        # Return line with the property
        if(type == 'int'):
            return newLine + str(int(index))
        elif(type == 'float'):
            return newLine + str(float(index))
        return ''

    def __writeHeaderASCII(self, file):
        for i in range(0, len(self.header) - 1):
            line = self.header[i]
            if(self.header[i].startswith(END_HEADER)):
                continue
            file.write(line)
        labelProperty = PROPERTY + DELIMITER + self.propertyType + DELIMITER + self.label + '\n'
        file.write(labelProperty)
        file.write(END_HEADER + '\n')

    def __writePointsASCII(self, file):
        pointIndex = 0
        progress = 0
        for pointLine in self.points:
            newLine = self.__createLineASCII(pointLine, self.propertyType, -1)
            unclassifiedDeclaration = DELIMITER + self.unclassifiedColor + DELIMITER
            for colorKey in self.labels:
                colorDeclaration = DELIMITER + colorKey + DELIMITER
                if(pointLine.find(unclassifiedDeclaration) != -1 and self.unclassifiedColor != ''):
                    pass
                elif(pointLine.find(colorDeclaration) != -1):
                    newLine = self.__createLineASCII(pointLine, self.propertyType, self.labels.get(colorKey))
                    break
            file.write(newLine + '\n')
            pointIndex += 1
            # Show progress
            temp = progress
            progress = int(float(pointIndex) / float(len(self.points)) * 100)
            if(progress != temp):
                print('Completed:', progress, '%')

    def __writeASCII(self, path):
        file = open(path, 'w')
        self.__writeHeaderASCII(file)
        self.__writePointsASCII(file)
        file.close()

    def __writeBinary(path):
        pass

    def __getNewPath(self):
        path = ''
        filePathSplitted = self.filePath.split('/')
        for i in range(0, len(filePathSplitted) - 1):
            path += filePathSplitted[i] + '/'
        nameSplitted = filePathSplitted[len(filePathSplitted) - 1].split('.')
        path += nameSplitted[0] + '-prop.ply'
        return path

    def setUnclassified(self, red, green, blue):
        self.unclassifiedColor = red + DELIMITER + green + DELIMITER + blue

    def save(self):
        self.__generateLabels()
        path = self.__getNewPath()
        if(not self.binary):
            self.__writeASCII(path)
        else:
            self.__writeBinary(path)