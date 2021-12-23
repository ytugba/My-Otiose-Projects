from tkinter import *
from tkinter import messagebox
import random
import time
import sys

#default colors
backgroundColor = '#141414'
numberColor = '#ffffff'
buttonColor = '#188996'
headingColor = '#969494'


#default variables
currentPattern = 3
totalInput = ''
totalScore = 0

#window customizations
root= Tk()
root.title("Memoria")
root.geometry("600x590+350+0")
root.resizable(width=False, height=False)
root.configure(background= backgroundColor, cursor = "heart")
photo = PhotoImage(file = "over.png")
root.iconbitmap('favicon.ico')

#functions
def beginning():
    begin.destroy()
    begin_button.destroy()
    exit_button.destroy()
    root.update()
    time.sleep(1)
    start2 = Label(text="Your game will start in 3 seconds.",fg=buttonColor, font=("Verdana",18), bg = backgroundColor, justify=CENTER)
    start2.pack(pady = 20)
    start2.place(x=100,y = 200)
    root.update()
    time.sleep(1)
    start2.destroy()
    start3 = Label(text="Your game will start in 2 seconds.",fg=buttonColor, font=("Verdana",18), bg = backgroundColor, justify=CENTER)
    start3.pack(pady = 20)
    start3.place(x=100,y = 200)
    root.update()
    time.sleep(1)
    start3.destroy()
    start4 = Label(text="Your game will start in 1 seconds.",fg=buttonColor, font=("Verdana",18), bg = backgroundColor, justify=CENTER)
    start4.pack(pady = 20)
    start4.place(x=100,y = 200)
    root.update()
    time.sleep(1)
    start2.destroy()
    start3.destroy()
    start4.destroy()
    game()
def game():
   
   def userAnswer():

      global totalInput
      global currentPattern

      def compare(event = None):

         global currentPattern
         global totalScore
         global totalInput

         answer = data.get().replace(" ", "")
         
         if answer == totalInput:
         
            currentPattern = currentPattern+1
            totalScore += currentPattern ** 2
            
            data.destroy()
            button.destroy()
            heading.destroy()
            totalInput=''

            game()
            
         else:
            data.destroy()
            button.destroy()
            heading.destroy()
            totalInput=''
        
            label = Label(image=photo, cursor = "heart")
            label.pack()
            
            messagebox.showerror("WRONG ANSWER", "Game Over.\nTotal Score: " + str(totalScore))
            
            root.destroy()

      #input box
      data = Entry(justify = CENTER, width = 35, font=("Verdana", 15))
      data.focus_set()
      data.pack()
      data.place(x=75, y=255)

      #button
      button = Button(text="CLICK", width = 0, bg = buttonColor, fg = 'white', font=("Verdana"), 
                      command = compare, activebackground = 'black', activeforeground = 'white', bd = 6, relief = RAISED, cursor="heart")
      root.bind('<Return>', lambda e: compare())
      button.pack()
      button.place(x=270,y=325)
 
   global totalInput
   global totalScore
   global currentPattern

        #level definition
   heading = Label(text="LEVEL "+ str(currentPattern-2), 
                   fg=headingColor, font=("Verdana",30), bg = backgroundColor, height = 2 , cursor = "heart")
   heading.pack(pady = 20)

   for i in range(currentPattern):
      sayi = random.randint(0,30)
      totalInput += str(sayi)
        #take random numbers
      randomNumber = Label(text= sayi , fg= numberColor, bg = backgroundColor, font=("Verdana",40), cursor = "heart")
      randomNumber.pack()
      randomNumber.place(x=random.randint(0,500), y=random.randint(150,500))
      root.update()
      time.sleep(1.25)
      randomNumber.destroy()
      root.update()
      time.sleep(0.5)
   userAnswer()



#main part
begin = Label(text="\n \n \nWelcome to the Memoria!\n\n",fg=buttonColor, font=("Verdana",30), bg = backgroundColor)
begin.pack(pady = 20)

begin_button = Button(text="START", width = 0, bg = buttonColor, fg = 'white', font=("Verdana"), command = beginning, justify = CENTER,
               activebackground = 'black', activeforeground = 'white', bd = 6, relief = RAISED, cursor="heart")
begin_button.pack(padx= 20, pady = 20)

exit_button = Button(text=" EXIT ", width = 0, bg = buttonColor, fg = 'white', font=("Verdana"), command = sys.exit, justify = CENTER,
               activebackground = 'black', activeforeground = 'white', bd = 6, relief = RAISED, cursor="heart")
exit_button.pack()

root.mainloop()
