
const int RESPONSE_MODE_BUTTON_PIN = 2;  // leftmost button
const int POT_MODE_BUTTON_PIN      = 3;  // selects volume vs cutoff
const int TEMPO_MODE_BUTTON_PIN    = 4;  // cycles 4 tempo modes
const int RESET_BUTTON_PIN         = 5;  // reset
const int SHARED_POT_PIN           = A0; // main potentiometer

// LED pins for the two illuminated buttons
const int TEMPO_LED_PIN            = 9;
const int RESET_LED_PIN            = 10;

const unsigned long debounceDelay = 30;
const unsigned long potSendIntervalMs = 15;
const unsigned long resetFlashMs = 120;

// Serial event codes
const int RESPONSE_MODE_EVENT = 250;
const int POT_MODE_EVENT      = 251;
const int TEMPO_MODE_EVENT    = 252;
const int RESET_EVENT         = 253;

// Button debounce state
bool lastResponseReading = HIGH;
bool lastPotModeReading  = HIGH;
bool lastTempoReading    = HIGH;
bool lastResetReading    = HIGH;

bool stableResponseState = HIGH;
bool stablePotModeState  = HIGH;
bool stableTempoState    = HIGH;
bool stableResetState    = HIGH;

unsigned long lastResponseDebounceTime = 0;
unsigned long lastPotModeDebounceTime  = 0;
unsigned long lastTempoDebounceTime    = 0;
unsigned long lastResetDebounceTime    = 0;

// Pot state
int lastPotValue = -1;
unsigned long lastPotSendTime = 0;
const int potThreshold = 2;  // smaller threshold = smoother response

// Tempo mode memory for LED feedback
int tempoMode = 0;

// Reset LED flash state
bool resetLedActive = false;
unsigned long resetLedStartTime = 0;

void setup() {
  pinMode(RESPONSE_MODE_BUTTON_PIN, INPUT_PULLUP);
  pinMode(POT_MODE_BUTTON_PIN, INPUT_PULLUP);
  pinMode(TEMPO_MODE_BUTTON_PIN, INPUT_PULLUP);
  pinMode(RESET_BUTTON_PIN, INPUT_PULLUP);

  pinMode(TEMPO_LED_PIN, OUTPUT);
  pinMode(RESET_LED_PIN, OUTPUT);

  digitalWrite(TEMPO_LED_PIN, LOW);
  digitalWrite(RESET_LED_PIN, LOW);

  Serial.begin(115200);
  delay(300);

  updateTempoLed();
}

void loop() {
  handleResponseModeButton();
  handlePotModeButton();
  handleTempoModeButton();
  handleResetButton();
  handleSharedPot();
  updateResetLedFlash();
}

void handleResponseModeButton() {
  bool reading = digitalRead(RESPONSE_MODE_BUTTON_PIN);

  if (reading != lastResponseReading) {
    lastResponseDebounceTime = millis();
  }

  if ((millis() - lastResponseDebounceTime) > debounceDelay) {
    if (reading != stableResponseState) {
      stableResponseState = reading;
      if (stableResponseState == LOW) {
        Serial.write(RESPONSE_MODE_EVENT);
      }
    }
  }

  lastResponseReading = reading;
}

void handlePotModeButton() {
  bool reading = digitalRead(POT_MODE_BUTTON_PIN);

  if (reading != lastPotModeReading) {
    lastPotModeDebounceTime = millis();
  }

  if ((millis() - lastPotModeDebounceTime) > debounceDelay) {
    if (reading != stablePotModeState) {
      stablePotModeState = reading;
      if (stablePotModeState == LOW) {
        Serial.write(POT_MODE_EVENT);
      }
    }
  }

  lastPotModeReading = reading;
}

void handleTempoModeButton() {
  bool reading = digitalRead(TEMPO_MODE_BUTTON_PIN);

  if (reading != lastTempoReading) {
    lastTempoDebounceTime = millis();
  }

  if ((millis() - lastTempoDebounceTime) > debounceDelay) {
    if (reading != stableTempoState) {
      stableTempoState = reading;
      if (stableTempoState == LOW) {
        tempoMode = (tempoMode + 1) % 4;
        updateTempoLed();
        Serial.write(TEMPO_MODE_EVENT);
      }
    }
  }

  lastTempoReading = reading;
}

void handleResetButton() {
  bool reading = digitalRead(RESET_BUTTON_PIN);

  if (reading != lastResetReading) {
    lastResetDebounceTime = millis();
  }

  if ((millis() - lastResetDebounceTime) > debounceDelay) {
    if (reading != stableResetState) {
      stableResetState = reading;
      if (stableResetState == LOW) {
        Serial.write(RESET_EVENT);

        // Reset local hardware state too
        tempoMode = 0;
        updateTempoLed();

        digitalWrite(RESET_LED_PIN, HIGH);
        resetLedActive = true;
        resetLedStartTime = millis();
      }
    }
  }

  lastResetReading = reading;
}

void handleSharedPot() {
  if ((millis() - lastPotSendTime) < potSendIntervalMs) {
    return;
  }

  lastPotSendTime = millis();

  int rawPot = analogRead(SHARED_POT_PIN);      // 0..1023
  int mappedPot = map(rawPot, 0, 1023, 0, 127); // 0..127

  if (lastPotValue < 0 || abs(mappedPot - lastPotValue) >= potThreshold) {
    lastPotValue = mappedPot;

    // Send in a separate range so Pd can distinguish it from button events
    Serial.write((byte)(100 + mappedPot));
  }
}

void updateTempoLed() {
  // Simple readable behavior:
  // mode 0 -> off
  // mode 1/2/3 -> on
  // If you want 4 distinct LED patterns later, we can do that too
  if (tempoMode == 0) {
    digitalWrite(TEMPO_LED_PIN, LOW);
  } else {
    digitalWrite(TEMPO_LED_PIN, HIGH);
  }
}

void updateResetLedFlash() {
  if (resetLedActive && (millis() - resetLedStartTime >= resetFlashMs)) {
    digitalWrite(RESET_LED_PIN, LOW);
    resetLedActive = false;
  }
}