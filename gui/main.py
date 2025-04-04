import tkinter as tk
import WikiChecks

def r():
    root = tk.Tk()
    root.geometry("800x500")
    root.title("Wikipedia Speedrun Bot")
    label = tk.Label(root,text="Wikipedia Speedrun Bot",font=('Ariel',18))
    label.pack(padx=20,pady=20)
    start_page_entry = tk.Entry(root)
    start_page_entry.pack()
    end_page_entry = tk.Entry(root)
    end_page_entry.pack()
    button = tk.Button(root,text="Run!",font=('Ariel',18))
    button.pack(padx=10,pady=10)
    root.mainloop()

def checkInput() -> bool:
    return True

def main():
    r()

main()