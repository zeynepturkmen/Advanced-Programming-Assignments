//Zeynep Turkmen - 29541

#include "Car.h"
#include <iostream>

using namespace std;

Car::Car(double f, double i, int k) //constructs the car object accordingly with the inputted values
{
    km = k;
    fuel = f;
    insurance = i;
    maxfuel = f; //added so that the class can be used (later on) for more than max 300 dollars of fuel
}

void Car::display() //displays the private variables to the user
{
    cout << "Fuel Level: " << fuel << endl;
    cout << "Insurance Fee: " << insurance << endl;
    cout << "Total distance that the car has travelled: " << km << endl;
}

void Car::modifyKM(int a) //modifies the km of the vehicle by the inputted amount of km "a"
{
    km = km + a;
}

void Car::modifyFuel(int a) //modifies the km of the vehicle accordingly to km "a"
{
    fuel = fuel - (a * 0.25); //reduces the fuel assuming that fuel costs 0.25 for each km
}

void Car::modifyInsurance(double a) //modified the insurance accordingly to the given percentage -> "a"
{
    insurance = insurance * (100 + a)/100;
}

double Car::usedFuel()
{
    return (maxfuel - fuel); //returns amount of used fuel = amount that needs to be filled
}


void Car::fuelUP() //maximizes the fuel level
{
    fuel = maxfuel;
}

double Car::Insurance() //returns the insurance to the user
{
    return insurance;
}
