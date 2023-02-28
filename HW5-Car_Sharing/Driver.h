//Zeynep Turkmen - 29541

#ifndef Driver_h
#define Driver_h

#include "Car.h"
#include <string>

using namespace std;

class Driver
{
  public:
    Driver (Car & c, double b); //constructs the driver object accordingly with the given values
    void drive(int); //increments the km count of the car while reducing the fuel
    void repairCar(string); //increases the insurance of the car, reduces the drivers budget accordingly to the inputted string (size of an accident)
    void display(); //displays drivers budget
    void fullFuel(); //fills the fuel of the car object while reducing drivers budget accordingly
  private:
    double budget;
    Car & theCar;
};

#endif /* Driver_h */
