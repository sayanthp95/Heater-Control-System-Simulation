const int potPin = 34;

// State LEDs
const int idleLEDPin        = 13;
const int heatingLEDPin     = 12;
const int stabilizingLEDPin = 14;
const int targetLEDPin      = 27;
const int overheatLEDPin    = 26;

// Heater and Buzzer
const int heaterPin = 25;
const int buzzerPin = 33;

const float T_IDLE       = 25.0;
const float T_HEATING    = 60.0;
const float T_STABILIZE  = 65.0;
const float T_TARGET     = 70.0;

enum State { IDLE, HEATING, STABILIZING, TARGET_REACHED, OVERHEAT };
State state = IDLE;
float temperature = 0.0;

unsigned long lastUpdate = 0;
unsigned long lastLog = 0;

void setup() {
  Serial.begin(115200);

  pinMode(idleLEDPin, OUTPUT);
  pinMode(heatingLEDPin, OUTPUT);
  pinMode(stabilizingLEDPin, OUTPUT);
  pinMode(targetLEDPin, OUTPUT);
  pinMode(overheatLEDPin, OUTPUT);
  pinMode(heaterPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void updateLEDs(State currentState) {
  digitalWrite(idleLEDPin,        currentState == IDLE);
  digitalWrite(heatingLEDPin,     currentState == HEATING);
  digitalWrite(stabilizingLEDPin, currentState == STABILIZING);
  digitalWrite(targetLEDPin,      currentState == TARGET_REACHED);
  digitalWrite(overheatLEDPin,    currentState == OVERHEAT);
}

void controlHeater(State currentState) {
  if (currentState == HEATING || currentState == STABILIZING) {
    digitalWrite(heaterPin, HIGH);  // Heater ON
  } else {
    digitalWrite(heaterPin, LOW);   // Heater OFF
  }
}

void controlBuzzer(State currentState) {
  if (currentState == OVERHEAT) {
    digitalWrite(buzzerPin, HIGH); // Buzzer ON
  } else {
    digitalWrite(buzzerPin, LOW);  // Buzzer OFF
  }
}

void loop() {
  unsigned long now = millis();

  // Every 500 ms: Read temperature and update state
  if (now - lastUpdate >= 500) {
    lastUpdate = now;

    int raw = analogRead(potPin);
    temperature = (raw / 4095.0) * 100.0;

    if (temperature > T_TARGET)          state = OVERHEAT;
    else if (temperature >= T_STABILIZE) state = TARGET_REACHED;
    else if (temperature >= T_HEATING)   state = STABILIZING;
    else if (temperature >= T_IDLE)      state = HEATING;
    else                                 state = IDLE;

    updateLEDs(state);
    controlHeater(state);
    controlBuzzer(state);
  }

  // Every 1 sec: Serial log
  if (now - lastLog >= 1000) {
    lastLog = now;
    const char* states[] = { "Idle", "Heating", "Stabilizing", "Target Reached", "Overheat" };
    Serial.printf("Temp: %.1f°C | State: %s | Heater: %s | Buzzer: %s\n",
                  temperature,
                  states[state],
                  (digitalRead(heaterPin) ? "ON" : "OFF"),
                  (digitalRead(buzzerPin) ? "ON" : "OFF"));
  }
}
