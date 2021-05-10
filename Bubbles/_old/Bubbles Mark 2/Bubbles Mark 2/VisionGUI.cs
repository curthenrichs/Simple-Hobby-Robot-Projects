using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Bubbles_Mark_2
{
    public partial class VisionGUI : Form
    {
        //==========================================================
        //               Enum and Field declaration
        //                    and Constructor
        //==========================================================
        public enum TrackOption { Red, Orange, Yellow, Green, Blue, Purple, User };
        private TrackOption currentOption;

        //default contructor
        public VisionGUI()
        {
            InitializeComponent();
            currentOption = TrackOption.Red;
        }

        //===========================================================
        //                    Color Selection 
        //===========================================================

        //red radio button is clicked
        private void RedOption_CheckedChanged(object sender, EventArgs e)
        {
            if (RedOption.Checked)
                currentOption = TrackOption.Red;
        }

        //orange radio button is clicked
        private void OrangeOption_CheckedChanged(object sender, EventArgs e)
        {
            if (OrangeOption.Checked)
                currentOption = TrackOption.Orange;
        }

        //yellow radio button is clicked
        private void YellowOption_CheckedChanged(object sender, EventArgs e)
        {
            if (YellowOption.Checked)
                currentOption = TrackOption.Yellow;
        }

        //green radio button is clicked
        private void GreenOption_CheckedChanged(object sender, EventArgs e)
        {
            if (GreenOption.Checked)
                currentOption = TrackOption.Green;
        }

        //blue radio button is clicked
        private void BlueOption_CheckedChanged(object sender, EventArgs e)
        {
            if (BlueOption.Checked)
                currentOption = TrackOption.Blue;
        }

        //purple radio button is clicked
        private void PurpleOption_CheckedChanged(object sender, EventArgs e)
        {
            if (PurpleOption.Checked)
                currentOption = TrackOption.Purple;
        }
        
        //user radio button is clicked
        private void UserOption_CheckedChanged(object sender, EventArgs e)
        {
            if (UserOption.Checked)
                currentOption = TrackOption.User;
        }

        //==================================================================
        //                      User Selected Color
        //==================================================================

        //user Min color selection
        private void userMinColorButton_Click(object sender, EventArgs e)
        {
            if (ColorDialog.ShowDialog() == DialogResult.OK)
            {
                //pull color out and set as rgb values in gui
                userMinRed.Text = "" + ColorDialog.Color.R;
                userMinGreen.Text = "" + ColorDialog.Color.G;
                userMinBlue.Text = "" + ColorDialog.Color.B;
            }
        }

        //user max color selection
        private void userMaxColorButton_Click(object sender, EventArgs e)
        {
            if (ColorDialog.ShowDialog() == DialogResult.OK)
            {
                //pull color out and set as rgb values in gui
                userMaxRed.Text = "" + ColorDialog.Color.R;
                userMaxGreen.Text = "" + ColorDialog.Color.G;
                userMaxBlue.Text = "" + ColorDialog.Color.B;
            }
        }

        //===================================================================
        //                    Image Passing and Mode Request
        //===================================================================

        //passes back the current tracking mode (useful for the tracting thread)
        public TrackOption getCurrentTrackingOption()
        {
            return currentOption;
        }

        //get the minimum color for user defiend color tracking
        public Color getUserMinColor()
        {
            try
            {
                int r = Convert.ToInt32(userMinRed.Text);
                int g = Convert.ToInt32(userMinGreen.Text);
                int b = Convert.ToInt32(userMinBlue.Text);
                Color minColor = Color.FromArgb(r, g, b);
                return minColor;
            }
            catch (Exception e)
            {
                throw new ArgumentException("Yeah something is not right");
            }
        }

        //get the maximum color for user defined color tracking
        public Color getUserMaxColor()
        {
            try
            {
                int r = Convert.ToInt32(userMaxRed.Text);
                int g = Convert.ToInt32(userMaxGreen.Text);
                int b = Convert.ToInt32(userMaxBlue.Text);
                Color maxColor = Color.FromArgb(r, g, b);
                return maxColor;
            }
            catch (Exception e)
            {
                throw new ArgumentException("Yeah something is not right");
            }
        }

        //pass new before picture
        public void setBeforeImage(Bitmap beforeImage)
        {
            BeforePictureBox.Image = (Bitmap)beforeImage.Clone();
        }

        //pass new after picture
        public void setAfterImage(Bitmap afterImage)
        {
            AfterPictureBox.Image = (Bitmap)afterImage.Clone();
        }
    }
}
