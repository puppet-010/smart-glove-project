# Gesture Definition

This document describes the first gesture recognition logic currently implemented in the smart glove project.

## 1. Current Gesture Demo

The current prototype implements a first shooting-style gesture demo.

This gesture is intended as a proof of concept showing that the glove can combine:
- finger posture detection from the flex sensors,
- motion detection from the IMU module.

## 2. General Logic

The gesture detection is based on two conditions:

1. **A predefined finger posture must be detected**
2. **A dynamic hand motion must be detected by the IMU**

Only when both conditions are satisfied is the gesture considered valid.

## 3. Finger Posture Condition

The first step is to check whether the hand matches the target posture defined in the code.

The implementation uses a specific combination of bent and extended finger states to identify the shooting-style hand position. This posture is derived from the two-state classification of the five flex sensors.

Because the project is still in a prototype phase, the exact finger-to-sensor mapping may still be refined in future integrated versions. However, the current code already provides a working posture-detection stage.

## 4. Motion Condition

Once the correct hand posture is detected, the system checks whether a dynamic motion corresponding to the gesture occurs.

The IMU is used to detect this movement through acceleration and gyroscope data. In the current implementation, the gesture is triggered when the measured motion exceeds predefined thresholds, representing a shooting-style action or recoil-like movement.

## 5. Cooldown Logic

A cooldown delay is included between two consecutive detections.

This prevents repeated triggering caused by the same movement or by rapid oscillations immediately after the gesture.

## 6. Current Role of This Gesture

The current shooting-style gesture should be understood as a first working demonstration rather than a final complete gesture library.

Its purpose is to validate the following points:
- the five-finger sensing system works in practice,
- the IMU data can be integrated into the logic,
- a combined posture + motion gesture can be recognized successfully.

## 7. Future Extensions

Future versions of the project may include:
- additional gesture definitions,
- better posture discrimination,
- more precise motion interpretation,
- improved mapping consistency between sensors and finger names,
- application of the glove to robot control or other interaction systems.
