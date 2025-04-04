import tkinter as tk
from tkinter import messagebox
import ctypes
import WikiChecks
import webbrowser
from tkinter import PhotoImage

class MainManu:
    def __init__(self):
        self.root = tk.Tk()
        self.root.geometry("800x500")
        self.root.title("Wikipedia Speedrun Bot")
        self.root.configure(background="Dark Cyan")
        
        # Make UI responsive
        self.root.bind("<Configure>", self.resize_widgets)
        
        myappid = 'tkinter.python.test'
        ctypes.windll.shell32.SetCurrentProcessExplicitAppUserModelID(myappid)
        self.root.wm_iconbitmap('./Images/Icon1.ico')
        
        # Title Label
        self.title_label = tk.Label(self.root, text="Wikipedia Speedrun Bot", font=('Impact', 32), background="Dark Cyan")
        self.title_label.place(relx=0.5, rely=0.1, anchor='center')
        
        # Frame for input fields
        self.input_frame = tk.Frame(self.root, background="Dark Cyan")
        self.input_frame.place(relx=0.5, rely=0.3, anchor='center')
        
        self.start_page_entry = tk.Entry(self.input_frame, font=('Arial', 14))
        self.to_label = tk.Label(self.input_frame, text="to", font=('Arial', 16), background="Dark Cyan")
        self.end_page_entry = tk.Entry(self.input_frame, font=('Arial', 14))
        
        self.start_page_entry.pack(side=tk.LEFT, padx=10, ipadx=10, ipady=5)
        self.to_label.pack(side=tk.LEFT, padx=10)
        self.end_page_entry.pack(side=tk.LEFT, padx=10, ipadx=10, ipady=5)
        
        # Run Button
        self.run_button = tk.Button(self.root, text="Run!", font=('Arial', 18, 'bold'), command=self.runProgram)
        self.run_button.place(relx=0.5, rely=0.45, anchor='center')
        
        # GitHub Button (Top-right corner)
        github_image = PhotoImage(file='./Images/github2.png')
        self.github_button = tk.Button(self.root, image=github_image, command=self.redirect, borderwidth=0)
        self.github_button.image = github_image  # Keep reference
        self.github_button.place(relx=0.95, rely=0.05, anchor='ne')
        
        self.root.mainloop()
    def runProgram(self):
        start_page = self.start_page_entry.get()
        end_page = self.end_page_entry.get()
        if WikiChecks.pageValid(start_page) and WikiChecks.pageValid(end_page):
            ResultPage(start_page,end_page)
        else:
            messagebox.showinfo(title="Error",message=f"one of the pages is not valid, Please check again")
    def redirect(self):
        url = 'https://github.com/LironVaisman9/WikipediaSpeedrunBot?tab=readme-ov-file'
        webbrowser.open(url)
    def resize_widgets(self, event):
        """ Adjust widget sizes based on window size """
        width, height = event.width, event.height
        font_size = max(16, int(width / 50))
        self.title_label.config(font=('Impact', font_size))
        self.run_button.config(font=('Arial', max(14, font_size - 8)))
        self.to_label.config(font=('Arial', max(12, font_size - 10)))
        self.start_page_entry.config(font=('Arial', max(12, font_size - 10)))
        self.end_page_entry.config(font=('Arial', max(12, font_size - 10)))
        
        # Resize GitHub button
        new_size = max(30, width // 30)
        resized_image = self.github_button.image.subsample(2)  # Adjust scaling
        self.github_button.config(image=resized_image)
        self.github_button.image = resized_image  # Keep reference
class ResultPage:
    def __init__(self,start_page: str,end_page: str):
        self.start_page = start_page
        self.end_page = end_page

        self.root = tk.Tk()
        self.root.geometry("800x500")
        self.root.title("Wikipedia Speedrun Bot")
        self.root.mainloop()