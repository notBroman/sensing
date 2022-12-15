#pragma once

#include <cmath>
#include <vector>

#include "newEntry.hpp"

class Sensor{
protected:
    const int sensor_id;
    std::vector<Entry*> measurements;

    static std::vector<Sensor*> sensors;
    static std::array<float, 3> coeff;

public:
    // constructor
    Sensor();

    // getters
    std::array<int, 3> nextTemporalInfo();
    float nextReadingInfo();

    bool setInitialMeasurement(int Tval1, int Tval2, int Tval3, float Rval);
    bool simulateMeasurement(SensDataEntry& result);
    void printSensorRecord();

};
