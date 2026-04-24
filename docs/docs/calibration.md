
# Calibration and Sensing Logic

This document describes the reading method, filtering logic, and calibration values used for the smart glove project.

## 1. Reading Method

The flex sensors are read in analog mode rather than digital mode.

Each flex sensor is connected through a sensor module providing four pins: VCC, GND, AO, and DO. In this project, the analog output (AO) is used because it preserves more detailed information about finger bending and makes gesture interpretation more flexible.

For each sensor, the signal is not read only once. Instead, the system performs multiple consecutive analog readings and computes an average value. This helps reduce small fluctuations and provides a more stable measurement.

## 2. Filtering Method

A simple averaging filter is used in the current implementation.

For each flex sensor:
- 10 readings are taken
- a delay of 2 ms is inserted between samples
- the final value is the average of the 10 readings

This method is simple but effective for improving the stability of the raw sensor signal.

## 3. Why a Two-State Classification Was Chosen

At the beginning, a more detailed multi-state interpretation was considered.

In theory, flex sensors are sensitive enough to support finer distinctions of finger positions. However, in the real wearable configuration, the sensors do not remain in perfect contact with the hand all the time. Even after assembly, small gaps still exist between the hand and the sensor support structure.

As a result:
- the effective bending variation becomes relatively small,
- the measured values change quickly,
- the intermediate range is not always stable enough for consistent classification.

In practice, a three-state interpretation was less robust for the current prototype. For this reason, the final implementation uses a two-state classification:
- **Extended**
- **Bent**

This simplified logic gives more stable results for gesture recognition.

## 4. Finger Reference Values

The following table summarizes the current reference ranges measured for each finger.

| Finger | GPIO | Flat Value (approx.) | Bent Value (approx.) | Threshold |
|---|---:|---:|---:|---:|
| Index | 34 | 850–1000 | 50–100 | 200 |
| Middle | 35 | 1000–1150 | 60–120 | 250 |
| Ring | 32 | 1200–1400 | 150–250 | 300 |
| Thumb | 39 | 1650–1750 | 1150–1300 | 1350 |
| Pinky | 33 | 1500–1600 | 950–1200 | 1200 |

## 5. Threshold Interpretation

The current thresholds are finger-specific.

This means that each finger is calibrated independently instead of using one common threshold for all sensors. This choice is necessary because the sensors do not produce the same numerical range on every finger. In particular, the thumb and pinky operate in a significantly higher range than the other fingers.

The thresholds are currently used to convert the filtered analog readings into two discrete states:
- one state corresponding to the extended finger position,
- one state corresponding to the bent finger position.

## 6. Current Limitations

The current values provide a working solution for the prototype, but they are still dependent on:
- the mechanical fit of the glove,
- the way the glove is worn,
- the exact position of each sensor,
- the user’s hand shape and bending amplitude.

Because of these factors, the calibration may vary slightly between users or between mechanical revisions.

## 7. Possible Future Improvements

Possible improvements for future versions include:
- more precise per-user calibration,
- improved mechanical contact between the glove and the hand,
- better support for intermediate finger positions,
- adaptive thresholds,
- more advanced filtering and signal interpretation.

At the current stage, the chosen calibration logic is sufficient for stable operation of the first gesture recognition prototype.
