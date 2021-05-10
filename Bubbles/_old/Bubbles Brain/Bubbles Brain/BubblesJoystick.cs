using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AForge.Controls;

namespace Bubbles_Brain
{
    class BubblesJoystick
    {
        public bool joystickFound = false;
        public bool killThread = false;
        private Joystick joystick;
        private double x = 0;
        private double y = 0;
        private string data;

        //thread worker method
        public void run()
        {
            List<Joystick.DeviceInfo> lis = Joystick.GetAvailableDevices();

            if (lis != null)
            {
                try
                {
                    joystick = new Joystick(0);
                }
                catch (AForge.NotConnectedException e)
                {
                    joystick = null;
                }
            }

            while(!killThread)
            {
                //check to see if the joystick has valid identity
                if (!(joystick == null))
                {
                    //create a dataset instance
                    Joystick.Status status = joystick.GetCurrentStatus();
                    //extract x and y values and set joystick state
                    x = status.XAxis;
                    y = status.YAxis;
                    joystickFound = true;
                }
                else
                {
                    joystickFound = false;
                    x = 0;
                    y = 0;
                }
            }
        }

        //returns the string name of the controller
        public string getControllerName()
        {
            if (joystickFound)
            {
                AForge.Controls.Joystick.DeviceInfo dvinfo = joystick.Info;
                return dvinfo.Name;
            }
            else
            {
                return "";
            }
        }

        //gets the x coordinate from the controller
        public double getX()
        {
            return x;
        }

        //gets the y coordinate from the controller
        public double getY()
        {
            return y;
        }
    }
}
