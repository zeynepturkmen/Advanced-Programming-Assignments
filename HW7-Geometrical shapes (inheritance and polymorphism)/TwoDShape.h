//Zeynep Turkmen - 29541

#ifndef TwoDShape_h
#define TwoDShape_h

#include "shape.h"

class TwoDShape: public shape //abstract class
{
    public:
        virtual float volume() //volume of a 2D shape is always set as 0
        {
            return 0;
        }
        TwoDShape(string n): shape(n)
        {
           //sets myName as n and makes the volume function return 0
        }
        virtual ~TwoDShape(){};
};

class rectangle: public TwoDShape
{
    public:
        rectangle(float w, float l, string n): TwoDShape(n) //creates a 2D rectangle with name n
        {
            width = w; //sets the private variables accordingly to the given inputs
            length = l;
        }
        virtual ~rectangle(){};
        virtual float perimeter() //returns the perimeter of the rectangle
        {
            return 2 * (width + length);
        }
        virtual float area() //returns the area of the rectangle
        {
            return width * length;
        }
    private:
        float width;
        float length;
};
#endif
