# RoverBot

RoverBot is a custom Arduino-based robot built from an RC car chassis, featuring:

- Arduino Uno with a motor shield for drivetrain control
- Servo-based steering replacing the original turning assembly
- Ultrasonic sensor on a servo for obstacle detection
- Wheel encoder (LED + phototransistor) for speed measurement
- OLED display & I2C accelerometer for diagnostics

This repository is for archival purposes. The code is minimally maintained. 

Code architecture follows a state-machine-based autonomy implementing a wall-banger behavior with closed-loop speed adjustments.

For more details, check out the in-depth blog post: https://www.half-built-robots.com/2025/03/02/building-roverbot-an-arduino-based-robot/

## Hardware Overview

- Base: RC car chassis with custom servo steering
- Electronics: Arduino stackup with motor shield & prototyping board
- Sensors: Ultrasonic for obstacle avoidance, encoder for speed, accelerometer for potential future use
- Power: 9V for electronics & servos, 4xAA for drivetrain

## Software Highlights

- State Machine: Controls navigation, obstacle avoidance, and turning decisions
- Hardware Abstraction Layer (HAL): Decouples low-level hardware control from high-level logic
- Speed Controller: Uses encoder feedback to adjust PWM for different surfaces
- OLED Display: Shows diagnostic info including state codes, sensor data, and motor status

## Future Improvements (if I get around to it)

- Integrate accelerometer into the control loop
- Improve stuck detection with additional sensors
- Refactor OLED driver for a better GUI structure