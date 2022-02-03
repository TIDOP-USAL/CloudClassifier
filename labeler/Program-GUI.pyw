from Labeler import Labeler

import tkinter as tk
from tkinter import ttk
from tkinter.filedialog import askopenfilename
from tkinter import colorchooser
from tkinter import messagebox

from threading import Thread

TITLE = 'Labeler'
LABEL_DEFAULT = 'label'

class Application(ttk.Frame):

    global TITLE
    global LABEL_DEFAULT
    
    def __init__(self, mainWindow):
        super().__init__(mainWindow)
        mainWindow.title(TITLE)
        # Vars
        self.filePath = ''
        self.red = '0'
        self.green = '0'
        self.blue = '0'
        # Components
        self.__initComponents()
        self.__placeComponents()

    def __initComponents(self):
        self.entryFile = ttk.Entry(self, state='disabled')
        self.buttonSearch = ttk.Button(self, text='Search', command=self.__searchFile)

        self.labelName = ttk.Label(self, text='Property name:')
        self.entryName = ttk.Entry(self)
        self.entryName.insert(0, LABEL_DEFAULT)

        self.labelType = ttk.Label(self, text='Type:')
        self.combo = ttk.Combobox(self)
        self.combo["values"] = ["int", "float"]
        self.combo.set("int")

        self.labelColor = ttk.Label(self, text='Unclassified color:')
        self.buttonColor = ttk.Button(self, text="Select", command=self.__getUnclassifiedColor)
        
        self.buttonProgram = ttk.Button(self, text="Run", command=self.__runProgram)
        
        self.progressbar = ttk.Progressbar(self, mode="indeterminate")

    def __placeComponents(self):
        self.buttonSearch.place(x = 20, y = 25)
        self.entryFile.place(x = 130, y = 25, width = 200)

        self.labelName.place(x = 20, y = 60)
        self.entryName.place(x = 130, y = 60, width = 200)

        self.labelType.place(x = 20, y = 95)
        self.combo.place(x = 130, y = 95, width = 200)

        self.labelColor.place(x = 20, y = 130)
        self.buttonColor.place(x = 130, y = 130, width = 200)

        self.buttonProgram.place(x = 20, y = 165, width = 310)

        self.place(width=350, height=235)
        mainWindow.geometry("350x235")
        
    def __searchFile(self):
        self.entryFile.configure(state='normal')
        self.filePath = askopenfilename()
        self.entryFile.delete(0, 'end')
        self.entryFile.insert(0, self.filePath)
        self.entryFile.configure(state='disabled')

    def __getUnclassifiedColor(self):
        color = colorchooser.askcolor()
        self.red = str(color[0][0])
        self.green = str(color[0][1])
        self.blue = str(color[0][2])
        colorHex = color[1]
        self.labelColor.configure(foreground=colorHex)

    def __runProgram(self):
        if(self.filePath == '' or self.filePath == ""):
            raise IOError
        self.progressbar.place(x = 20, y = 200, width = 310)
        self.progressbar.start()
        Thread(target=self.__runLabeler).start()

    def __runLabeler(self):
        # Get vars
        propertyType = self.combo.get()
        label = self.entryName.get()
        # Labeler
        labeler = Labeler(self.filePath, propertyType, label)
        labeler.setUnclassified(self.red, self.green, self.blue)
        labeler.save()
        # Stop progress bar
        self.progressbar.stop()
        #Show message
        messagebox.showinfo(message="Saved successfuly", title="Saved")

mainWindow = tk.Tk()
mainWindow.resizable(False, False)
app = Application(mainWindow)
app.mainloop()