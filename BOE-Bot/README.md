# BOE-Bot

Back when I was getting started with robotics in middle school / high school, I purchased the BOE-Bot kit as my introduction into microcontrollers. This repo is primarily for my archival purposes. The code itself is not well structured or maintained.

## Overview

BOE-Bot is an educational robotics kit that teaches fundamental circuit design and microcontroller programming. It is built around the Basic Stamp microcontroller, which is programmed in PBASIC and mounted on the Board of Education (BOE). The BOE provides:

- GPIO breakout for sensors and actuators
- Power regulation
- A breadboard for circuit prototyping
- Servo motor control

The kit includes a polished aluminum chassis, two continuous rotation servo motors for movement, and a variety of sensors for interactive behavior.

For a full write-up on my experiences with BOE-Bot, check out my blog post : https://www.half-built-robots.com/2025/02/23/next-steps-with-robotics-kits-parallax-boe-bot/

## Implementation

My specific code implementation loosely follows Rodney Brooks' subsumption architecture:

1. Light-Seeking Behavior – The highest priority routine that steers the robot toward brighter areas using phototransistor sensors.
2. Wall-Banger Routine – Engaged when light levels are too low or too high, prompting the robot to drive and turn upon collision.
3. Obstacle Avoidance – Whisker switches detect physical collisions, triggering evasive maneuvers.
4. Motor Control – The lowest-level behavior, handling pulse-width modulation (PWM) control of the servo motors.

Each behavior layer can subsumed by a higher-priority response, ensuring the robot reacts appropriately to its environment.

### Key Circuits

- Whisker Switches – Collision detection with simple mechanical switches.
- Phototransistors – Light sensors using an RC decay circuit to measure ambient brightness.
- LED Indicators – Visual cues for turning direction and status.
- Piezo Buzzer – Audible feedback using PWM frequency control.
- Continuous Rotation Servos – Movement controlled via PWM signals.

### Code & Schematic

This repository contains:

- Firmware – PBASIC code for BOE-Bot's behavior.
- Schematic Capture – Circuit diagrams for interfacing with BOE-Bot's sensors and actuators.

See the official Parallax BOE-Bot kit for more details on deployment.

## Reflections

I highly recommend starting robotics with pre-built kits that provide structured learning while enforcing constraints. However, for beginners today, I would suggest exploring an Arduino-based kit instead, as it offers a more modern and flexible learning path.