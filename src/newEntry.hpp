#pragma once

#include "SensorDataEntry.hpp"
#include <stdio.h>

// an entire class just for this one function ...
class Entry : public SensDataEntry{

public:
    void printEntry() const override;
};
