# Smart Glove Project

A smart glove project based on five flex sensors and one IMU module for finger bending detection, hand motion sensing, and simple gesture recognition.

## Project Overview

This project was developed to build a wearable glove system capable of detecting the bending state of all five fingers and the motion of the hand. The glove combines flex sensors for finger tracking and an IMU module for hand orientation and acceleration measurement.

The system is designed as a practical prototype that can be used for gesture-based interaction and future control applications.

## Main Functions

- Detection of the bending state of five fingers
- Measurement of hand angle and acceleration using an IMU module
- Integration of sensor data into one wearable glove system
- Recognition of a first working gesture

## Current Working Result

At the current stage, the glove is fully functional.

The five flex sensors can detect the bending states of the five fingers. Four finger sensors are mounted on the back of the hand structure, while the fifth finger sensor is connected with a dedicated support solution adapted to its position.

In addition, the IMU module is used to detect the orientation and acceleration of the hand. This allows the glove not only to detect static finger positions, but also to include dynamic hand motion in the interaction logic.

A first gesture has already been implemented successfully. The working gesture is inspired by a military-style forward command: a hand sign similar to a pointing gesture, followed by two short forward motions. This result demonstrates that the glove can already be used for simple gesture recognition.

## Hardware Architecture

The system mainly includes:

- 5 flex sensors for finger bending detection
- 1 IMU module for hand motion sensing
- 1 microcontroller board for data acquisition and processing
- A glove structure with sensor supports and mechanical fixing elements
- A dedicated mounting solution for the thumb/fifth finger sensor

## Sensor Placement

The finger sensing system is based on five flex sensors.

- Four sensors are positioned on the back of the hand structure for four fingers
- The fifth finger sensor uses a dedicated connection and support method
- The IMU module is installed on the glove to capture hand angle and acceleration

This arrangement allows the system to combine finger posture detection with global hand motion sensing.

## Mechanical Design

The glove is not only an electronics project, but also a mechanical integration project.

A dedicated structure was designed to support the sensors and fix them in stable positions on the glove. CAD/mechanical design files are included in this repository to document the structure and the assembly logic.

The design was made to ensure:
- stable sensor placement
- good integration on the hand
- easy adjustment and future extension

## Repository Structure

- `firmware/` → code for flex sensor tests, IMU tests, integrated system, and gesture demo
- `hardware/` → wiring information, sensor placement, and component details
- `mechanical/` → CAD files and assembly notes
- `docs/` → calibration notes, system description, and test results
- `media/` → photos, videos, and screenshots of the project

## Demonstration Material

This repository also includes:
- project photos
- demonstration videos
- screenshots of test outputs

These materials are used to show that the glove has been physically built and tested successfully.

## Future Improvements

Possible future extensions include:

- recognition of more gestures
- improved calibration for each finger
- more advanced motion interpretation
- wireless communication
- use of the glove for robot control or other interactive applications

## Contributors

This project was developed as a team project.

Contributors will be added here.
