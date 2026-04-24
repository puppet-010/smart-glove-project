# Documentation

This folder contains supporting documentation for the smart glove project.

## Content

- calibration notes
- sensor interpretation logic
- gesture definition
- system architecture
- test results

## Sensor Logic and Gesture Demo

The glove uses five flex sensors to detect the bending state of the fingers and one IMU module to capture hand motion. In the current prototype, the finger signals are processed in analog mode and classified into two states: extended or bent.

A two-state logic was selected because it is more stable in the real wearable configuration. Although the flex sensors are sensitive enough for finer measurement, the actual bending variation becomes relatively small once the glove is worn, due to small gaps between the hand and the sensor support structure. In practice, a three-state interpretation was less stable, while a two-state interpretation gave more reliable results for gesture recognition.

The current demo also includes a first shooting-style gesture detection. This gesture combines a predefined finger posture with a motion condition detected by the IMU. Detailed calibration values and gesture logic are provided in the project documentation.
## Purpose

These documents explain how the glove was designed, calibrated, tested, and used for gesture recognition.
