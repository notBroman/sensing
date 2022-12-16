#include "newEntry.hpp"

// all this just for a nicer printing function?
void Entry::printEntry() const{
    if(isDataEntrySet()){
        printf(" %4d-%2d-%2d |", temporal_info[0], temporal_info[1], temporal_info[2]);
        printf("%10.2lf |", reading_info);
        printf("%10d\n", sensor_id);
    }
}
