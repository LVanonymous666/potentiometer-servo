#include <NanitLib.h>
#include <Servo.h>
#include <LinkedList.h>

byte potentiometer = P4_1;
Servo myServo;
byte button = P3_4;
byte greenLedPin = P4_3;
byte redLedPin = P4_4;
LinkedList<int> angles;

void setup() {
  Nanit_Base_Start();
  myServo.attach(P4_2);
  pinMode(button, INPUT_PULLUP);
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  initiateServoPosition();
}

void loop() {
  getPotentiometerValues();
  delay(50);
  rotateServo();
  angles.clear();
  delay(100);

}

void getPotentiometerValues() {
  turnOnLight(0, 255);
  while (digitalRead(button) == 1) {
    int angle = map(analogRead(potentiometer), 0, 1023, 0, 180);
    if(angles.size() == 1 && abs(angles.get(0) - angle) < 10) {
      continue;
    }
    angles.add(angle);
    delay(50);
  }
}

void rotateServo(){
  turnOnLight(255, 0);
  for (int i = 0; i < angles.size(); i++) {
    myServo.write(angles.get(i));
    delay(50);
  }
}

void initiateServoPosition() {
  turnOnLight(255, 0);
  int angle = map(analogRead(potentiometer), 0, 1023, 0, 180);
  myServo.write(angle);
  delay(100);
}

void turnOnLight(byte redValue, byte greenValue) {
  digitalWrite(redLedPin, redValue);
  digitalWrite(greenLedPin, greenValue);
}
