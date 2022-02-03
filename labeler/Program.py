from Labeler import Labeler

filePath = input('File path (.ply): ')
propertyType = input('Property type: ')
label = input('Label name: ')

print('Set unclassified color: ')
red = input('Red: ')
green = input('Green: ')
blue = input('Blue: ')

labeler = Labeler(filePath, propertyType, label)
labeler.setUnclassified(red, green, blue)
labeler.save()