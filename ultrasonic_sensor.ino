const int tiltModulePin1 = 2; // First tilt sensor module
const int tiltModulePin2 = 3; // Second tilt sensor module (or mercury tilt sensor)
const int hgTiltPin = 4;      // Third tilt sensor (HG mercury tilt sensor)
const int buzzerPin = 8;     // Buzzer pin

void setup() {
  pinMode(tiltModulePin1, INPUT);
  pinMode(tiltModulePin2, INPUT);
  pinMode(hgTiltPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Read all sensor states
  int tiltState1 = digitalRead(tiltModulePin1);
  int tiltState2 = digitalRead(tiltModulePin2);
  int hgTiltState = digitalRead(hgTiltPin);

  // Assuming:
  // - Tilt Module: LOW when triggered
  // - Mercury Tilt Sensor: HIGH when triggered

  if (tiltState1 == HIGH || tiltState2 == HIGH || hgTiltState == HIGH) { 
    digitalWrite(buzzerPin, HIGH); // Turn on the buzzer
  } else {
    digitalWrite(buzzerPin, LOW);  // Turn off the buzzer
  }
}
