# Lego Mindstorms NXT
Back when I started learning robotics, I purchased a few robotics kits that helped me in that journey. The LEGO Mindstorms NXT 2.0 kit was one of them, and I found it to be a fun and educational introduction to programming and robotics. This repository is primarily for archival purposes, and the code is not actively maintained.

## Overview

LEGO Mindstorms is a robotics kit designed for beginners to learn STEM concepts, programming, and robotics principles. The NXT 2.0 version, which I used, features:

- NXT Brick – A programmable microcontroller with support for motors and sensors.
- NXT-G – A graphical programming environment.
- Ultrasonic Sensor – Used for basic obstacle detection.
- Servo Motors – Provide controlled movement.
- Touch, Light, and Sound Sensors – Expand interactive capabilities.

For a detailed breakdown of my experience with the LEGO Mindstorms kit, check out my blog post : https://www.half-built-robots.com/2025/02/23/next-steps-with-robotics-kits-lego-mindstorms/

## Beta Rex – My Humanoid Robot

The specific project I am preserving here is Beta Rex, a humanoid walker based on the Alpha Rex design provided by LEGO. I made some modifications (e.g., repositioning the light sensor) and incremented the version to Beta Rex.

### Behavior & Programming

Beta Rex operates under a wall-banger routine, meaning it:

1. Walks forward using a cyclic weight-shifting gait.
2. Detects obstacles with the ultrasonic sensor.
3. Scans left and right, determining the clearer path.
4. Turns accordingly, then repeats the cycle.
5. Blinks LED colors for aesthetic effect.

This behavior is implemented in NXT-G and follows a basic subsumption architecture, where:

- The primary behavior track controls movement and sensors.
- A secondary track handles LED toggling.

### Code Structure

- Main Loop: Governs walking and collision detection.
- Decision Logic: Compares left/right distances to choose the best turn direction.
- Motor Control: Executes turns and forward steps.
- LED Effects: Simple visual feedback.

### Code & Repository

This repository contains:

- Beta Rex NXT-G Code – The archived visual programming project.

## Reflections

LEGO Mindstorms was a fantastic first step into robotics, offering a structured and engaging learning experience. However, as projects grow in complexity, the limitations of visual programming become apparent. Later, I explored BOE-Bot and Arduino-based robots for a more flexible programming experience. You can read about my transition in my BOE-Bot writeup.