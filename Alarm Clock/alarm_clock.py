
# Firstly, we must important all the neccesary libaries and modules needed for the alarm clock 

from tkinter import *
import datetime 
import time 
import subprocess


def alarm(set_alarm_timer):
    while True:
        time.sleep(1)
        current_time = datetime.datetime.now()
        now = current_time.strftime("%H:%M:%S")
        date = current_time.strftime("%d/%m/%Y")

        print("The current date is :",date)
        print(now)
        if now == set_alarm_timer:
            print("Rise and Shine, Sleep Head!")
        subprocess.call(["afplay", "sound.wav"])
        break
    
def actual_time():
    set_alarm_timer = f"{hour.get()}:{min.get()}:{sec.get()}"
    alarm(set_alarm_timer)