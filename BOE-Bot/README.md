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

## Fork Notes
This repo was forked from my alt github account that I am going to be deleting soon.
