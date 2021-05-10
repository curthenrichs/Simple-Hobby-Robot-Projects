import sys
import serial
import time
import json
import threading

MIN_NECK_POSITION = 0
MAX_NECK_POSITION = 120
NECK_POSITION_STEP = 10
TIMEOUT_TIME = 0.1

class Bubbles(object):
    '''Defines the hardware interface for the Bubbles robot'''



#===============================================================================
#                                Initializer
#===============================================================================

    def __init__(self,port=None):
        '''Generate class attributes'''

        #Control attributes
        self.rgb = (0,0,0)
        self.direction = "stop"
        self.mode = "off"
        self.neck_position = 0
        self.distance = 0
        self.serialPort = serial.Serial()

        #dirty flags
        self.updatedColor = True
        self.updatedDirection = True
        self.updatedMode = True
        self.updatedNeckPosition = True

        #Sensor attributes
        self.distance = 0
        self.connectionStatus = False
        self._currentNeckPosition = MIN_NECK_POSITION
        self._last_uuid = 0

        #thread safe attributes
        self.lock = threading.RLock()

#===============================================================================
#                          Accessors and Modifiers
#===============================================================================

    def get_port_list(self):
        ''' Lists serial port names
            :raises EnvironmentError:
                On unsupported or unknown platforms
            :returns:
                A list of the serial ports available on the system
        '''
        #determine operating system
        if sys.platform.startswith("win"):
            ports = ["COM%s" % (i + 1) for i in range(256)]
        elif sys.platform.startswith("linux") or sys.platform.startswith("cygwin"):
            # this excludes your current terminal "/dev/tty"
            ports = glob.glob("/dev/tty[A-Za-z]*")
        elif sys.platform.startswith("darwin"):
            ports = glob.glob("/dev/tty.*")
        else:
            raise EnvironmentError("Unsupported platform")

        #generate list of valid ports
        result = []
        for port in ports:
            try:
                s = serial.Serial(port)
                s.close()
                result.append(port)
            except (OSError, serial.SerialException):
                pass

        retStr = ""
        for str in result:
            retStr = retStr + " " + str
        retStr = retStr + " -none-"
        return retStr


    def set_port(self,port):
        '''Set and open the serial port for the object'''
        self.close_port()
        str = "failed"
        with self.lock:
            try:
                self.serialPort.baudrate = 9600
                self.serialPort.port = port
                self.serialPort.timeout = 0.2
                self.serialPort.open()
                str = "passed"
            except:
                pass
        return str


    def close_port(self):
        '''Close the serial port if open'''
        with self.lock:
            try:
                if self.serialPort != None and self.serialPort.is_open:
                    self.serialPort.close()
            except:
                pass


    def set_direction(self,cmd):
        '''Sets the travel direction of bubbles either as
           forward, backward, left, right, or stop'''
        if cmd == "stop" or cmd == "forward" or cmd == "backward" or \
            cmd == "left" or cmd == "right":
            with self.lock:
                self.direction = cmd
                self.updatedDirection = True


    def set_mode(self,mode):
        '''Sets the control mode of Bubbles as off, auton, or manual'''
        if mode == "off" or mode == "auton" or mode == "manual":
            with self.lock:
                self.mode = mode
                self.updatedMode = True


    def set_head(self,pos):
        '''Sets the head step as either up, down or sets the head to home'''
        if pos == "up" or pos == "down" or pos == "home":
            with self.lock:
                self.neck_position = pos
                self.updatedNeckPosition = True


    def set_head_color(self,r,g,b):
        '''Sets the next color for the RGB lights'''
        if r >= 0 and r < 256 and g >= 0 and g < 256 and b >= 0 and b < 256:
            with self.lock:
                self.rgb = (r,g,b)
                self.updatedColor = True


    def get_head_color(self):
        '''Gets the current LED color'''
        color = None
        with self.lock:
            color = self.rgb
        return color


    def get_connection_status(self):
        '''Gets the current Bubbles connection status'''
        connect = None
        with self.lock:
            connect = self.connectionStatus
        return connect


    def get_distance(self):
        '''Gets the current ultrasonic distance in inches'''
        dist = 0
        with self.lock:
            dist = self.distance
        return dist

#===============================================================================
#                          Hardware Update Loop
#===============================================================================

    def _writeMessage(self,msg):
        '''writes a message to the open serial port'''
        txStr = json.dumps(msg, separators=(',',':'))
        try :
            if self.serialPort is not None and self.serialPort.is_open :
                self.serialPort.write(bytearray(txStr.encode('utf-8')))
                self.serialPort.write(b'\x00')
        except :
            pass


    def _readMessage(self):
        '''reads a message from the currently open serial port'''
        global TIMEOUT_TIME
        if self.serialPort is not None and self.serialPort.is_open :
            start_time = time.time()
            endOfStr = False
            rxStr = ""
            while (time.time() - start_time) < TIMEOUT_TIME and not endOfStr :
                try:
                    byte = self.serialPort.read()
                    if byte == b'\x00':
                        endOfStr = True
                    else:
                        rxStr = rxStr + str(byte,'utf-8')
                except:
                    break
            try:
                rxMsg = json.loads(rxStr)
                return rxMsg
            except Exception as e:
                return None
        else:
            return None


    def _encodeSyncRequest(self):
        '''encodes the sync request which gets the current control parameters'''
        self._last_uuid = 12#int(time.time()) % 0xFFFFFF
        txMsg = {
                    "GCD" : True,
                    "GDi" : True,
                    "U" : self._last_uuid,
                }
        return txMsg


    def _decodeSyncMessage(self,msg):
        '''Decodes message from bubbles with the current control parameters'''
        try:
            neckPos = msg["CD"]["Np"]
            if neckPos != self.neck_position and self.mode == "manual":
                self.updatedNeckPosition = True

            controlMode = msg["CD"]["Mo"]
            if controlMode != self.mode:
                self.updatedMode = True

            controlCmd = msg["CD"]["Dr"]
            if controlCmd != self.direction and self.mode == "manual":
                self.updatedDirection = True

            r = msg["CD"]["Cr"]["r"]
            g = msg["CD"]["Cr"]["g"]
            b = msg["CD"]["Cr"]["b"]
            if self.rgb[0] != r and self.mode == "manual":
                self.updatedColor = True
            elif self.rgb[1] != g and self.mode == "manual":
                self.updatedColor = True
            elif self.rgb[2] != b and self.mode == "manual":
                self.updatedColor = True

            self.distance = msg["Di"]
        except:
            pass

    def _encodeUpdateMessage(self):
        '''encodes message to bubbles with the content to update parameters'''
        self._last_uuid = 13#int(time.time()) % 0xFFFFFF
        txMsg = {"U" : self._last_uuid }
        with self.lock :
            if self.updatedColor :
                self.updatedColor = False
                c = self.rgb
                txMsg.update({"Cr":{"r":c[0],"g":c[1],"b":c[2]}})

            if self.updatedMode :
                self.updatedMode = False
                txMsg.update({"Mo":self.mode})

            if self.updatedDirection :
                self.updatedDirection = False
                dir = self.direction
                if dir == "left":
                    dir = dir + " forward"
                if dir == "right":
                    dir = dir + " forward"
                txMsg.update({"Dr":dir})

            if self.updatedNeckPosition :
                global NECK_POSITION_STEP
                global MAX_NECK_POSITION
                global MIN_NECK_POSITION
                self.updatedNeckPosition = False
                if self.neck_position == "up" :
                    pos = (self._currentNeckPosition + NECK_POSITION_STEP)
                    if pos >= MIN_NECK_POSITION and pos <= MAX_NECK_POSITION :
                        txMsg.update({"Np":pos})
                        self._currentNeckPosition = pos
                elif self.neck_position == "down" :
                    pos = (self._currentNeckPosition - NECK_POSITION_STEP)
                    if pos >= MIN_NECK_POSITION and pos <= MAX_NECK_POSITION :
                        txMsg.update({"Np":pos})
                        self._currentNeckPosition = pos
                elif self.neck_position == "home" :
                    txMsg.update({"Np":MIN_NECK_POSITION})
                    self._currentNeckPosition = MIN_NECK_POSITION
        return txMsg


    def _update(self,stop_event):
        '''Periodic update of the data over serial. Place function in thread'''
        print("hardware update thread opened")
        while not stop_event.wait(1) :
            #delay for some time before next update
            print("...hardware update tick")

            #send sync with bubbles for current hardware configuration
            txMsg = self._encodeSyncRequest()
            self._writeMessage(txMsg)

            #recieve sync message from bubbles for current state
            rxMsg = self._readMessage()
            if rxMsg is None :
                self.connectionStatus = False
                continue #message not captured, end as not synced
            elif "U" in rxMsg.keys() and rxMsg["U"] == self._last_uuid :
                self._decodeSyncMessage(rxMsg)

            #cache local copies of data for update and produce json output
            txMsg = self._encodeUpdateMessage()
            self._writeMessage(txMsg)

            #wait for acknowlegement
            rxMsg = self._readMessage()
            if rxMsg is None:
                self.connectionStatus = False
                continue #message not captured, end as not synced
            elif "U" in rxMsg.keys() and rxMsg["U"] == self._last_uuid :
                self.connectionStatus = True

        print("hardware update thread closed")
