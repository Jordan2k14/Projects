
# Firstly, we must important all the neccesary libaries and modules needed for the alarm clock 

from tkinter import *      # Needed for the GUI
import datetime           # Needed for the date
import time              # Needed for the time
import subprocess       # Needed to play the alarm sound


# I'm using important subprocess instead of import winsound because I am on MAC
# However you can change import subprocess with import winsound if you want to use windows sounds
# Regardless it should still work the same

# While loop needed for the alarm
def alarm(set_alarm_timer):
    while True:
        time.sleep(1) # Halts the execution until we get the time value from the user as displayed below
        current_time = datetime.datetime.now() # displays the current time 
        now = current_time.strftime("%H:%M:%S") # sets the time
        date = current_time.strftime("%d/%m/%Y") # sets the date

        print("Welcome, The current date is :",date) # Tells the user the current date
        print(now)
        if now == set_alarm_timer:
            subprocess.call(["afplay", "sound.wav"]) # Plays the sound - sound.wav
            print("Wake Up! Wake Up! It's time to get up!!")
            break
    
def actual_time():
    set_alarm_timer = f"{hour.get()}:{min.get()}:{sec.get()}"
    alarm(set_alarm_timer)


# This is our GUI for the alarm clock using tkinter

clock = Tk()

clock.title("Jordan's Alarm Clock") # Name of the alarm clock
clock.geometry("400x200") # Setting size
time_format=Label(clock, text= "Enter time in 24 hour format!", fg="blue",bg="red",font="Arial").place(x=60,y=120) # Setting the font & colour
addTime = Label(clock,text = "Hour  Min   Sec",font=60).place(x = 110)
setYourAlarm = Label(clock,text = "Alarm for waking the user",fg="orange",relief = "solid",font=("Helevetica",7,"bold")).place(x=0, y=29) # setting font and colour

# The Variables we require to set the alarm(initialization):
hour = StringVar()
min = StringVar()
sec = StringVar()

#Time required to set the alarm clock:
hourTime= Entry(clock,textvariable = hour,bg = "yellow",width = 15).place(x=110,y=30) # setting the colour
minTime= Entry(clock,textvariable = min,bg = "yellow",width = 15).place(x=150,y=30)   # setting the colour
secTime = Entry(clock,textvariable = sec,bg = "yellow",width = 15).place(x=200,y=30)  # setting the colour

#To take the time input by user:
submit = Button(clock,text = "Set Alarm",fg="pink",width = 10,command = actual_time).place(x =110,y=70) # creates a button so the user can set the alarm, a countdown will be displayed

clock.mainloop()
#Execution of the window.