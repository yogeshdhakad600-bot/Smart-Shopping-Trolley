/*
  Smart Shopping Trolley — ESP8266 starter firmware
  Current scope: IR input + 3 ultrasonic distance sensors + L298N motor driver.
  RFID billing and mobile app are NOT implemented in this sketch.

  SAFETY:
  - Treat this as starter code, not a certified safety controller.
  - Test with wheels lifted and motor supply disconnected first.
  - HC-SR04 ECHO is commonly 5 V: use a divider/level shifter so ESP8266 GPIO
    never receives more than 3.3 V.
  - Verify pin mapping against the actual board. ESP8266 boot-strap pins can
    prevent boot if attached modules hold them at the wrong level.
  - Use a physical emergency-stop circuit that interrupts motor power.
*/

#include <Arduino.h>

// PROVISIONAL NodeMCU pin mapping. Verify before wiring.
// Motor driver inputs:
const uint8_t IN1 = D1;
const uint8_t IN2 = D2;
const uint8_t IN3 = D5;
const uint8_t IN4 = D6;

// One shared TRIG pin; ECHO pins are separate.
// D3 and D4 are boot-strap pins: attached sensor states may affect boot.
// If boot is unreliable, change the pin plan or add suitable I/O expansion.
const uint8_t TRIG_PIN = D7;
const uint8_t ECHO_FRONT = D0;
const uint8_t ECHO_LEFT  = D3;
const uint8_t ECHO_RIGHT = D4;

// D8 is also a boot-strap pin. Check the IR module's output level at startup.
const uint8_t IR_PIN = D8;

// Tune only after controlled testing. These are initial demo values, not safety-certified.
const float STOP_DISTANCE_CM = 25.0;
const float CAUTION_DISTANCE_CM = 45.0;
const unsigned long ECHO_TIMEOUT_US = 25000UL;

enum Motion { STOPPED, FORWARD, TURN_LEFT, TURN_RIGHT };
Motion currentMotion = STOPPED;

float readDistanceCm(uint8_t echoPin) {
  // Trigger sensors sequentially to reduce ultrasonic cross-talk.
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(3);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH, ECHO_TIMEOUT_US);
  if (duration == 0) return -1.0; // invalid / no echo
  return (duration * 0.0343f) / 2.0f;
}

bool invalidDistance(float d) {
  return d < 0.0f || d > 450.0f;
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  currentMotion = STOPPED;
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  currentMotion = FORWARD;
}

void turnLeft() {
  // Simple differential turn. Verify motor wiring/direction on your chassis.
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  currentMotion = TURN_LEFT;
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  currentMotion = TURN_RIGHT;
}

void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_FRONT, INPUT);
  pinMode(ECHO_LEFT, INPUT);
  pinMode(ECHO_RIGHT, INPUT);
  pinMode(IR_PIN, INPUT);

  digitalWrite(TRIG_PIN, LOW);
  stopMotors();

  Serial.println();
  Serial.println(F("Smart Shopping Trolley ESP8266 starter"));
  Serial.println(F("RFID billing and mobile app are not implemented."));
}

void loop() {
  // Sequential measurements help reduce cross-talk.
  float front = readDistanceCm(ECHO_FRONT);
  delay(35);
  float left = readDistanceCm(ECHO_LEFT);
  delay(35);
  float right = readDistanceCm(ECHO_RIGHT);
  delay(35);

  int irState = digitalRead(IR_PIN);

  Serial.print(F("IR=")); Serial.print(irState);
  Serial.print(F(" front=")); Serial.print(front);
  Serial.print(F(" left=")); Serial.print(left);
  Serial.print(F(" right=")); Serial.println(right);

  // Fail safe: if any required distance reading is invalid, stop.
  if (invalidDistance(front) || invalidDistance(left) || invalidDistance(right)) {
    stopMotors();
    delay(100);
    return;
  }

  // Stop if an obstacle is critically close in any monitored direction.
  if (front <= STOP_DISTANCE_CM || left <= STOP_DISTANCE_CM || right <= STOP_DISTANCE_CM) {
    stopMotors();
    delay(100);
    return;
  }

  // Basic example only: IR module output polarity varies by model.
  // This assumes HIGH means the tracking input is detected.
  // Confirm this with Serial Monitor and change if your sensor is active LOW.
  bool targetDetected = (irState == HIGH);

  if (!targetDetected) {
    stopMotors();
    delay(100);
    return;
  }

  // Basic obstacle response. This is not person tracking: the IR sensor
  // does not provide reliable left/right human position by itself.
  if (front <= CAUTION_DISTANCE_CM) {
    if (left > right && left > CAUTION_DISTANCE_CM) {
      turnLeft();
    } else if (right > CAUTION_DISTANCE_CM) {
      turnRight();
    } else {
      stopMotors();
    }
  } else {
    moveForward();
  }

  delay(80);
}
