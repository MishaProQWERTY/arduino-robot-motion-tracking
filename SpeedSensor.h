#ifndef SPEED_SENSOR_H
#define SPEED_SENSOR_H

#include <Arduino.h>

class SpeedSensor {
public:
    SpeedSensor(int sensorPin, int spokesCount = 12, double wheelRadius = 0.031);
    void init();
    void update();
    double getSpeed();
    double getSpeedMs();
    double getSpeedKmH();
    double getDistanceMeters();
    int getDistance();
    void mileageCleaning();

private:
    int sensorPin;
    int spokesCount;
    double wheelRadius;
    volatile int currentSpokeCount;
    volatile unsigned long lastSpokeTime;
    volatile double speed;

    void calculateSpeed();
    void onSpokeDetected();
    
    static void handleInterrupt0();
    static void handleInterrupt1();

    static SpeedSensor* leftSensorInstance;
    static SpeedSensor* rightSensorInstance;
};

#endif