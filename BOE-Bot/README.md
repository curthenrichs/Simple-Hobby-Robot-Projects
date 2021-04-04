# BOE-Bot
Back when I was getting started with robotics in middle school / high school, I
purchased the BOE-Bot kit as my introduction into microcontrollers. This repo is primarily
for my archival purposes. The code itself is not well structured or maintained.

![Picture showing BOE-bot, Basic Stamp robot](./boe-bot.jpg?raw=true)

## Implementation
My specific code implementation loosely follows the ideas of Rodney Brooks
subsumption architecture. At the highest level is the light seeking routine. Then
at a mid-level (when the light level is too low) is a simple wall-banger routine.
And of course at the lowest level is the basic motor behavior.

See [kit](https://www.parallax.com/product/boe-bot-robot-kit-usb/) for details on
deployment. I highly recommend starting robotics with pre-built kits that place
constraints on the learner. However, I would recommend an Arduino based kit
instead.
