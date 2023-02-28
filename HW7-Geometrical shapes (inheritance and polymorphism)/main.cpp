// Zeynep Turkmen - 29541
#include <iostream>
#include "shape.h"
#include "TwoDShape.h"
#include "ThreeDShape.h"

using namespace std;

shape * getShape()
{
    char choice;
    
    cout << "Choose an option < 1 or 2 >: " << endl;
    cout << "1. Rectangle" << endl;
    cout << "2. Box" << endl;
    cin >> choice; //User picks the type of the shape
    
    while (choice != '1' && choice != '2') //if user picks something other than 1 or 2
    {
        cout << "UNAVAILABLE OPTION CHOSEN. Try again." << endl << endl;
        cout << "Choose an option < 1 or 2 >: " << endl;
        cout << "1. Rectangle" << endl;
        cout << "2. Box" << endl;
        cin >> choice;
    }
    if (choice == '1') //shape is a rectangle
    {
        float w,l;
        string n;
        cout << "You chose rectangle. Give it's width, length and name: " << endl;
        cin >> w >> l >> n;
        rectangle * r = new rectangle(w,l,n); //create the rectangle dynamically allocated with the given input
        return r;
    }
    else //shape is a box
    {
        float w,l,h;
        string n;
        cout << "You chose box. Give it's width, length, height and name: " << endl;
        cin >> w >> l >> h >> n;
        box * r = new box(w,l,h,n); //create the box dynamically allocated with the given input
        return r;
    }
} //returns a pointer to a shape

int main()
{
	cout<<"WELCOME TO THE SHAPE COMPARISONN PROGRAM"<<endl;
	cout<<"FOR EXITIING PRESS Y/y, OTHERWISE PRESS ANY KEY"<<endl;
	shape *shape_1, *shape_2; /* define two varibles, named shape_1 and shape_2 of the class shape.*/
	/*What should they be in order to enable proper polymorphism?*/
	char c;
	while (tolower(c = getchar())!='y')
	{
		cout<<"Defining (getting) shape 1..."<<endl;
		
		shape_1 = getShape();
		cout<<"Defining (getting) shape 2..."<<endl;
		shape_2 = getShape();
		cout<<"********************************************************************"<<endl;
		cout<<"PRINTING SHAPE_1 INFOS:"<<endl<<"Name: "<<shape_1->getName()<<", perimeter: "
			<<shape_1->perimeter()<<", area: "<<shape_1->area()<<", volume: "<<shape_1->volume()<<endl<<endl;
		cout<<"PRINTING SHAPE_2 INFOS:"<<endl<<"Name: "<<shape_2->getName()<<", perimeter: "
			<<shape_2->perimeter()<<", area: "<<shape_2->area()<<", volume: "<<shape_2->volume()<<endl;		
		bool nothingInCommon=true; // to check whether they have anything in common (perimeter, area, volume)
		if(shape_1->perimeter()==shape_2->perimeter())
		{
			nothingInCommon = false;
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" have the same perimeter, which is: "
				<<shape_1->perimeter()<<" cm."<<endl;
		}
		if(shape_1->area()==shape_2->area())
		{
			nothingInCommon = false;
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" have the same area, which is: "
				<<shape_1->area()<<" cm^2."<<endl;
		}
		if(shape_1->volume()==shape_2->volume())
		{
			nothingInCommon = false;
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" have the same volume, which is: "
				<<shape_1->volume()<<" cm^3."<<endl;
		}
		if (nothingInCommon)
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" don't have anything in common."<<endl;		
		
		delete shape_1;
		delete shape_2;

		cout<<"********************************************************************"<<endl;
		cout<<"FOR EXITIING PRESS Y/y, OTHERWISE, FOR ANOTHER COMPARISON PRESS ANY KEY"<<endl<<endl;
		cin.ignore();//flushing the buffer for remaining character(s), in order getchar() to work
  	}//while(tolower(c = getchar())!='y')
	cout<<"PROGRAM EXITING. THANKS FOR USING IT."<<endl;
	system("pause");
	return 0;
}
