#include <Servo.h>

Servo servoThumb;
Servo servoIndex;
Servo servoMiddle;
Servo servoRing;
Servo servoPinky;

const int thumbPin = 3;
const int indexPin = 5;
const int middlePin = 6;
const int ringPin = 9;
const int pinkyPin = 10;

void setup() {
  Serial.begin(9600);
  
  servoThumb.attach(thumbPin);
  servoIndex.attach(indexPin);
  servoMiddle.attach(middlePin);
  servoRing.attach(ringPin);
  servoPinky.attach(pinkyPin);

  servoThumb.write(90);
  servoIndex.write(90);
  servoMiddle.write(90);
  servoRing.write(90);
  servoPinky.write(90);

  Serial.println("Servo initialized and set to 90 degrees");
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    int positions[5];
    int index = 0;
    
    char *str = strtok(&data[0], ",");
    while (str != NULL && index < 5) {
      positions[index] = constrain(atoi(str), 0, 180);
      str = strtok(NULL, ",");
      index++;
    }

    servoThumb.write(positions[0]);
    servoIndex.write(positions[1]);
    servoMiddle.write(positions[2]);
    servoRing.write(positions[3]);
    servoPinky.write(positions[4]);

    Serial.print("Servo positions: ");
    Serial.print(positions[0]); Serial.print(", ");
    Serial.print(positions[1]); Serial.print(", ");
    Serial.print(positions[2]); Serial.print(", ");
    Serial.print(positions[3]); Serial.print(", ");
    Serial.println(positions[4]);
  }
} 
