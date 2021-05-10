# Bubbles
Bubbles is a dog toy converted into a robotic platform.

![Picture of a robotic dog toy with arduino attached. Its really cute by the way. UwU](./Main-Img.jpg?raw=true)

# Design
After building roverbot, I moved on to a dog toy that was being thrown away. The batteries installed in it had leaked onto the fur making not just an unappealing toy but also an unsafe one. The first order of buisness was to skin the toy out in the garage (not sure what the neighbors were thinking when they walked past).

Unlike roverbot where I replaced all of the electronics, I instead wanted to hack an arduino ontop of the existing controls. This lead to a three layer architecture:
- Hardware ~ Provides low-level movment and dog toy behavior.
- Arduino ~ Takes the place of the leash remote that came with the toy, affords wall-banger routine.
- PC ~ Teleoperated control with commands issued over XBEE radio.

**This project is on pause for the forseeable future, though I do intend to get back to it.**

## Hardware
Bubbles came into my life with several capacitive touch sensors on its body that cause various animations to be played. Likewise, he has a photodiode on his head that detects nearby movement to play an animation. The animations consist of head movmement, torso rotation (for turing), drive motor activation (to move forward/reverse and/or to move the tail). On teardown all actions are done with two motors and clever gearing. There is also a speaker that plays barking sounds during animation.

Bubbles also came with a leash that could be plugged into the toy. This leash had several buttons to manually steer the robot. However, the low-level control seems to take the commands as suggestion instead of strictly following them. That is, Bubbles would occasionally play animations or forget it was being commanded.

Lastly, I had to remove the existing battery pack as the electrodes were corroded beyond repair. I stayed with a four C-battery configuration as it was originally.

## Arduino
I mounted the Arduino to the rear of Bubbles along with a relay sheild and XBee breakout board. The relay sheild was wired up to mimic the leash controls. This configuration worked to initially move bubbles but it had the same problems as the original leash. I then built a custom motor drive board that took in the raw motor controls from the low-level hardware and conditionally passed it to the the motor depending on control mode. As for the firmware, this codebase inherits from [Roverbot's state-machine](https://github.com/curthenrichs/Roverbot), primarily due to Bubble's turnable drivetrain.

## PC
I started development of a basic webserver to provide teleoperated control of Bubbles. This peice of the project was the least developed.

# Fork Notes
This repo is forked from an alt account that I intend to delete in the near future.
