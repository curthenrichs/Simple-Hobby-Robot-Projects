using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

using AForge;
using AForge.Video;
using AForge.Video.DirectShow;

// currently the system is disabling the vision processing until the error is fixed


namespace Bubbles_Brain
{
    public partial class form1 : Form
    {
        //variables for the cleint to communicate to the robot server
        //control mode for the state machine
        int controlMode = 0;

        //Create the server for bubbles to interface with hardware
        BubblesRobotServer bubbles;
        Thread bubblesServerThread;

        //create the joystick server and thread
        BubblesJoystick joystick;
        Thread joystickThread;

        //Vision stuff
        Bitmap currentImage;
        //vision form commented to cancel from launch
        //Form3 form3;

        //constructor
        public form1()
        {
            //init form
            InitializeComponent();

            //start up the bubbles brain and server
            bubbles = new BubblesRobotServer(bubblesHardware);
            bubblesServerThread = new Thread(bubbles.run);
            bubblesServerThread.Start();

            //start up the joystick thread for updating joystick info
            joystick = new BubblesJoystick();
            joystickThread = new Thread(joystick.run);
            joystickThread.Start();

            //let stuff get setup
            Thread.Sleep(200);
            
            //start the video feed
            localVideoDevice();

            //Display serialPort option panel
            //Not implemented yet :(

            // start vision processing form
            //form3 = new Form3();
            //form3.Show();
        }

        //Auton enabled or not helps to control state of bot
        private void autoRadio_CheckedChanged(object sender, EventArgs e)
        {
            controlMode = 0;
        }

        //Command mode for teleop
        private void CommandRadio_CheckedChanged(object sender, EventArgs e)
        {
            controlMode = 1;
        }

        //go to joystick mode return an error if no joystick available for teleop
        private void JoystickRadio_CheckedChanged(object sender, EventArgs e)
        {
            
            controlMode = 2;
            //check to make sure a joystick is available
            if(joystick.joystickFound)
            {
                //then we link the value for the joystick to the server
                label5.Text = joystick.getControllerName();
            }
            else if (JoystickRadio.Checked)
            {
                //there is no joystick
                MessageBox.Show("No Joystick detected on System", "ERROR", MessageBoxButtons.OK);
                label5.Text = "No Joystick Detected";
            }
        }

        //go to keyboard drive mode for teleop
        private void KeyBoardRadio_CheckedChanged(object sender, EventArgs e)
        {
            controlMode = 3;
        }

        //opens a dialog to tell the commands of the system to the user and what they mean
        private void commandsOpen_Click(object sender, EventArgs e)
        {
            Form2 commandForm = new Form2();
            commandForm.Show();
        }
        
        //used to enter the data for the command into the system
        private void enterButton_Click(object sender, EventArgs e)
        {
            if (controlMode == 1)
            {
                string text = textBox1.Text;
                textBox1.Text = "";
                bubbles.processCommands(text);
            }
            else
            {
                MessageBox.Show("Need to be in Command Mode to use Commands", "ERROR", MessageBoxButtons.OK);
            }
        }

        //estop button kills the movements of bubbles if it can talk to it else it it is up to the firmware
        private void button1_Click(object sender, EventArgs e)
        {
            //send a stop signal to the object
            bubbles.setEnableAuton('D');
            bubbles.setEnableDrive('D');
        }

        //gets when the keyboard is pressed over the form
        private void form1_KeyDown(object sender, KeyEventArgs e)
        {
            //if we are in keyboard mode then route w,a,d,s to the singals
            if (controlMode == 3)
            {
                bubbles.setEnableAuton('D');
                bubbles.setEnableDrive('E');
                
                //if a w go  forward
                if (e.KeyValue == 87)
                {
                    bubbles.setDriveMode('F');
                    bubbles.setToggleMotor('F');
                }
                //if a s go backward
                else if(e.KeyValue == 83)
                {
                    bubbles.setDriveMode('F');
                    bubbles.setToggleMotor('B');
                }
                //if an a go left
                else if(e.KeyValue == 65)
                {
                    bubbles.setDriveMode('L');
                }
                //if a d go right
                else if (e.KeyValue == 68)
                {
                    bubbles.setDriveMode('R');
                }
                //if a space stop
                else if(e.KeyValue == 32)
                {
                    bubbles.setEnableDrive('D');
                }
                else
                {
                    //invalid command
                    MessageBox.Show("Invalid character please try 'w' 's' 'a' 'd' or spacebar. \nAlso please do not capitalize", "ERROR", MessageBoxButtons.OK);
                }
            }
            else if(controlMode == 1)
            {
                if(e.KeyValue == 13)
                {
                    string text = textBox1.Text;
                    textBox1.Text = "";
                    int typeCmd = bubbles.processCommands(text);
                    //get the tracking color
                    Color tColor = bubbles.getTrackColor();
                    //send the color to the tracking form
                }
            }
        }

        //loads a videosource on startup
        private void localVideoDevice()
        {
            VideoCaptureDeviceForm form = new VideoCaptureDeviceForm();

            if(form.ShowDialog(this) == DialogResult.OK)
            {
                //create video source
                VideoCaptureDevice videoSource = form.VideoDevice;
                OpenVideoSource(videoSource);
            }
        }

        //opens the selected videosource from startup
        private void OpenVideoSource(IVideoSource source)
        {
            //set busy cursor
            this.Cursor = Cursors.WaitCursor;

            //stop any current video source
            CloseCurrentVideoSource();

            //start new video source
            videoSourcePlayer1.VideoSource = source;
            videoSourcePlayer1.Start();

            this.Cursor = Cursors.Default;

            label10.Visible = false;
        }

        //closes the videosource playing on the screen
        private void CloseCurrentVideoSource()
        {
            if(videoSourcePlayer1.VideoSource != null)
            {
                videoSourcePlayer1.SignalToStop();

                //wait ~ 3 seconds
                for(int i = 0; i < 30; i++)
                {
                    if (!videoSourcePlayer1.IsRunning)
                        break;
                    Thread.Sleep(100);
                }

                if (videoSourcePlayer1.IsRunning)
                {
                    videoSourcePlayer1.Stop();
                }

                videoSourcePlayer1.VideoSource = null;
                label10.Visible = true;
            }
        }

        //this is a tick for the gui which then relays all the information to the server
        private void timer1_Tick(object sender, EventArgs e)
        {
            //if joystick calculate the zones for left and right
            if(controlMode == 2)
            {
                bubbles.setEnableAuton('D');
                bubbles.setEnableDrive('E');
               
                //if not turning
                if((joystick.getX() < 0.3) && (joystick.getX() > -0.3))
                {
                    //down
                    if(joystick.getY() < -0.3)
                    {
                        bubbles.setDriveMode('F');
                        bubbles.setToggleMotor('F');
                    }
                    //up
                    else if(joystick.getY() > 0.3)
                    {
                        bubbles.setDriveMode('F');
                        bubbles.setToggleMotor('B');
                    }
                    //stop
                    else
                    {
                        bubbles.setEnableDrive('D');
                    }
                }
                //else turning
                else
                {
                    bubbles.setEnableAuton('D');
                    bubbles.setEnableDrive('E');
                    bubbles.setToggleMotor('F');

                    //left
                    if(joystick.getX() < -0.3)
                    {
                        bubbles.setDriveMode('L');
                    }
                    //right
                    else 
                    {
                        bubbles.setDriveMode('R');
                    }
                }
            }
            //IF AUTON
            else if(controlMode == 0)
            {
                bubbles.setEnableAuton('E');

                //set to defaults for next time switch to teleop
                bubbles.setEnableDrive('D');
                bubbles.setNeckState('D');
                bubbles.setToggleMotor('F');
                bubbles.setDriveMode('F');
            }
        }

        //the program is closing everyone screem !!!!!!!!!!!!!!!!!
        private void form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            //kill threads
            bubbles.killThread = true;
            joystick.killThread = true;

            //delay enough time for threads to close
            Thread.Sleep(1000);

            //close the video signal
            CloseCurrentVideoSource();
        }

        //every time a new frame appears for the player it is grabbed and saved to be sent to bubbles
        private void videoSourcePlayer1_NewFrame(object sender, ref Bitmap image)
        {
            //flip it to be correct
            image.RotateFlip(RotateFlipType.RotateNoneFlipX);
            //create a copy of the image for use in the vision thread
            currentImage = (Bitmap)image.Clone();
            //set values to be processed by the thread
            //form3.setOriginalImage(currentImage);
        }
    }
}
