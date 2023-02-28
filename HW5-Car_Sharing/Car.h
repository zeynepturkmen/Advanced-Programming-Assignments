//Zeynep Turkmen - 29541

#ifndef Car_h
#define Car_h

class Car
{
  public:
    Car(double f, double i, int k); //construts the car object with the given parameters
    void display(); //displays the fuel level, insurance and km of the car
    void modifyKM(int); //modifies the km by the given input
    void modifyFuel(int); //modifies the fuel level accordingly to the traveled km
    void modifyInsurance(double); //modifies the accordingly to the inputted %
    double usedFuel(); //show the amount of fuel used aka needs to be filled up
    void fuelUP(); //maximizes the fuel level
    double Insurance(); //returns the current insurance of the car
    
  private:
    double fuel; //keeps the current fuel of the car
    double insurance; //keeps the insurance value
    int km; //keeps the value of odometer (all km the car has traveled)
    double maxfuel; //keeps the maximum fuel level the car can reach
};

#endif
