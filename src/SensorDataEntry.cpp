#include "SensorDataEntry.hpp"

SensDataEntry::SensDataEntry(){
    temporal_info.fill(std::nan("-1"));
    reading_info = std::nanf("1");
    reading_init = false;
    temporal_init = false;
}

SensDataEntry::~SensDataEntry(){
}

SensDataEntry::SensDataEntry(const SensDataEntry& other){
    this->temporal_info = other.getTemporalData();
    this->reading_info = other.getSensData();
    this->temporal_init = true;
    this->reading_init = true;
}

// Setters
bool SensDataEntry::checkAndSetTemporalInfo(int Tval1, int Tval2, int Tval3){

    if(this->checkTemporalInfo(Tval1, Tval2, Tval3) && !temporal_init){
        this->temporal_info = {Tval1, Tval2, Tval3};
        return true;
    } if(temporal_init){
        std::cout << "temporal info already set, must reset first" << std::endl;
    }
    return false;

}

bool SensDataEntry::checkTemporalInfo(int Tval1, int Tval2, int Tval3){

    if(Tval1 < 2021 || Tval1 > 2023){
        std::cout << "year invalid" << std::endl;
        return false;
    }
    if(Tval2 < 1 || Tval2 > 12){
        std::cout << "month invalid" << std::endl;
        return false;
    }
    switch(Tval2){
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            if(Tval3 > 31){
                std::cout << "day invalid" << std::endl;
                return false;
            }
        case 4:
        case 6:
        case 9:
        case 11:
            if(Tval3 > 30){
                std::cout << "day invalid" << std::endl;
                return false;
            }
        case 2:
            if(Tval1 % 4 == 0 && Tval3 > 29){
                std::cout << "day invalid" << std::endl;
                return false;
            } else if (Tval3 > 28){
                std::cout << "day invalid" << std::endl;
                return false;
            }
    }
    return true;
}

bool SensDataEntry::setRandomTemporalInfo(){
    return false;
}

bool SensDataEntry::checkReadingInfo(float Rval){
    if(trunc(fabs(Rval*100))/100 < 0.0 && trunc(fabs(Rval*100))/100 > 100.0){
        std::cout << "Reading not in bounds" << std::endl;
        return false;
    }
    return true;
}

bool SensDataEntry::checkAndSetReadingInfo(float Rval){
    if(this->checkReadingInfo(Rval) && !reading_init){
        this->reading_info = Rval;
        this->reading_init = true;
        return true;
    } if(reading_init){
        std::cout << "reading set, must reset first" << std::endl;
    }
    return false;
}

bool SensDataEntry::setRandomReadingInfo(){
    return checkAndSetReadingInfo(RandomValInBounds(0.0,100.0));
}

bool SensDataEntry::checkAndSetSensorID(int IDval){
    // no ideal how to check if unique for ever instance ever created
    // maybe with a static list of all instances
    //if(isnan(this->sensor_id))
        return false;
}

void SensDataEntry::reset(){
    temporal_info.fill(std::nan("-1"));
    reading_info = std::nanf("1");
    reading_init = false;
    temporal_init = false;
}

// Getters
bool SensDataEntry::isDataEntrySet() const {
    // temp only ever set as a whole not seperately -> okay to do this
    bool res = (!isnan(temporal_info[0]) && !isnan(reading_info)) ? true : false;
    return res;
}

bool SensDataEntry::getSDE(int& Tval1, int& Tval2, int& Tval3, float& Rval, int& IDval) const {
    if(this->isDataEntrySet()){
        Tval1 = temporal_info[0];
        Tval2 = temporal_info[1];
        Tval3 = temporal_info[3];
        Rval = reading_info;
        IDval = sensor_id;
        return true;
    }
    std::cout << "not all data set" << std::endl;
    return false;
}

float SensDataEntry::getSensData() const {
    return 0.0;
}

std::array<int, 3> SensDataEntry::getTemporalData() const {
    return {-1,-1,-1};
}

void SensDataEntry::printEntry() const {
    // print stuff
}
/*
SensDataEntry& SensDataEntry::operator= (const SensDataEntry& other){
    return;
}
*/
float SensDataEntry::RandomValInBounds(float min_val, float max_val){
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<float> distribution(min_val, max_val);
    return distribution(generator);
}

