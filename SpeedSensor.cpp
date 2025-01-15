#include "SpeedSensor.h"

SpeedSensor* SpeedSensor::leftSensorInstance = nullptr;
SpeedSensor* SpeedSensor::rightSensorInstance = nullptr;

SpeedSensor::SpeedSensor(int sensorPin, int spokesCount, double wheelRadius) 
    : sensorPin(sensorPin), spokesCount(spokesCount), wheelRadius(wheelRadius), currentSpokeCount(0), lastSpokeTime(0), speed(0.0) {
    if (sensorPin == 2) {
        leftSensorInstance = this;
    } else if (sensorPin == 3) {
        rightSensorInstance = this;
    }
}

void SpeedSensor::init() {
    pinMode(sensorPin, INPUT_PULLUP);
    if (sensorPin == 2) {
        attachInterrupt(digitalPinToInterrupt(sensorPin), handleInterrupt0, RISING);
    } else if (sensorPin == 3) {
        attachInterrupt(digitalPinToInterrupt(sensorPin), handleInterrupt1, RISING);
    }
}

void SpeedSensor::handleInterrupt0() {
    if (leftSensorInstance != nullptr) {
        leftSensorInstance->onSpokeDetected();
    }
}

void SpeedSensor::handleInterrupt1() {
    if (rightSensorInstance != nullptr) {
        rightSensorInstance->onSpokeDetected();
    }
}

void SpeedSensor::onSpokeDetected() {
    unsigned long currentTime = millis();
    
    if (lastSpokeTime > 0) {
        unsigned long timeDifference = currentTime - lastSpokeTime;
        speed = 60000 / (timeDifference*spokesCount); // Скорость в RPM
    }

    lastSpokeTime = currentTime;
    currentSpokeCount++;
}

double SpeedSensor::getSpeed() {
    return speed;
}

double SpeedSensor::getSpeedKmH() {
    float circumference = 2 * PI * wheelRadius;
    return speed * circumference * 60 / 1000;
}

double SpeedSensor::getSpeedMs() {
    return getSpeedKmH() / 3.6;
}

double SpeedSensor::getDistanceMeters() {
    double circumference = 2 * PI * wheelRadius;
    return currentSpokeCount * circumference / spokesCount;
}

int SpeedSensor::getDistance() {
    return currentSpokeCount;
}

void SpeedSensor::mileageCleaning() {
    currentSpokeCount = 0;
}