#pragma once

#include <cmath>
#include <vector>

#include "newEntry.hpp"

class Sensor{
protected:
    // unique const id for sensor
    const int sensor_id;
    std::vector<Entry*> measurements;

    // static stuff because how else can a unique const id be forced
    static std::vector<Sensor*> sensors;
    static std::array<float, 3> coeff;

public:
    // constructor
    Sensor();

    // getters
    std::array<int, 3> nextTemporalInfo();
    float nextReadingInfo();
    int diff;
    float delta;
    bool decreasing = true;

    bool setInitialMeasurement(int Tval1, int Tval2, int Tval3, float Rval);
    bool simulateMeasurement(Entry& result);
    void printSensorRecord();

};
