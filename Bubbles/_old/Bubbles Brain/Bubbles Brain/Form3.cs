using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;

namespace Bubbles_Brain
{
    public partial class Form3 : Form
    {
        private VisionProcessing vision = new VisionProcessing();

        public Form3()
        {
            InitializeComponent();
        }

        public void setOriginalImage(Bitmap b)
        {
            vision.setImage(b);
        }

        //close form as of now no need to do anything jurassic but if later then yeah
        private void Form3_FormClosing(object sender, FormClosingEventArgs e)
        {

        }

        //every tick update the pictures of the form
        //and run the vision processing system
        private void timer1_Tick(object sender, EventArgs e)
        {
            //run color tracking on vision
            vision.colorTrack();

            //update pictures
            pictureBox1.Image = vision.getOriginalImage();
            pictureBox2.Image = vision.getPostImage();
        }

        private void red_CheckedChanged(object sender, EventArgs e)
        {
            //if on
            if(red.Checked)
            {
                vision.setColorTrack('r');
            }
        }

        private void orange_CheckedChanged(object sender, EventArgs e)
        {
            //if on
            if(orange.Checked)
            {
                vision.setColorTrack('o');
            }
        }

        private void yellow_CheckedChanged(object sender, EventArgs e)
        {
            //if on
            if(yellow.Checked)
            {
                vision.setColorTrack('y');
            }
        }

        private void green_CheckedChanged(object sender, EventArgs e)
        {
            //if on
            if(green.Checked)
            {
                vision.setColorTrack('g');
            }
        }

        private void blue_CheckedChanged(object sender, EventArgs e)
        {
            //if on
            if(blue.Checked)
            {
                vision.setColorTrack('b');
            }
        }

        private void purple_CheckedChanged(object sender, EventArgs e)
        {
            //if on
            if(purple.Checked)
            {
                vision.setColorTrack('p');
            }
        }

        private void userSelectColor_CheckedChanged(object sender, EventArgs e)
        {
            //if on
            if(userSelectColor.Checked)
            {
                vision.setColorTrack('u');
            }
        }
    }
}
