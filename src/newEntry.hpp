#pragma once

#include "SensorDataEntry.hpp"
#include <stdio.h>

class Entry : public SensDataEntry{

public:
    void printEntry() const override;
};
