# Roverbot
I built roverbot as the next step after working with kits and building simple robots.

At its base is an RC car chassis and drivetrain. I removed the electronics and replaced the steering assembly with an standard RC servo motor. To control the robot I used an Arduino Uno with a motor shield. For sensing, I attatched an ultrasonic sensor on a servo and attached a low-fidelity wheel encoder (LED + Phototransistor). The code is built around a single state-machine that produces "wall-banger" behavior.

More recently I added an OLED display to provide some state information in order to diagnose its behavior. I also added an I2C accelerometer for additional output though not doing anything behavior-wise with it. Lastly, changed the ultrasonic sensor as the old one died after moving across the country.

This repositiory is primarily used for archival purposes. This code is minimally being maintained. There are some not-so-great design choices and coding practices that I just don't care to fix as it "just works".
