#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <array>
#include <cmath>
#include <random>

class SensDataEntry{
protected:
    //YYYY-MM-DD
    std::array<int ,3> temporal_info;
    //0.00 - 100.00 % Humidity
    float reading_info;
    bool reading_init;
    bool temporal_init;

    int sensor_id;


public:
    SensDataEntry();
    ~SensDataEntry();
    SensDataEntry(const SensDataEntry& other);

    // Setters
    bool checkAndSetTemporalInfo(int Tval1, int Tval2, int Tval3);
    bool checkTemporalInfo(int Tval1, int Tval2, int Tval3);
    bool setRandomTemporalInfo();
    bool checkAndSetReadingInfo(float Rval);
    bool checkReadingInfo(float Rval);
    bool setRandomReadingInfo();
    bool checkAndSetSensorID(int IDval);
    void reset();

    // Getters
    bool isDataEntrySet() const;
    bool getSDE(int& Tval1, int& Tval2, int& Tval3, float& Rval, int& IDval) const;
    float getSensData() const;
    std::array<int, 3> getTemporalData() const;
    void printEntry() const;

    // Overloads
    SensDataEntry& operator= (const SensDataEntry& other);

    // Utility
    static float RandomValInBounds(float min_val, float max_val);
};

