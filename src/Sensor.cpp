#include "Sensor.hpp"

std::vector<Sensor*> Sensor::sensors {};
std::array<float, 3> Sensor::coeff {-0.8, -0.01, 0.8};

Sensor::Sensor() : sensor_id(Sensor::sensors.size()){
    Sensor::sensors.push_back(this);
    Sensor::sensors.shrink_to_fit();
}

bool Sensor::setInitialMeasurement(int Tval1, int Tval2, int Tval3, float Rval){
    if(measurements.size() == 0){
        Entry* tmp = new Entry();
        tmp->checkAndSetTemporalInfo(Tval1,Tval2,Tval3);
        tmp->checkAndSetReadingInfo(Rval);
        tmp->checkAndSetSensorID(this->sensor_id);

        measurements.push_back(tmp);
        tmp->printEntry();
        return true;
    }
    return false;

}

bool Sensor::simulateMeasurement(Entry& result){
    if(Sensor::sensors.size() > 0){
        Entry* tmp = new Entry();
        std::array<int, 3> t_info = nextTemporalInfo();
        float read = nextReadingInfo();
        tmp->checkAndSetTemporalInfo(t_info[0], t_info[1], t_info[2]);
        tmp->checkAndSetReadingInfo(read);
        tmp->checkAndSetSensorID(this->sensor_id);

        measurements.push_back(tmp);
        result = *tmp;
        return true;
    }
    return false;
}

void Sensor::printSensorRecord(){
    std::cout << "  Temporal  |  Reading  |  Sensor  " << std::endl;
    std::cout << "------------|-----------|----------" << std::endl;
    for(Entry* i : measurements){
        i->printEntry();
    }
}

std::array<int, 3> Sensor::nextTemporalInfo(){
    Entry* prev = measurements.back();
    std::array<int, 3> t_next, t_prev = prev->getTemporalData();
    int rand = (int)prev->RandomValInBounds(0.00, 100.00);
    int add;
    if(rand >= 0 && rand < 60){
        // add 2 days
        add = 2;
    } else if (rand >= 60 && rand < 90){
        // add 2 * 2days
        add = 4;
    } else if (rand >= 90 && rand < 97 ){
        // add 3 * 2 days
        add = 6;
    } else {
        // add 4 * 2 days
        add = 8;
    }
    this->diff = add;
    t_prev[2] += add;
    // i realized i don't actually need to check for leap years, but its in here anyway
    if(t_prev[2] > 30 && (t_prev[1] == 4 || t_prev[1] == 6 || t_prev[1] == 9 || t_prev[1] == 11)){
        t_next[0] = t_prev[0];
        t_next[1] = t_prev[1] + 1;
        t_next[2] = t_prev[2] - 30;
    } else if(t_prev[2] > 31 && (t_prev[1] == 1 || t_prev[1] == 3 || t_prev[1] == 5 || t_prev[1] == 7 || t_prev[1] == 8 || t_prev[1] == 10)){
        t_next[0] = t_prev[0];
        t_next[1] = t_prev[1] + 1;
        t_next[2] = t_prev[2] - 31;
    } else if(t_prev[2] > 31 && t_prev[1] == 12){
        t_next[0] = t_prev[0] + 1;
        t_next[1] = 1;
        t_next[2] = t_prev[2] - 31;
    } else if (t_prev[2] > 28 && t_prev[1] == 2){
        t_next[0] = t_prev[0];
        t_next[1] = t_prev[1] + 1;
        t_next[2] = t_prev[2] - 28;
    } else{
        t_next = t_prev;
    }
    return t_next;

}

float Sensor::nextReadingInfo(){
    int sz = measurements.size();
    if(sz == 1){
        int coeff_choice = (int)measurements.back()->RandomValInBounds(0, 3);
        this->delta = Sensor::coeff[coeff_choice];
    }
    else if (sz%4 == 1){
        if(this->decreasing){
            std::cout << this->delta << std::endl;
        }
    }
    std::cout << "∂: " << this->delta << std::endl;

    return measurements.back()->getSensData();
}

