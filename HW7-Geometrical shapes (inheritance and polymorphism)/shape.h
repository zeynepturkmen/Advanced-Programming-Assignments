//Zeynep Turkmen - 29541

#ifndef shape_h
#define shape_h

#include <string>
using namespace std;

class shape //abstract class that keeps the name
{
    public:
        shape(string n) //constructor that sets myname as the given input
        {
            myName = n;
        }
        virtual ~shape() {};
        string getName() //returns the name of the shape
        {
            return myName;
        }
        virtual float perimeter() = 0; //pure virtual functions
        virtual float area() = 0;
        virtual float volume() = 0;
    protected:
        string myName;
};
#endif
