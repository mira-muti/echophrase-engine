# echophrase-engine
A real-time call-and-response musical system built with Pure Data and Arduino.


EchoPhrase is an interactive musical system that listens to a performer’s input and generates a responsive phrase in real time.

Built using Pure Data (Pd) and Arduino, the system acts as a musical collaborator, capturing live input, detecting phrase boundaries, and producing algorithmically transformed responses.

- It bridges:
	•	🎹 Human performance
	•	⚙️ Real-time signal processing
	•	🎛️ Hardware-based interaction

⸻

- Features
	•	Real-time call & response
	•	Phrase capture + replay system
	•	Algorithmic transformation modes
	•	Mirror (direct reflection)
	•	Answer (contour-based variation)
	•	Hardware control via Arduino
	•	Potentiometer (volume / timbre)
	•	Buttons (mode switching, tempo, reset)
	•	Dynamic sound synthesis
	•	Sine + phasor blending
	•	Envelope shaping
	•	Filter control (brightness)

⸻

- How It Works

1. Input Layer
	•	MIDI keyboard → pitch + timing
	•	Arduino → physical controls (serial input)

2. Logic Layer
	•	Stores phrases using indexed buffers
	•	Detects phrase end (silence threshold)
	•	Applies transformation logic

3. Audio Layer
	•	Generates sound via:
	•	osc~ (sine)
	•	phasor~ (bright tone)
	•	Shapes sound using:
	•	line~ envelopes
	•	lop~ filtering


- System Architecture

The system is modular:
	•	Input / Capture → MIDI + Arduino
	•	Storage / Logic → phrase buffers + sequencing
	•	Audio Engine → synthesis + effects

This modular design allowed for:
	•	easier debugging
	•	isolated iteration
	•	scalable extensions


Setup

-> Requirements
	•	Pure Data (PlugData / Purr Data recommended)
	•	Arduino Uno
	•	MIDI keyboard (or Pd keyboard object)

-> Hardware
	•	Potentiometer (A0)
	•	4 push buttons
	•	Breadboard + jumper wires

-> Run
	1.	Upload Arduino code
	2.	Open Pd patch
	3.	Start DSP
	4.	Open serial port:

      [open 5]
      |
      [comport 5 115200]

🎥 Demo


- Challenges

Serial Communication
	•	Mixed data streams caused parsing issues
→ Solved using value ranges + [moses]

Timing Synchronization
	•	Response lag / jitter
→ Optimized scheduling and delays

Phrase Detection
	•	System responded too early
→ Implemented silence-based trigger

Scheduler Bug
	•	Output lagged by one tick
→ Fixed using [del 0]

Potentiometer Routing
	•	Conflicts between UI and hardware input
→ Introduced clean source selection system

⸻

- Future Improvements
	•	Polyphonic responses
	•	Smarter harmonic transformations
	•	MIDI output support
	•	Visual UI feedback
	•	Multi-user / network interaction

⸻

- Tech Stack
	•	Pure Data (Pd)
	•	Arduino (C++)
	•	Serial Communication (USB)
	•	Real-time audio synthesis

⸻

- References
	•	Pure Data Documentation
	•	Arduino Official Examples
	•	Pd Forums & Open-Source Patches

⸻

- Author

Mira Muti
McGill University — MUMT 306
