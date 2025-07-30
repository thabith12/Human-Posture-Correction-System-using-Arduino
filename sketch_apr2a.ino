#include <NewPing.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define TRIGGER_PIN1 2
#define ECHO_PIN1 3
#define TRIGGER_PIN2 4
#define ECHO_PIN2 5
#define MAX_DISTANCE 200 // Maximum distance for ultrasonic sensors (in cm).

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET_PIN 9 // Reset pin
#define OLED_DC 10       // Data/Command pin
#define OLED_CS 8        // Chip Select pin

#define ALARM_PIN 7
#define IR_SENSOR_PIN 6 // IR sensor input pin

NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE);
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE);

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET_PIN);

void setup() {
  pinMode(ALARM_PIN, OUTPUT);
  pinMode(IR_SENSOR_PIN, INPUT);

  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for the OLED
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Loop forever if initialization fails
  }

  display.display();
  delay(2000); // Pause for 2 seconds
  display.clearDisplay();
}

void loop() {
  int distance1 = sonar1.ping_cm();
  int distance2 = sonar2.ping_cm();
  bool isObjectDetected = digitalRead(IR_SENSOR_PIN) == LOW; // Assuming LOW means object detected

  bool alarmCondition = (!isObjectDetected || (distance1 > 10 || distance2 > 10));

  if (alarmCondition) {
    digitalWrite(ALARM_PIN, HIGH); // Turn on the alarm
    displayMessage("Wrong");
  } else {
    digitalWrite(ALARM_PIN, LOW); // Turn off the alarm
    displayMessage("Correct");
  }

  delay(100); // Wait for 100 milliseconds
}

void displayMessage(String message) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);
  display.println(message);
  display.display();
}
