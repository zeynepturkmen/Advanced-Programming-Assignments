//Zeynep Turkmen - 29541

#ifndef ThreeDShape_h
#define ThreeDShape_h

#include "shape.h"

class ThreeDShape: public shape //abstract class
{
    public:
        virtual float perimeter() //perimeter of a 3D shape is always set as 0
        {
            return 0;
        }
        ThreeDShape(string n): shape(n)
        {
            //sets myName as n and makes the perimeter function return 0
        }
        virtual ~ThreeDShape(){};
};

class box: public ThreeDShape
{
    public:
        box(float w, float l, float h, string n): ThreeDShape(n) //creates a 3D box with name n
        {
            width = w; //sets the private variables accordingly to the given inputs
            length = l;
            height = h;
        }
        virtual ~box(){};
        virtual float volume() //returns the volume of the box
        {
            return width * length * height;
        }
        virtual float area() //returns the area of the box
        {
            return 2 * (width * length + width * height + length*height);
        }
    private:
        float width;
        float length;
        float height;
};
#endif 
