//Zeynep Turkmen - 29541

#include "Driver.h"
#include <iostream>
using namespace std;

Driver::Driver(Car & c, double b): theCar(c), budget(b) //constructs the Driver object accordingly to the inputted values
{}

void Driver::drive(int km) //modifies the fuel and km levels with the inputted km
{
    theCar.modifyKM(km);
    theCar.modifyFuel(km);
}

void Driver::repairCar(string s)
{
    double amount; //is set depending on the size of the accident
    
    if (s == "SMALL")
    {
        amount = 50;
        theCar.modifyInsurance(5); //modifies the insurence by 5%
    }
    else if (s == "MEDIUM")
    {
        amount = 150;
        theCar.modifyInsurance(10); //modifies the insurence by 10%
    }
    else
    {
        amount = 300;
        theCar.modifyInsurance(20); //modifies the insurence by 20%
    }
    budget = budget - amount; //reduces the budget
    cout << amount << "$ is reduced from the driver's budget because of the " << s << " accident." << endl;
    cout << "Yearly insurance fee is increased to " << theCar.Insurance() << " because of the " << s << " accident." << endl;
}

void Driver::display() //displays drivers budget to the user
{
    cout << "Driver Budget: " << budget << endl;
}

void Driver::fullFuel() //fills the fuel
{
    budget = budget - theCar.usedFuel(); //reduces the budget by amount that needs to be filled
    theCar.fuelUP(); //maximizes the fuel of the car
    cout << endl << "Fuel is full" << endl << endl;
}
