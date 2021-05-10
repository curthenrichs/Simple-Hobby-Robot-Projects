using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.IO.Ports;
using System.Drawing;
using System.Windows.Forms;

namespace Bubbles_Mark_2
{
    //enums for the states the robot could be in (Disable brain means the arduino no longer controls bubbles)
    enum State { Teleoperated, Autonomous, DisableBrain };
    enum AutonStates { ColorTracking, OnBoard, MoveHead, EyeColor, Stop }
    enum DriveMovements { Forward, Backward, ForwardLeft, ForwardRight, BackwardLeft, BackwardRight, Stop, DontCare };
    enum NeckPos { Up, Down, DontCare };
    enum EyeColor { Red, Green, Blue, DontCare };

    /// <summary>
    /// This class is the hardware communication point. It controls the flow of data from the user interface and the vision system
    /// into a serial line to the bubbles hardware. Pretty snazy if you ask me.
    /// Several enum types are used as states for the robot.
    /// Autonmous has the ability to use tracking, onboard, eye color, and neck movements
    /// </summary>
    class RobotServer
    {
        //================================================================
        //                      Fields
        //================================================================
        
        //variables that hold the current states
        //statemachine variables for the autonomous code
        private AutonStates currentAutonState, nextAutonState;
        //the state the user desires the robot to be in
        private State desiredState;
        //hold the user desired states of the robot
        private DriveMovements desiredMovement;
        private NeckPos desiredNeckPosition;
        //hold the current states of the robot
        private DriveMovements currentMovement;
        private NeckPos currentNeckPosition;
        private EyeColor currentEyeColor;

        //object fields
        //used to store the current tracking clor for the vision system
        private Color trackingColor;
        //used to store the serial interface to the hardware
        private SerialPort hardware;
        //commanded true to kill the thread
        public bool killThread = false;

        //=================================================================
        //                         Constructor 
        //=================================================================

        //default constructor
        public RobotServer()
        {
            desiredState = State.DisableBrain;
            currentAutonState = AutonStates.Stop;
            nextAutonState = AutonStates.Stop;
            desiredMovement = DriveMovements.Stop;
            desiredNeckPosition = NeckPos.Down;
            trackingColor = Color.Black;
            currentEyeColor = EyeColor.DontCare;
            hardware = null;
        }

        //serialport constructor 
        public RobotServer(SerialPort port)
        {
            desiredState = State.DisableBrain;
            currentAutonState = AutonStates.Stop;
            nextAutonState = AutonStates.Stop;
            desiredMovement = DriveMovements.Stop;
            desiredNeckPosition = NeckPos.Down;
            trackingColor = Color.Black;
            currentEyeColor = EyeColor.DontCare;
            hardware = port;
        }

        //serialport and seeded event mode constructor (recommended)
        public RobotServer(SerialPort port,MainGUI.Mode mode)
        {
            desiredMovement = DriveMovements.Stop;
            currentAutonState = AutonStates.Stop;
            nextAutonState = AutonStates.Stop;
            desiredNeckPosition = NeckPos.Down;
            trackingColor = Color.Black;
            currentEyeColor = EyeColor.DontCare;
            hardware = port;

            if (mode == MainGUI.Mode.Autonomous)
                desiredState = State.Autonomous;
            else
                desiredState = State.Teleoperated;
        }

        //seed event mode only (Auto creates serialport)
        public RobotServer(MainGUI.Mode mode)
        {
            desiredMovement = DriveMovements.Stop;
            currentAutonState = AutonStates.Stop;
            nextAutonState = AutonStates.Stop;
            desiredNeckPosition = NeckPos.Down;
            trackingColor = Color.Black;
            currentEyeColor = EyeColor.DontCare;
            hardware = generateNewSerialPort();

            if (mode == MainGUI.Mode.Autonomous)
                desiredState = State.Autonomous;
            else
                desiredState = State.Teleoperated;
        }

        //==================================================================
        //                   Event Based Movement calculators
        //==================================================================

        //calculate the movement to be performed by bubbles based on x and y
        public void calcMovementsViaJoystick(BubblesJoystick joystick)
        {
            //teleoperated mode
            desiredState = State.Teleoperated;

            //calculate the behavior
            //if not turning
            if ((joystick.getX() < 0.3) && (joystick.getX() > -0.3))
            {
                //down
                if (joystick.getY() < -0.3)
                    desiredMovement = DriveMovements.Forward;
                //up
                else if (joystick.getY() > 0.3)
                    desiredMovement = DriveMovements.Backward;
                //stop
                else
                    desiredMovement = DriveMovements.Stop;
            }
            //else turning
            else
            {
                //left
                if (joystick.getX() < -0.3)
                {
                    if (joystick.getY() < -0.3)
                        desiredMovement = DriveMovements.ForwardLeft;
                    else if (joystick.getY() > 0.3)
                        desiredMovement = DriveMovements.BackwardLeft;
                    else
                        desiredMovement = DriveMovements.Stop;
                }
                //right
                else
                {
                    if (joystick.getY() < -0.3)
                        desiredMovement = DriveMovements.ForwardRight;
                    else if (joystick.getY() > 0.3)
                        desiredMovement = DriveMovements.BackwardRight;
                    else
                        desiredMovement = DriveMovements.Stop;
                }
            }
        }

        //autonomous movement calculator
        public void calcMovementsViaAuton()
        {
            desiredState = State.Autonomous;
        }

        //when the emergency stop is pressed
        public void estop()
        {
            desiredState = State.DisableBrain;
            desiredMovement = DriveMovements.Stop;
        }

        //calc movement based on commands
        public void calcMovementsViaCommand(String text)
        {
            //set the mode to teloperated
            desiredState = State.Teleoperated;

            //make all lowercase to make things easier
            String command = text.ToLower();

            //figure out what was said
            if (command.Contains("forward"))
            {
                desiredMovement = DriveMovements.Forward;
            }
            else if (command.Contains("backward"))
            {
                desiredMovement = DriveMovements.Backward;
            }
            else if (command.Contains("left"))
            {
                desiredMovement = DriveMovements.ForwardLeft;
            }
            else if (command.Contains("right"))
            {
                desiredMovement = DriveMovements.ForwardRight;
            }
            else if (command.Contains("rest"))
            {
                desiredMovement = DriveMovements.DontCare;
                desiredState = State.DisableBrain;
            }
            else if (command.Contains("stay"))
            {
                desiredMovement = DriveMovements.Stop;
            }
            else if (command.Contains("look"))
            {
                if (command.Contains("down"))
                {
                    desiredNeckPosition = NeckPos.Down;
                }
                else if (command.Contains("up"))
                {
                    desiredNeckPosition = NeckPos.Up;
                }
                else
                {
                    MessageBox.Show("Head position not recognized!", "ERROR", MessageBoxButtons.OK);
                }
            }
            else if (command.Contains("track"))
            {
                desiredState = State.Autonomous;
                currentAutonState = AutonStates.ColorTracking;

                if (command.Contains("red"))
                {
                    trackingColor = Color.Red;
                }
                else if (command.Contains("orange"))
                {
                    trackingColor = Color.Orange;
                }
                else if (command.Contains("yellow"))
                {
                    trackingColor = Color.Yellow;
                }
                else if (command.Contains("green"))
                {
                    trackingColor = Color.Green;
                }
                else if (command.Contains("blue"))
                {
                    trackingColor = Color.Blue;
                }
                else if (command.Contains("purple"))
                {
                    trackingColor = Color.Purple;
                }
                else
                {
                    MessageBox.Show("Color not recognized!", "ERROR", MessageBoxButtons.OK);
                }
            }
            else
            {
                MessageBox.Show("Command not recognized!", "ERROR", MessageBoxButtons.OK);
            }
        }

        //calc movement based a=n characters from keyboard
        public void calcMovementsViaChar(char com)
        {
            //state is teleop
            desiredState = State.Teleoperated;

            //figure out what key is pressed
            switch (com)
            {
                case 'W':
                case 'w':
                    desiredMovement = DriveMovements.Forward;
                    break;
                case 'S':
                case 's':
                    desiredMovement = DriveMovements.Backward;
                    break;
                case 'A':
                case 'a':
                    desiredMovement = DriveMovements.ForwardLeft;
                    break;
                case 'D':
                case 'd':
                    desiredMovement = DriveMovements.ForwardRight;
                    break;
                case (char)32: //space
                    desiredMovement = DriveMovements.Stop;
                    break;
                default:
                    MessageBox.Show("Invalid character please try 'w' 's' 'a' 'd' or spacebar.\nAlso please do not capatilize.", "ERROR", MessageBoxButtons.OK);
                    break;
            }
        }

        //===================================================================
        //                      Getters and Setters
        //===================================================================
        
        //gets the current tracking color
        public Color getTrackingColor()
        {
            return trackingColor;
        }
        
        //sets the tracking color
        public void setTrackingColor(Color color)
        {
            trackingColor = color;
        }

        //===================================================================
        //                  Thread Work and Serial Comm
        //===================================================================

        //runable thread
        public void run()
        {
            try
            {
                if (hardware != null)
                    hardware.Open();

                //the main running method for the thread
                while (!killThread)
                {
                    //are we autonomous?
                    if(desiredState == State.Autonomous)
                    {
                        //if hardware is bad
                        if (hardware != null && !hardware.IsOpen)
                            break;
                        //do auton code here
                        OuputCode();
                        NextStateCode();
                    }
                    else if(desiredState == State.DisableBrain)
                    {
                        //we are in disable brain and need to tell the serial that unless serial is down in which case we break
                        if (hardware != null && !hardware.IsOpen)
                            break;
                        hardware.WriteLine(encodeDataOut(desiredState, DriveMovements.DontCare, NeckPos.DontCare, EyeColor.DontCare)); //disable string
                        saveCurrentStates(desiredMovement, desiredNeckPosition, EyeColor.DontCare);
                    }
                    else
                    {
                        //we are in a teleoperated state and the behavior was already given in the state values
                        //if hardware is bad
                        if (hardware != null && !hardware.IsOpen)
                            break;
                        hardware.WriteLine(encodeDataOut(desiredState, desiredMovement, desiredNeckPosition, EyeColor.DontCare));
                        saveCurrentStates(desiredMovement, desiredNeckPosition, EyeColor.DontCare);
                    }
                }

                //close serial port connection
                if (hardware != null && hardware.IsOpen)
                {
                    hardware.Close();
                }
            } 
            catch(Exception e)
            {
                //is it serial difficulty?
                if (hardware == null || !hardware.IsOpen)
                    MessageBox.Show("SerialPort is dead " + e.Message);
                else
                    MessageBox.Show("Curt something funny happened here. " + e.Message);
            }
            finally
            {
                //close serial port
                if (hardware != null)
                    hardware.Close();
                MessageBox.Show("Serial Port is Closed");
            }
        }

        //auton code to be run  this is a state machine
        private void OuputCode()
        {
            //controls the mode to drive in auton
            DriveMovements autonMovements;
            //~~~~~~~~~~~~~~~~~~~~~OUTPUT LOGIC~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            //decide on mode to be in
            if(currentAutonState == AutonStates.ColorTracking)
            {
                //call reference to color tracking and set current color to the color
                //dont care about right now
            }
            else if(currentAutonState == AutonStates.EyeColor)
            {
                //set bubbles eye color in the future
                //dont care about right now
            }
            else if(currentAutonState == AutonStates.MoveHead)
            {
                //if up move it down if down move it up
                if (currentNeckPosition == NeckPos.Down)
                {
                    hardware.WriteLine(encodeDataOut(State.Autonomous, DriveMovements.DontCare, NeckPos.Up, EyeColor.DontCare));
                    saveCurrentStates(DriveMovements.DontCare, NeckPos.Up, EyeColor.DontCare);
                }
                else
                {
                    hardware.WriteLine(encodeDataOut(State.Autonomous, DriveMovements.DontCare, NeckPos.Down, EyeColor.DontCare));
                    saveCurrentStates(DriveMovements.DontCare, NeckPos.Down, EyeColor.DontCare);
                }
            }
            else if(currentAutonState == AutonStates.Stop)
            {
                //command a full stop of bubbles
                autonMovements = DriveMovements.Stop;
                hardware.WriteLine(encodeDataOut(State.Autonomous, autonMovements, currentNeckPosition, EyeColor.DontCare)); //string commanding full stop
                saveCurrentStates(autonMovements, currentNeckPosition, EyeColor.DontCare);
            }
            else
            {
                //use the onboard intelligence
                hardware.WriteLine(encodeDataOut(State.DisableBrain,DriveMovements.DontCare ,NeckPos.Down,EyeColor.DontCare)); //string commanding use onboard
                saveCurrentStates(DriveMovements.DontCare, NeckPos.Down, EyeColor.DontCare);
            }
        }

        //auton code to be run for the next state in state machine
        private void NextStateCode()
        {
            //~~~~~~~~~~~~~~~~~~~~~NEXT STATE LOGIC~~~~~~~~~~~~~~~~~~~~~~~~~~
        }

        //===================================================================
        //                       Utility Methods
        //===================================================================
        //save current states via desired states
        private void saveCurrentStates(DriveMovements move,NeckPos neck,EyeColor eye)
        {
            //if dont care then save from last
            if (move == DriveMovements.DontCare)
                currentMovement = currentMovement;
            else
                currentMovement = move;
            if (neck == NeckPos.DontCare)
                currentNeckPosition = currentNeckPosition;
            else
                currentNeckPosition = neck;

            if (eye == EyeColor.DontCare)
                currentEyeColor = currentEyeColor;
            else
                currentEyeColor = eye;
        }

        //encodes the state information to the arduino standard
        public String encodeDataOut(State st, DriveMovements move, NeckPos neck, EyeColor eye)
        {
            return "";
        }

        //decodes the sensor information from the ardunio standard
        public void decodeDataIn(String input)
        {

        }

        //generates a new serial port
        public SerialPort generateNewSerialPort()
        {
            return new SerialPort("COM1", 9600);   
        }
    }
}
