# EchoPhrase
A Real-Time Call-and-Response Musical System (Pure Data + Arduino)

---

## Overview

EchoPhrase is an interactive musical system that captures a performer’s input and generates a responsive phrase in real time.

Built using Pure Data (Pd) and Arduino, the system functions as a musical collaborator. It listens to live input, detects phrase boundaries, and produces algorithmically transformed responses.

The project combines real-time audio synthesis, embedded hardware control, and algorithmic composition.

---

## Features

- Real-time call-and-response interaction
- Phrase capture and replay system
- Multiple response modes:
  - Mirror (direct reflection)
  - Answer (contour-based transformation)
- Hardware control via Arduino:
  - Potentiometer (volume or timbre)
  - Buttons (mode selection, tempo, reset)
- Dynamic sound synthesis:
  - Sine and phasor oscillators
  - Envelope shaping
  - Low-pass filtering

---

## System Architecture

The system is organized into three main components:

### Input and Capture
- MIDI keyboard input (pitch and timing)
- Arduino serial input (buttons and potentiometer)
- Data normalization and routing

### Logic and Sequencing
- Phrase storage using indexed buffers
- Phrase-end detection based on silence threshold
- Transformation logic for response generation

### Audio Engine
- Sound synthesis using osc~ and phasor~
- Envelope shaping using line~
- Timbre control via filtering

This modular structure enabled efficient debugging, testing, and iteration.

---

## Methodology

### Input Acquisition
- Arduino reads analog and digital inputs
- MIDI keyboard provides note input

### Data Transmission
- Arduino sends:
  - Potentiometer values (encoded range)
  - Button events (distinct event codes)
- Pure Data parses input using moses and normalization

### Control Mapping

The system supports multiple modes:

- Response Mode:
  - Mirror
  - Answer

- Pot Mode:
  - Volume control
  - Filter cutoff (timbre)

- Tempo Mode:
  - Four discrete timing presets

- Reset:
  - Clears phrase memory and resets system state

---

## Implementation

### Arduino
- Handles debouncing and input smoothing
- Maps analog input to usable ranges (0–127)
- Sends serial data at 115200 baud


### Pure Data

Core components:
- comport for serial input
- text objects for phrase storage
- metro and delay for timing
- line~ for amplitude envelopes
- osc~ and phasor~ for synthesis

### Potentiometer Routing
- Separation of sources:
  - physical_pot (Arduino)
  - virtual_pot (UI)
  - pot_value (final selected control)
- Mode-dependent routing using spigot

### Phrase Handling
- Notes stored with pitch, index, and timing
- Phrase-end detection triggers response playback


## Code

- [Pure Data Patch](echophrase-miramuti.pd)
- [Arduino Code](echophraseARDUINO/echophrase.ino)

  

## Running the Project

1. Upload the Arduino sketch from `arduino/echophrase.ino`
2. Open `pd/echophrase.pd` in Pure Data
3. Enable DSP
4. Open serial port:
   [open 5(
   |
   [comport 5 115200]
   

---

## Demo

Watch the system in action:
(check out the google drive documentation folder for a demo) 
https://drive.google.com/drive/folders/1qUv_cKbZUo1fq6ZDsoq7geZac_iTL-4m?usp=drive_link

Hardware vid added soon

---

## Challenges

### Serial Communication
Issue: mixed data streams caused parsing errors  
Solution: separated data ranges and used moses for routing

### Timing Synchronization
Issue: latency and inconsistent response timing  
Solution: optimized scheduling and reduced unnecessary processing

### Phrase Detection
Issue: system responded before performer finished playing  
Solution: implemented silence-based phrase-end detection

### Scheduler Delay
Issue: output lagged by one processing tick  
Solution: introduced del 0 to correct execution order

### Potentiometer Routing
Issue: conflicting control signals from UI and hardware  
Solution: implemented a unified pot_value signal with source selection

---

## Results

The system allows a performer to:

- Play a musical phrase
- Trigger an automated response after completion
- Modify sound characteristics in real time using hardware controls

Example use cases:
- Live improvisation with responsive system feedback
- Interactive installation for exploratory sound interaction

---

## Future Work

- Polyphonic response generation
- More advanced transformation algorithms (harmonic awareness)
- MIDI output support
- Visual interface for feedback and control
- Multi-user or networked interaction

---

## Tools and Resources

Software:
- Pure Data (PlugData / Purr Data)
- Arduino IDE

Hardware:
- Arduino Uno
- Potentiometer
- Push buttons
- Breadboard and wiring components

References:
- Pure Data documentation
- Arduino official examples
- Open-source Pd patches and online forums

---

## Author

Mira Muti  
McGill University – MUMT 306
