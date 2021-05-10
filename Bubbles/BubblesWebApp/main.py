import sys
import time
import threading
from hardware import Bubbles
from flask import Flask, render_template, request, Response

# Global application objects
app = Flask (__name__)
bubbles = Bubbles()

#===============================================================================
#                            Web Server Functions
#===============================================================================

@app.route("/")
def index():
    '''Render the control page'''
    return render_template ('index.html', name = None)

@app.route("/move/")
@app.route("/move/<direction>")
def move(direction="stop"):
    '''Moves bubbles in specified direction'''
    bubbles.set_direction(direction)
    return direction

@app.route("/set_mode/")
@app.route("/set_mode/<mode>")
def set_mode(mode="off"):
    '''Sets the operation mode of Bubbles hardware'''
    bubbles.set_mode(mode)
    return mode

@app.route("/list_ports")
def list_ports():
    '''Lists all open Serial ports and returns them as space deliminated
    string for future request to open a port'''
    return bubbles.get_port_list()

@app.route("/open_port/")
@app.route("/open_port/<port>")
def open_port(port="-none-"):
    '''Attempts to open the current port '''
    str = "...failed"
    if port == "-none-":
        str = ""
        bubbles.close_port()
    else:
        try:
            str = bubbles.set_port(port)
        except:
            pass
    return str

@app.route("/set_color/")
@app.route("/set_color/<hexColor>")
def set_color(hexColor="000000"):
    '''Parses supplied 24-bit hex value to rgb color'''
    try:
        hex = int(hexColor,16)
        r = (hex & 0x0FF0000) >> 16
        g = (hex & 0x000FF00) >> 8
        b = (hex & 0x00000FF) >> 0
        bubbles.set_head_color(r,g,b)
    except:
        pass
    return hexColor

@app.route("/move_head/<pos>")
def move_head(pos):
    '''Moves Bubbles head by step or back to home'''
    bubbles.set_head(pos)
    return pos

#===============================================================================
#                                    MAIN
#===============================================================================

def main():
    '''Main program will create an update thread for Bubbles hardware
       connection. main will be consumed with webserver code. WHen server is
       killed, all threads will stop and hardware devices released'''

    pill2kill = threading.Event()
    t1 = threading.Thread(target=bubbles._update, args=(pill2kill,))
    t1.start()

    try:
        app.run(debug=False, threaded=True)
    except:
        print("shutting down server")

    #shut off hardware
    pill2kill.set()
    t1.join(2)
    time.sleep(2)
    bubbles.close_port()

#run main program if this module is not included
if __name__ == "__main__":
    main()
