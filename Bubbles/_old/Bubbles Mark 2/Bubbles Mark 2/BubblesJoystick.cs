using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using AForge.Controls;

namespace Bubbles_Mark_2
{
    //This class implments a joystick from the Aforge library and combines that ability with the reading desired 
    //inorder for a fuly operational joystick system for bubbles
    class BubblesJoystick
    {
        //holds whether a joystick is found
        private bool joystickFound = false;
        //commanded to true when the run method needs to die
        public bool killThread = false;
        //the aforge joystick system we will use an xbox controller most likely
        private Joystick joystick = null;
        //x position of joystick
        private double x = 0.0;
        //y position of joystick
        private double y = 0.0;

        //method that is intended to be threaded
        public void run()
        {
            List<Joystick.DeviceInfo> list = Joystick.GetAvailableDevices();

            if(list != null)
            {
                try
                {
                    joystick = new Joystick(0);
                }
                catch(AForge.NotConnectedException e)
                {
                    joystick = null;
                }
            }

            while(!killThread)
            {
                //check to see if joystick is not null
                if(joystick != null)
                {
                    Joystick.Status status = joystick.GetCurrentStatus();
                    //extract x and y values
                    x = status.XAxis;
                    y = status.YAxis;
                    joystickFound = true;
                }
                else
                {
                    joystickFound = false;
                    x = 0.0;
                    y = 0.0;
                }
                Thread.Sleep(250);
            }
        }

        //Gets the String name of the controller
        public String getControllerName()
        {
            if(joystickFound)
            {
                Joystick.DeviceInfo dvingo = joystick.Info;
                return dvingo.ToString();
            }
            return "No Joystick Detected";
        }

        //Gets the x coordinate from joystick
        public double getX()
        {
            return x;
        }

        //gets y coordinate
        public double getY()
        {
            return y;
        }

        //is there a joystick connected
        public bool isJoystickFound()
        {
            return joystickFound;
        }
    }
}
