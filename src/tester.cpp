#include "tester.hpp"
#include "SensorDataEntry.hpp"
#include "newEntry.hpp"
#include "Sensor.hpp"

using namespace std;

void test_SDE(){
    SensDataEntry test_SDE;
    float Rval;
    int Tval1, Tval2, Tval3;
    float chk_Rval;
    int chk_Tval1, chk_Tval2, chk_Tval3, chk_IDval;
    bool check;
    // Report at least one test with input values in the correct range; then at least one test with value(s) outside the range.
    // Insert appropriate values below:
    Tval1 = 2021;
    Tval2 = 1;
    Tval3 = 12;
    // Report at least one test with input value in the correct range; then at least one test with value outside the range.
    // Insert the appropriate value below:
    Rval = 67.43;
    // test the input funciton
    test_SDE.checkAndSetTemporalInfo(Tval1, Tval2, Tval3);
    test_SDE.checkAndSetReadingInfo(Rval);
    test_SDE.checkAndSetSensorID(5);
    // test the output functions
    check = test_SDE.getSDE(chk_Tval1, chk_Tval2, chk_Tval3, chk_Rval, chk_IDval);
    if (check){
        cout << "Entry values: " << chk_Tval1 << " ; " << chk_Tval2 << " ; ";cout << chk_Tval3 << " ; " << chk_Rval << " ; " << chk_IDval << endl;
    }else
        cout << "Check failed: one or more values are not set." << endl;
    cout << endl << endl;
    // Also check the same information is printed to screen
    cout << " -- Now print to screen --" << endl;
    test_SDE.printEntry();
    cout << "make a copy with operator= and print it" << endl;
    SensDataEntry a = test_SDE;
    a.checkAndSetSensorID(4);
    a.printEntry();
    cout << " -- ------------------- --" << endl;
    // this checks random entries
    for (int i = 1; i <= 10; i++){
        test_SDE.reset();
        test_SDE.setRandomTemporalInfo();
        test_SDE.setRandomReadingInfo();
        test_SDE.checkAndSetSensorID(i);
        test_SDE.printEntry();
        cout << endl;
    }
}

void test_sensor(){
    // removed printing statements
    static const int TOT_SENSORS = 2;
    Sensor test_sensor[TOT_SENSORS];
    Entry result;
    // this line assumes the base class SensDataEntry form Part 1; you may change it to the derived class, if needed.
    bool check;
    int Tval1, Tval2, Tval3; float Rval;
    // TO DO: set inital T_info as the earliest value:
    Tval1 = 2022;
    Tval2 =1;
    Tval3 =12;
    // TO DO: set inital R_info somewhere in the middle of the range:
    Rval =43.98;
    for (int sensor_i = 0; sensor_i < TOT_SENSORS; sensor_i++){
        cout << " ------ Testing Sensor " << (sensor_i+1) << " ------" << endl;
        check = test_sensor[sensor_i].setInitialMeasurement(Tval1, Tval2, Tval3, Rval);
        if (check){
            int tot_test = 25;
            for (int i = 0; i < tot_test; i++){
                check = test_sensor[sensor_i].simulateMeasurement(result);
                if (check){
                }else{
                    cout << "Measurement simulation failed" << endl;
                    break;
                }
            }
        }else
            cout << "Setting starting measure failed" << endl;
        test_sensor[sensor_i].printSensorRecord();
        cout << " ------------- Done ----------------" << endl << endl;
    }
}
