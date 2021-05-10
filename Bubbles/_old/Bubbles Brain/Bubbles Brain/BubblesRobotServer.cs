using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO.Ports;
using System.Drawing;
using System.Windows.Forms;


namespace Bubbles_Brain
{
    /// <summary>
    ///  This is the main server class for bubbles interfaceing hardware to the machine
    ///  This has a Thread ready method for running the server at the optimal speed for the system
    /// </summary>
    class BubblesRobotServer
    {
        //Serial port interfaces to an xbee to bubbles
        private SerialPort hardware;
        //Kills the thread when triggered for closing time
        public bool killThread = false;

        //******** The style of output is <enableAuton><enableDrive><driveMode><toggleMotor><neckState>;

        //auton or teleop   choose E or D
        private char enableAuton = 'D';
        //drivtrain active or not  choose E or D
        private char enableDrive = 'D';
        //direction of drivetrain F,L,R
        private char driveMode = 'F';
        //motor drive in reverse  F,B forward backward
        private char toggleMotor = 'F';
        //neck state U,D up,down
        private char neckState = 'D';
        //Command out for the color to track
        private Color color;

        /* Default constructor
         */
        public BubblesRobotServer()
        {
            hardware = null;
        }

        /* Serial port passed in constructor
         */
        public BubblesRobotServer(SerialPort hard)
        {
            //initialize serial port
            hardware = hard;
            //open serial port
            try
            {
                if (hardware != null)
                {
                    hardware.Open();
                }
            }
            catch(System.IO.IOException ioe)
            {
                hardware = null;
            }
            catch(UnauthorizedAccessException aue)
            {
                hardware = null;
            }
        }

        /* the executable thread method for the server to keep constant contact witht the world
         */
        public void run()
        {
            //the main running method for the thread
            while(!killThread)
            {
                //if an actual serial port in created
                if(hardware != null)
                {
                    //send out the current data to the system   -----------------------> if overflow then have a check system
                    //<enableAuton><enableDrive><driveMode><toggleMotor><neckState>;
                    hardware.WriteLine(enableAuton.ToString() + enableDrive.ToString() + driveMode.ToString() + toggleMotor.ToString() + neckState.ToString() + ";");

                    //maybe someday read in the data from bubbles for high level decisions... but not today
                }
            }
        }

        /*Sets the state of ea=nableDrive
         */
        public void setEnableAuton(char c)
        {
            enableAuton = c;
        }

        /*Sets the state of enableDrive
         */
        public void setEnableDrive(char c)
        {
            enableDrive = c;
        }

        /*Sets the state of driveMode
         */
        public void setDriveMode(char c)
        {
            driveMode = c;
        }

        /*Sets the state of toggleMotor
         */
        public void setToggleMotor(char c)
        {
            toggleMotor = c;
        }

        /* Sets the state of neckState
         */
        public void setNeckState(char c)
        {
            neckState = c;
        }

        /*Returns the state of enableAuton
         */
        public char getEnableAuton()
        {
            return enableAuton;
        }

        /*Returns the state of enableDrive
         */
        public char getEnableDrive()
        {
            return enableDrive;
        }

        /*returns the char for the toggle of the motor
         */
        public char getToggleMotor()
        {
            return toggleMotor;
        }

        /* returns neckState char
         */
        public char getNeckState()
        {
            return neckState;
        }

        /* Returns the color to track 
         * if the command mode or the auton mode are open
         */
        public Color getTrackColor()
        {
            return color;
        }

        /*  Command Processing
         * processes a string with a command in from either the recognizer or the gui 
         * This will probabaly call a DB to match strings
         * 
         * will return a 0 if a move body command
         *      return a 1 if move head
         *      return a 2 if vision
         *      return a -1 if error
         */
        public int processCommands(string text)
        {
            String command = text.ToLower();
            int cmdSt = -1;

            if(command.Contains("forward"))
            {
                enableAuton = 'D';
                enableDrive = 'E';
                toggleMotor = 'F';
                driveMode = 'F';
                cmdSt = 0;
            }
            else if(command.Contains("backward"))
            {
                enableAuton = 'D';
                enableDrive = 'E';
                toggleMotor = 'B';
                driveMode = 'F';
                cmdSt = 0;
            }
            else if (command.Contains("left"))
            {
                enableAuton = 'D';
                enableDrive = 'E';
                toggleMotor = 'F';
                driveMode = 'L';
                cmdSt = 0;
            }
            else if (command.Contains("right"))
            {
                enableAuton = 'D';
                enableDrive = 'E';
                toggleMotor = 'F';
                driveMode = 'R';
                cmdSt = 0;
            }
            else if (command.Contains("rest"))
            {
                enableAuton = 'E';
                enableDrive = 'E';
                toggleMotor = 'F';
                driveMode = 'L';
                cmdSt = 0;
            }
            else if (command.Contains("stay"))
            {
                enableAuton = 'D';
                enableDrive = 'D';
                toggleMotor = 'F';
                driveMode = 'L';
                cmdSt = 0;
            }
            else if (command.Contains("look"))
            {
                if(command.Contains("down"))
                {
                    neckState = 'D';
                    cmdSt = 1;
                }
                else if(command.Contains("up"))
                {
                    neckState = 'U';
                    cmdSt = 1;
                }
                else
                {
                    MessageBox.Show("Head position not recognized!", "ERROR", MessageBoxButtons.OK);
                }
            }
            else if (command.Contains("track"))
            {
                if(command.Contains("red"))
                {
                    color = Color.Red;
                    cmdSt = 2;
                }
                else if(command.Contains("orange"))
                {
                    color = Color.Orange;
                    cmdSt = 2;
                }
                else if(command.Contains("yellow"))
                {
                    color = Color.Yellow;
                    cmdSt = 2;
                }
                else if(command.Contains("green"))
                {
                    color = Color.Green;
                    cmdSt = 2;
                }
                else if(command.Contains("blue"))
                {
                    color = Color.Blue;
                    cmdSt = 2;
                }
                else if(command.Contains("purple"))
                {
                    color = Color.Purple;
                    cmdSt = 2;
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

            return cmdSt;
        }
    }
}
