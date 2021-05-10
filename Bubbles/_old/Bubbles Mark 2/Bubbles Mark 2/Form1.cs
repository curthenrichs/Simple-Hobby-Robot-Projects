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
using System.IO.Ports;

using AForge;
using AForge.Video;
using AForge.Video.DirectShow;

namespace Bubbles_Mark_2
{
    public partial class MainGUI : Form
    {
        //==================================================================
        //                    Fields and Constructor
        //==================================================================
        
        //modes of operation
        public enum Mode { Keyboard, Joystick, Command, Autonomous}
        private Mode controlMode;
        private RobotServer bubblesHardware;
        private BubblesJoystick joystick;
        private Thread bubblesServerThread;
        private Thread joystickThread;
        private VisionGUI visionGUI;

        //constructor
        public MainGUI()
        {
            //initialize form
            InitializeComponent();

            //setup video source
            localVideoDevice();

            //set defaults for fields
            controlMode = Mode.Autonomous;
            bubblesHardware = new RobotServer(controlMode);
            joystick = new BubblesJoystick();

            //create threads
            bubblesServerThread = new Thread(bubblesHardware.run);
            bubblesServerThread.Start();
            joystickThread = new Thread(joystick.run);
            joystickThread.Start();
        }

        //===================================================================
        //                     Video Capture Methods
        //===================================================================
        
        //handles all of the code to get the videodevice and instatiate it
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

            //stop any playing video sources
            CloseCurrentVideoSource();

            //start new source
            videoSourcePlayer1.VideoSource = source;
            videoSourcePlayer1.Start();

            //reset cursor
            this.Cursor = Cursors.Default;
        }

        //closes the current source being played
        private void CloseCurrentVideoSource()
        {
            if(videoSourcePlayer1.VideoSource != null)
            {
                videoSourcePlayer1.SignalToStop();

                //wait ~ 3 seconds
                for(int i = 0; i < 30; i++)
                {
                    if(!videoSourcePlayer1.IsRunning)
                    {
                        break;
                    }
                    Thread.Sleep(100);
                }

                if(videoSourcePlayer1.IsRunning)
                {
                    videoSourcePlayer1.Stop();
                }

                videoSourcePlayer1.VideoSource = null;
            }
        }

        //====================================================================
        //                       Event Handler Methods
        //=====================================================================
        private void MainGUI_FormClosing(object sender, FormClosingEventArgs e)
        {
            //kill any threads
            bubblesHardware.killThread = true;
            joystick.killThread = true;

            //delay so that threads have time to close
            Thread.Sleep(1000);

            //close the video signal
            CloseCurrentVideoSource();

            
        }

        //new frame is sent to the player
        private void videoSourcePlayer1_NewFrame(object sender, ref Bitmap image)
        {
            //flip the image since it is mirrored
            image.RotateFlip(RotateFlipType.RotateNoneFlipX);
            //send image to vision system and also to vision form
            if (visionGUI != null)
            {
                visionGUI.setBeforeImage(image);
                visionGUI.setAfterImage(image);
            }
        }

        //keyboard option is checked
        private void keyboardOption_CheckedChanged(object sender, EventArgs e)
        {
            //if it is switching from unchecked to checked
            if (keyboardOption.Checked)
                controlMode = Mode.Keyboard;
        }

        //joystick option is checked
        private void joystickOption_CheckedChanged(object sender, EventArgs e)
        {
            //if it is switching from unchecked to checked
            if (joystickOption.Checked)
            {
                controlMode = Mode.Joystick;
                joystickDetectionLabel.Text = joystick.getControllerName();
                //check to see if its valid
                if (!joystick.isJoystickFound())
                    MessageBox.Show("No Joystick Found", "ERROR", MessageBoxButtons.OK);
            }
        }

        //command option is checked
        private void commandOption_CheckedChanged(object sender, EventArgs e)
        {
            //if it is switching from unchecked to checked
            if (commandOption.Checked)
                controlMode = Mode.Command;
        }

        //autonomous option is checked
        private void autonomousOption_CheckedChanged(object sender, EventArgs e)
        {
            //if it is switching from unchecked to checked
            if (autonomousOption.Checked)
                controlMode = Mode.Autonomous;
        }

        //opens up the command list form for the user to view
        private void CommandsButton_Click(object sender, EventArgs e)
        {
            CommandList commandsform = new CommandList();
            commandsform.Show();
        }

        //enters the command typed into the robotserver
        private void enterButton_Click(object sender, EventArgs e)
        {
            if(controlMode == Mode.Command)
            {
                String text = commandText.Text;
                commandText.Text = "";
                bubblesHardware.calcMovementsViaCommand(text);
            }
            else
            {
                MessageBox.Show("Need to be in Command Mode to use Commands", "ERROR", MessageBoxButtons.OK);
            }
        }

        //gets when key is pressed when frame is active
        private void MainGUI_KeyDown(object sender, KeyEventArgs e)
        {
            //if we are in keyboard mode then route w,a,d,s to robot signals
            if(controlMode == Mode.Keyboard)
            {
                char temp = (char)e.KeyValue;
                bubblesHardware.calcMovementsViaChar(temp);
            }
            else if(controlMode == Mode.Command)
            {
                if(e.KeyValue == 13)
                {
                    String text = commandText.Text;
                    commandText.Text = "";
                    bubblesHardware.calcMovementsViaCommand(text);
                }
            }
        }

        //this cycles every 100ms and will command the robot server
        private void Cycle_Tick(object sender, EventArgs e)
        {
            if (controlMode == Mode.Joystick)
            {
                //command server
                bubblesHardware.calcMovementsViaJoystick(joystick);
                joyXlabel.Text = "X = " + joystick.getX();
                joyYlabel.Text = "Y = " + joystick.getY();
            }
            else if (controlMode == Mode.Autonomous)
            {
                //command server
                bubblesHardware.calcMovementsViaAuton();
            }
        }

        //estop button is pressed
        private void button1_Click(object sender, EventArgs e)
        {
            bubblesHardware.estop();
        }

        //Opens the form for vision processing if the button is checked else if unckecked it closes the vision processing
        private void VisionProcessingCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            //if the box is checked then enable the vision thread
            if (VisionProcessingCheckBox.Checked)
            {
                //create vision processing form
                visionGUI = new VisionGUI();
                visionGUI.Show();
            }
            //if not checked then if the thread is running then kill it
            else
            {
                if (visionGUI != null)
                {
                    try
                    {
                        visionGUI.Close();
                        visionGUI = null;
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show("Vision GUI is currently unresponsive. Try to force close manualy.");
                    }
                }
            }
        }
    }
}
