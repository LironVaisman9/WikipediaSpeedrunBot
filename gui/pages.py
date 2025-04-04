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
        myappid = 'tkinter.python.test'
        ctypes.windll.shell32.SetCurrentProcessExplicitAppUserModelID(myappid)
        self.root.title("Wikipedia Speedrun Bot")
        self.root.wm_iconbitmap('./Images/Icon1.ico')
        self.root.configure(background="Dark Cyan")

        
        top_frame = tk.Frame(self.root, background="Dark Cyan")
        top_frame.grid(row=0, column=0, sticky="ew", padx=20, pady=20)

        
        top_frame.grid_columnconfigure(0, weight=1)  
        top_frame.grid_columnconfigure(1, weight=1)  
        top_frame.grid_columnconfigure(2, weight=0)  
        
        self.title_label = tk.Label(top_frame, text="Wikipedia Speedrun Bot", font=('Ariel', 18), background="Dark Cyan")
        self.title_label.grid(row=0, column=1)  

        
        original_image = PhotoImage(file='./Images/github2.png')
        resized_image = original_image.subsample(10, 10) 

       
        self.github_button = tk.Button(top_frame, image=resized_image, command=self.redirect, borderwidth=0)
        self.github_button.image = resized_image 
        self.github_button.grid(row=0, column=2, padx=10)  

       
        page_frame = tk.Frame(self.root, background="Dark Cyan")
        page_frame.grid(row=1, column=0, pady=10)  

        self.start_page_entry = tk.Entry(page_frame)
        self.start_page_entry.grid(row=0, column=0, padx=5)

        self.to_label = tk.Label(page_frame, text="to", font=('Ariel', 18), background="Dark Cyan")
        self.to_label.grid(row=0, column=1, padx=5)

        self.end_page_entry = tk.Entry(page_frame)
        self.end_page_entry.grid(row=0, column=2, padx=5)

        self.run_button = tk.Button(self.root, text="Run!", font=('Ariel', 18), command=self.runProgram)
        self.run_button.grid(row=2, column=0, padx=10, pady=10)  

        self.root.mainloop()

    def runProgram(self):
        start_page = self.start_page_entry.get()
        end_page = self.end_page_entry.get()
        if WikiChecks.pageValid(start_page) and WikiChecks.pageValid(end_page):
            ResultPage(start_page, end_page)
        else:
            messagebox.showinfo(title="Error", message="One of the pages is not valid, please check again.")
    
    def redirect(self):
        url = 'https://github.com/LironVaisman9/WikipediaSpeedrunBot?tab=readme-ov-file'
        webbrowser.open(url)

class ResultPage:
    def __init__(self, start_page: str, end_page: str):
        self.start_page = start_page
        self.end_page = end_page

        self.root = tk.Tk()
        self.root.geometry("800x500")
        self.root.title("Wikipedia Speedrun Bot")
        self.root.mainloop()

MainManu()
