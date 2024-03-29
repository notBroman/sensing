#include "SensorDataEntry.hpp"


SensDataEntry::SensDataEntry(){
    temporal_info.fill(std::nan("-1"));
    reading_info = std::nanf("1");
    reading_init = false;
    temporal_init = false;
    id_init = false;
}

SensDataEntry::~SensDataEntry(){
}

SensDataEntry::SensDataEntry(const SensDataEntry& other){
    if(other.isDataEntrySet()){
        this->temporal_info = other.getTemporalData();
        this->reading_info = other.getSensData();
        this->temporal_init = true;
        this->reading_init = true;
        this->id_init = true;
    }
}

// Setters
bool SensDataEntry::checkAndSetTemporalInfo(int Tval1, int Tval2, int Tval3){

    if(this->checkTemporalInfo(Tval1, Tval2, Tval3) && !temporal_init){
        this->temporal_info = {Tval1, Tval2, Tval3};
        temporal_init = true;
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
    if(Tval3 > 31){
        std::cout << "day invalid" << Tval3 << std::endl;
        return false;
    }
    if (Tval2 == 2 && Tval3 > 28){
        std::cout << "day invalid" << Tval3 << std::endl;
        std::cout << Tval1 << ":" << Tval2 << ":" << Tval3 << std::endl;
        return false;
    }
    switch(Tval2){
<<<<<<< HEAD
=======
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
>>>>>>> parent of de97e4f (bug with date validatin fml)
        case 4:
        case 6:
        case 9:
        case 11:
            if(Tval3 > 30){
                std::cout << "day invalid" << std::endl;
                return false;
            }
<<<<<<< HEAD
=======
        case 2:
            if(Tval1 % 4 == 0 && Tval3 > 29){
                std::cout << "day invalid" << std::endl;
                return false;
            } else if (Tval3 > 28){
                std::cout << "day invalid" << std::endl;
                return false;
            }
>>>>>>> parent of de97e4f (bug with date validatin fml)
    }
    return true;
}

bool SensDataEntry::setRandomTemporalInfo(){
    int YYYY = 0;
    int MM = 0;
    int DD = 0;

    do{
        YYYY = std::trunc(RandomValInBounds(2021,2023.1));
        MM = std::trunc(RandomValInBounds(1,12.1));
        DD = std::trunc(RandomValInBounds(1,31.1));
    }while(!checkTemporalInfo(YYYY, MM, DD));

    return checkAndSetTemporalInfo(YYYY, MM, DD);
}

bool SensDataEntry::checkReadingInfo(float Rval){
    if(round_down(Rval, 2) < 0.00 || round_down(Rval, 2) > 100.00){
        std::cout << "Reading not in bounds" << std::endl;
        return false;
    }
    return true;
}

bool SensDataEntry::checkAndSetReadingInfo(float Rval){
    if(checkReadingInfo(Rval) && !reading_init){
        this->reading_info = Rval;
        this->reading_init = true;
        return true;
    } else if(reading_init){
        std::cout << "reading set, must reset first" << std::endl;
        return false;
    }
    return false;
}

bool SensDataEntry::setRandomReadingInfo(){
    return checkAndSetReadingInfo(RandomValInBounds(0.0,100.0));
}

bool SensDataEntry::checkAndSetSensorID(int IDval){
    // no ideal how to check if unique for ever instance ever created
    // maybe with a static list of all instances
    if(IDval < 0){
        std::cout << "Sensor ID must be positive" << std::endl;
        return false;
    }
    sensor_id = IDval;
    id_init = true;
    return true;
}

void SensDataEntry::reset(){
    temporal_info.fill(std::nan("-1"));
    reading_info = std::nanf("1");
    sensor_id = std::nanf("-1");
    reading_init = false;
    temporal_init = false;
    id_init = false;
}

// Getters
bool SensDataEntry::isDataEntrySet() const {
    // temp only ever set as a whole not seperately -> okay to do this
    bool res = (temporal_init && reading_init && id_init) ? true : false;
    return res;
}

bool SensDataEntry::getSDE(int& Tval1, int& Tval2, int& Tval3, float& Rval, int& IDval) const {
    if(this->isDataEntrySet()){
        Tval1 = temporal_info[0];
        Tval2 = temporal_info[1];
        Tval3 = temporal_info[2];
        Rval = reading_info;
        IDval = sensor_id;
        return true;
    }
    std::cout << "not all data set" << std::endl;
    return false;
}

float SensDataEntry::getSensData() const {
    return reading_info;
}

std::array<int, 3> SensDataEntry::getTemporalData() const {
    return temporal_info;
}

void SensDataEntry::printEntry() const {
    // print stuff
    if(isDataEntrySet()){
        std::cout << "Temporal Data: " << temporal_info[0] << "-" << temporal_info[1] << "-" << temporal_info[2] << std::endl;
        std::cout << "Reading Data: " << reading_info << std::endl;
        std::cout << "Sensor ID: " << sensor_id << std::endl;
    } else{
        std::cout << "entry not set" << std::endl;
    }
}

SensDataEntry& SensDataEntry::operator= (const SensDataEntry& other){
    SensDataEntry tmp(other);
    swap(tmp);
    return *this;
}

void SensDataEntry::swap(SensDataEntry& tmp){
    this->temporal_info = tmp.getTemporalData();
    this->reading_info = tmp.getSensData();
    this->temporal_init = true;
    this->reading_init = true;
    this->id_init = true;
}

double SensDataEntry::round_down(double value, int decimal_places) {
    const double multiplier = std::pow(10.0, decimal_places);
    return std::floor(value * multiplier) / multiplier;
}


float SensDataEntry::RandomValInBounds(float min_val, float max_val){
    min_val *= 100;
    max_val *= 100;
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<float> distribution(min_val, max_val);
    return distribution(generator)/100;
}


