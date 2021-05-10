using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Threading;
using AForge;
using AForge.Imaging;

//Things to experiemnt with  
// 1) color tacking dial in
// 2) motion tracking
// 3) face tracking/recognition

namespace Bubbles_Brain
{
    public class VisionProcessing
    {                         
        private Bitmap originalImage;
        private Bitmap toFormOriginal;
        private Bitmap postImage;
        private double x = 0, y = 0;
        private bool blobFound = false;
        private char trackColor = 'r';    // r,o,y,g,b,v think the rainbow struzeski its a rainbow  or u for the user defiend

        //constructor
        public VisionProcessing()
        {
            originalImage = null;
            postImage = null;
        }

        //the executable thread
        public void colorTrack()
        {
            //create the filters
            //blur filter
            AForge.Imaging.Filters.Blur blur = new AForge.Imaging.Filters.Blur();
            // blur.Divisor = 3;
            //filter for color <need the if else struct here to choose color
            AForge.Imaging.Filters.ColorFiltering colorFilter = new AForge.Imaging.Filters.ColorFiltering();
            //size filter
            AForge.Imaging.Filters.BlobsFiltering blobSizeFilter = new AForge.Imaging.Filters.BlobsFiltering();

            if (originalImage != null)
            {
                //create a temperary image to work on
                Bitmap tempImage = (Bitmap)originalImage.Clone();

                //blur it to make it easier to filter
                blur.ApplyInPlace(tempImage);

                //set colors to filter here
                switch (trackColor)
                {
                    case 'r': colorFilter.Red = new IntRange(80, 255);
                        colorFilter.Green = new IntRange(0, 50);
                        colorFilter.Blue = new IntRange(0, 50);
                        break;

                    case 'o': colorFilter.Red = new IntRange(120, 255);
                        colorFilter.Green = new IntRange(140, 213);
                        colorFilter.Blue = new IntRange(0, 50);
                        break;

                    case 'y': colorFilter.Red = new IntRange(213, 255);
                        colorFilter.Green = new IntRange(203, 239);
                        colorFilter.Blue = new IntRange(0, 51);
                        break;

                    case 'g': colorFilter.Red = new IntRange();
                        colorFilter.Green = new IntRange();
                        colorFilter.Blue = new IntRange();
                        break;

                    case 'b': colorFilter.Red = new IntRange();
                        colorFilter.Green = new IntRange();
                        colorFilter.Blue = new IntRange();
                        break;

                    case 'v': colorFilter.Red = new IntRange();
                        colorFilter.Green = new IntRange();
                        colorFilter.Blue = new IntRange();
                        break;

                    case 'u': colorFilter.Red = new IntRange();
                        colorFilter.Green = new IntRange();
                        colorFilter.Blue = new IntRange();
                        break;

                    default: colorFilter.Red = new IntRange(0, 255);
                        colorFilter.Green = new IntRange(0, 255);
                        colorFilter.Blue = new IntRange(0, 255);
                        break;
                }
                colorFilter.Red = new IntRange(100, 255);
                colorFilter.Green = new IntRange(0, 75);
                colorFilter.Blue = new IntRange(0, 75);


                colorFilter.ApplyInPlace(tempImage);

                //filter to get only larger blobs
                blobSizeFilter.MinHeight = 100;
                blobSizeFilter.MinWidth = 100;
                blobSizeFilter.ApplyInPlace(tempImage);

                //get the number of blobs
                AForge.Imaging.BlobCounter blobCounter = new BlobCounter(tempImage);
                Blob[] blobs = blobCounter.GetObjects(tempImage, true);

                //if there are no blobs
                if (blobs.Length == 0)
                {
                    //set defaults
                    x = 0;
                    y = 0;
                    blobFound = false;
                }
                //there are blobs
                else
                {
                    //set the cog so the world can see
                    AForge.Point cog = blobs[0].CenterOfGravity;
                    x = cog.X;
                    y = cog.Y;
                    blobFound = true;

                    //draw a cute picture of where it is tracking the blob
                    tempImage = drawCOGBlob(tempImage, blobs[0]);
                }

                //set the final image
                postImage = (Bitmap)tempImage.Clone();
            }

            //delay between cycles so as to not overconsume the procesor
            Thread.Sleep(100);
        }

        //draws a rectangle on the bitmap image
        public Bitmap drawCOGBlob(Bitmap tempImage, Blob blob)
        {
            Rectangle rect = new Rectangle(0, 0, tempImage.Width, tempImage.Height);
            System.Drawing.Imaging.BitmapData bmpData = tempImage.LockBits(rect, System.Drawing.Imaging.ImageLockMode.ReadWrite, tempImage.PixelFormat);
            AForge.Imaging.Drawing.Rectangle(bmpData, blob.Rectangle, Color.Blue);
            tempImage.UnlockBits(bmpData);
            return tempImage;
        }

        //sets the current image for processing
        public void setImage(Bitmap i)
        {
            originalImage = (Bitmap)i.Clone();
            toFormOriginal = (Bitmap)i.Clone();
        }

        //gets the current image preprocessing
        public Bitmap getOriginalImage()
        {
            return toFormOriginal;
        }

        //gets the post image
        public Bitmap getPostImage()
        {
            return postImage;
        }

        //sets the color to trackfor
        public void setColorTrack(char c)
        {
            trackColor = c;
        }

        //get the x coordinate for tracking the blob
        public double getBlobX()
        {
            return x;
        }

        //gets the y coordinate from tracked blob
        public double getBlobY()
        {
            return y;
        }

        //gets if there is a blob being tracked
        public bool isBlob()
        {
            return blobFound;
        }

        //gets the tracking color
        public char getTrackingColor()
        {
            return trackColor;
        }
    }
}
