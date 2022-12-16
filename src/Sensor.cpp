#include "Sensor.hpp"

// static members
std::vector<Sensor*> Sensor::sensors {};
std::array<float, 3> Sensor::coeff {-0.8, -0.01, 0.8};

Sensor::Sensor() : sensor_id((Sensor::sensors.size()) + 1){
    // basic constructor
    // intialize the constant sensor id based on the number of sensors created
    Sensor::sensors.push_back(this);
    Sensor::sensors.shrink_to_fit();
}

bool Sensor::setInitialMeasurement(int Tval1, int Tval2, int Tval3, float Rval){
    // set the initial measurement with given values
    if(measurements.size() == 0){
        // since I append the measurement to a vector of all measurements by that
        // sensor I need to allocate mempry dynamically for it
        // since entries can only be added no need to worry about cleanup
        Entry* tmp = new Entry();
        tmp->checkAndSetTemporalInfo(Tval1,Tval2,Tval3);
        tmp->checkAndSetReadingInfo(Rval);
        tmp->checkAndSetSensorID(this->sensor_id);

        measurements.push_back(tmp);
        return true;
    }
    return false;

}

bool Sensor::simulateMeasurement(Entry& result){
    // only allow measures to be gnerated if there is already at least existing one measurement
    if(Sensor::sensors.size() > 0){
        // since I append the measurement to a vector of all measurements by that
        // sensor I need to allocate mempry dynamically for it
        // since entries can only be added no need to worry about cleanup
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
    // print stuff in a nice table
    std::cout << "  Temporal  |  Reading  |  Sensor  " << std::endl;
    std::cout << "------------|-----------|----------" << std::endl;
    for(Entry* i : measurements){
        i->printEntry();
    }
}

std::array<int, 3> Sensor::nextTemporalInfo(){
    // calculate new temporal info for the entry
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
    // fix dates after adding dates
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
    // implement rules for the readings
    int sz = measurements.size();
    if(sz == 1){
        int coeff_choice = (int)measurements.back()->RandomValInBounds(0, 3);
        this->delta = Sensor::coeff[coeff_choice];
    }
    else if (sz%4 == 1 && this->delta == Sensor::coeff[0]){
        if(this->decreasing){
            this->decreasing = !this->decreasing;
        }
        this->delta = Sensor::coeff[1];
    }
    else if (sz%4 == 1 && this->delta == Sensor::coeff[1]){
        this->delta = (this->decreasing) ? Sensor::coeff[0] : Sensor::coeff[2];
    }
    else if (sz%4 == 1 && this->delta == Sensor::coeff[2]){
        if(!this->decreasing){
            this->decreasing = !this->decreasing;
        }
        this->delta = Sensor::coeff[1];
    }

    float res = measurements.back()->getSensData() + (this->delta * 0.4 * this->diff);
    // clamp using ternary operator
    res = (res < 0.00) ? 0.00 : res;
    res = (res > 100.00) ? 100.00 : res;

    return res;
}

