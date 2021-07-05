# Orion

I designed Orion during my undergrad. This was by far one of my more mechanical projects. I cut a custom base out of plywood, 3D printed an SLA bttery holder, 3D printed motor mounts for Vex motors, and 3D printed pulley / idlers, and gears for the drivetrain. I did all of this in Google Sketchup (which is not the right tool for the job!).

The firmware architecture is nearly identical to Roverbot, except a few things:
- Runs on an ESP8266
  - Hosts a simple website that allows a phone to act as a joystick.
- Differential drivetrain
- No autonomous mode
