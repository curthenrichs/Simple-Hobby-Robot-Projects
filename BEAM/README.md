# BEAM Robots README

This repository contains information and KiCad schematic files for several BEAM robotics projects, including:

- Beetle
- Herbie
- NoBB
- Symet
- SymFlower

## About BEAM Robotics

BEAM (Biological, Electrical, Aesthetic, Mechanical) robotics is a philosophy pioneered by Mark Tilden that emphasizes simple, adaptive robots inspired by nature. These robots operate without traditional microcontrollers, instead relying on analog circuits and scavenged components to produce interesting behaviors.

For a detailed introduction and discussion on BEAM robotics, refer to my blog post here: https://www.half-built-robots.com/2025/02/23/my-intro-to-robots-beam-robotics/

## Robots Overview

### Beetle

A simple, tactile-switch-based robot that uses two motors and whisker sensors to navigate its environment. Originally designed by Jerome Demers, this project demonstrates basic behavior generation without microcontrollers.

### Herbie

A light-seeking (photovore) robot based on the LM386 op-amp. It uses photoresistors to detect light and adjust its motion accordingly.

### NoBB

A weekend project photovore similar to Herbie but built with salvaged components, including an LM380 op-amp. While functional, it exhibits drift due to mismatched motors.

### Symet

A solar-powered BEAM robot that moves periodically based on a solar engine circuit. Its movement pattern is determined by capacitor placement, making it a self-sustaining and visually interesting project.

### SymFlower

A modified version of a solar-powered toy, repurposed into a BEAM robot. It features a solar engine and two motors, with recent modifications improving its solar panel efficiency.

## Schematic Files

Each robot has its corresponding schematic files available in KiCad under its respective directory:

/Beetle
/Herbie
/NoBB
/Symet
/SymFlower

## Additional Resources

- Book Recommendation: Junkbots, Bugbots, and Bots on Wheels by David Hrynkiw and Mark Tilden
- Parts & Kits: Solarbotics