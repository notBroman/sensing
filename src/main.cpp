#include <iostream>
#include "SensorDataEntry.hpp"
#include "tester.hpp"

int main(int argv, char* argc[]){
    //test_SDE();
    std::cout << "--------------- ran test suite (1/2) ---------------" << std::endl;
    test_sensor();
    std::cout << "--------------- ran test suite (2/2) ---------------" << std::endl;
    return 0;
}
