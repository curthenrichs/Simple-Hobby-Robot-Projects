using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

//This code was initally found on http://letsmakerobots.com/content/a-simple-emotional-agent but since it was posted on a publicly 
//available site it is fair use for personal projects like mine

//TODO need to import the coordinates into the coordinate grid/ need to create emotion array as well/ make it return the string of closest emotion
//Need to create a database for it to store its emotional pointers to its perception and also store previous emotion
//These will then be used to create a system that selects a new emotion
namespace Bubbles_Brain
{
    public class EmotionalAgent
    {
        private const double r = 5.0;
        public void calcAgent(double x_P, double y_A)
        {
            if (x_P < -r) x_P = -r; // limit the range of x_P and y_A
            else if (x_P > r) x_P = r;
            if (y_A < -r) y_A = -r;
            else if (y_A > r) y_A = r;
            
            double[,] emotion_coordinates = new double[2,9];
            // = {
            //{0.0,  0.0, r, - r, 0.0, r/sqrt(2.0), - r/sqrt(2.0), r/sqrt(2.0), - r/sqrt(2.0)}, // x-coordinate of training samples
            //{0.0,  r, 0.0, 0.0, -r, r/sqrt(2.0), r/sqrt(2.0), - r/sqrt(2.0), -r/sqrt(2.0)} // y- coordinate of training samples
            //};
            
            //char *emotions[] = {"neutral", "vigilant", "happy", "sad", "bored", "excited", "angry", "relaxed", "depressed"};
            int i_emotion;
            int closestEmotion;
            double MaxDiff;
            double MinDiff = Math.Sqrt(2.0) * r + r; //set MinDiff initially to maximum distance that can occure
            for (i_emotion = 0; i_emotion < 9; i_emotion++)
            {
                // compute Euclidean distances
                double Euclidian_distance = Math.Sqrt(Math.Pow((emotion_coordinates[0,i_emotion] - x_P),2.0) + Math.Pow((emotion_coordinates[1,i_emotion] - y_A),2.0));
                MaxDiff = Euclidian_distance;

                // find minimum distance 
                if (MaxDiff < MinDiff)
                {
                    MinDiff = MaxDiff;
                    closestEmotion = i_emotion;
                }
            }
        }
    }
}

/*
Before we write down the function, we declare the radius as a constant and assign a value to it:
 const float r = 5.0; 

The function might then look as follows:

void Emotional_agent(float x_P, float y_A) {
  if(x_P < - r) x_P = - r; // limit the range of x_P and y_A
  else if(x_P > r) x_P = r;
  if(y_A < - r) y_A = - r;
  else if(y_A > r) y_A = r;
  float emotion_coordinates[2][9] = {
    {0.0,  0.0, r, - r, 0.0, r/sqrt(2.0), - r/sqrt(2.0), r/sqrt(2.0), - r/sqrt(2.0)}, // x-coordinate of training samples
    {0.0,  r, 0.0, 0.0, -r, r/sqrt(2.0), r/sqrt(2.0), - r/sqrt(2.0), -r/sqrt(2.0)} // y- coordinate of training samples
  };
  char *emotions[] = {"neutral", "vigilant", "happy", "sad", "bored", "excited", "angry", "relaxed", "depressed"};
  byte i_emotion; 
  byte closestEmotion;
  float MaxDiff;
  float MinDiff = sqrt(2.0) * r + r; //set MinDiff initially to maximum distance that can occure
  for (i_emotion = 0; i_emotion < 9; i_emotion ++) { 
    // compute Euclidean distances
    float Euclidian_distance = sqrt(pow((emotion_coordinates[0][i_emotion] - x_P),2.0) + pow((emotion_coordinates[1][i_emotion] - y_A),2.0));
    MaxDiff = Euclidian_distance;
    // find minimum distance 
    if (MaxDiff < MinDiff) {
      MinDiff = MaxDiff;
      closestEmotion = i_emotion;
    }
  }
  Serial.println(emotions[closestEmotion]);
  Serial.println("");
}
 */