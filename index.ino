#include <Arduino.h>
#include "Motor.h"
#include "SpeedSensor.h"
// #include "Control.h"

Motor leftMotor(5, 4);
Motor rightMotor(6, 7);

SpeedSensor leftSensor(2);
SpeedSensor rightSensor(3);

// const int leftAnalogSensorPin = A0;
// const int rightAnalogSensorPin = A1;

void setup() {
    Serial.begin(9600);
    leftMotor.init();
    leftSensor.init();
}

void loop() {
    // int leftAnalogSensorValue = analogRead(leftAnalogSensorPin);
    // int rightAnalogSensorValue = analogRead(rightAnalogSensorPin);

    for (size_t i = 0; i < 255; i+=5)
    {
        leftMotor.setSpeed(i, true);
        delay(200);
        Serial.println(leftSensor.getSpeed());
    }

    for (size_t i = 255; i > 0; i-=5)
    {
        leftMotor.setSpeed(i, true);
        delay(200);
        Serial.println(leftSensor.getSpeed());
    }

    delay(1000);

    for (size_t i = 0; i < 255; i+=5)
    {
        leftMotor.setSpeed(i, false);
        delay(200);
        Serial.println(leftSensor.getSpeed());
    }

    for (size_t i = 255; i > 0; i-=5)
    {
        leftMotor.setSpeed(i, false);
        delay(200);
        Serial.println(leftSensor.getSpeed());
    }

    delay(1000);
}