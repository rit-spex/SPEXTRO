# SPEXTRO Scientific Payload
## SDL Payload Challenge - IREC 2019

### Revision History
| Revision | Date | Author(s) | Description |
| --- | --- | --- | --- |
| 1 | 9/14/2018 | Daniel Mitchell, Dylan Wager, Luc Chartier | Initialized Document - Created Structure |
-----

### Scientific Objectives

---
### Scientific Experiment Interface & Support

---
### Power
* At least 24 hours of runtime
* __ watts instantaneously (TBD)
* Redundant battery option
* Reverse polarity protection
* Thermal protection
* Parallel regulators
* Physical switch to enable power
* Physical switch does not disable power (MCU takes over)

---
### Communication
* Discrete Tx and Rx radios
* 1W transmission power
* 10Kbit/s (with factor of safety)

| Data | Rate (Hz) | Size (Bytes) | Bits/sec | Phase |
| - | - | - | - | - |
| Pitch/Roll/Yaw | 20 | 4 | 640 | UKN |
| Altitude | 5 | 2 | 80 | Main |
| GPS | 5 | 8 | 320 | Main, Science |
| Accel x/y/z | 5 | 3 | 104 | Unarmed |
| Science | 100 | 2 | 800 | Science |
| Status | 5 | 2 | 80 | Unarmed |
Continued...

---
### Data Acquisition
* Acceleration
* Magnetometer
* Altitude
* GPS

Continued...

---
### Actuation
* Parachute deployment from PCB
* Redundant parachute deployment
* Scientific Mixing??

---

### Tracking/Recovery
* Redundant frequency for tracking
* Buzzer
* Bright LEDs
* Bright parachute

---

### Computing Resources
* Watchdog Timer for power reset
* Nonvolatile memory

---

### Flight Software

---

### Size/Weight
* Cubesat standard
* 2U preferred, 3U acceptable
* 8.8lbs Minimum

---

### Structure
* RF Transparent
* Structurally rigid
* Components easily mountable inside
* Access internals with minimal effort

---

### Rocket Interface(s)
* Deployment detection
* Rocket armed detection?

---

### Ground Station
* Real-time updates from rocket/payload during mission
* Mobile & compact
* Directional receiver for additional range

---

### Environmental Protection
* High temps ~60C can be expected
* Conformal coating should be used for electronics
* Surface mount components for vibration resistance

---
