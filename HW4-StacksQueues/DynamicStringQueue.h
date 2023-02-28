/*Author: Zeynep Dogmus
 *Date: March 2013
 *Operator Overloading with Queue
*/

/*
This is a queue class which has a copy constructor(deep/shallow), a destructor and assignment operator(deep/shallow).
6 different scenarios are created using different combinations of shallow/deep 
copy constructors, assignment operators and Print function.

Scenario 1(deep copy and deep assignment operator) and Scenario 2(shallow copy constructor and deep assignment operator) without Print function:
	The main idea behind these scenarios is to show the issue when destructor called for an object created by shallow copy constructor.
	Shallow copy constructor results a different object on the same memory adress with the original one. When destructor is called for one of them(doesn't matter if the original one or copy one),
	both of them will be deleted from the memory, on the other hand, at the end of the program, even if both of them were deleted in the memory, 
	the program won't be aware of it and it will call destructor for the other one, then your program will crash since it will try to delete an object which was already deleted. This is why scenario 1
	works normal while 2nd one crashes.

Scenario 3(deep copy and deep assignment operator) and Scenario 4(shallow copy constructor and deep assignment operator) with Print function:
	The main idea behind these scenarios is similar with the previous ones but with Print function. Since Print function takes parameter with value, copy constructor will be called when Print 
	function is called. Therefore, when this function is called with a shallow copy constructor, changes done on local object also effects the original one. Due to nature of queue structure, 
	when an element is dequeued, it will be deleted from the queue. So thanks to shallow copy, printed queue object will be empty at the end of the Print function. But this is a naive problem 
	besides the following one, destructor will be called for the local object and it will be deleted at the end of the Print function(recall that changes done on local object also effect the original one),
	hence usage of the original object after Print function causes crash. Scenario 3 works as desired while scenario 4 crashes.

Scenario 5(deep copy and deep assignment operator) and Scenario 6(deep copy constructor and shallow assignment operator):
	Deep copy constructor is used for both of them, therefore Print function is not the issue in these scenarios. On the other hand, shallow assignment operator causes crash this time thanks 
	to similar reason behind the 2nd scenario's crash. In the main function line 57, queue2 is assigned to queue and when one of them is deleted automatically other one will be deleted also. 
	Just like in the 2nd scenario, at the end of the program, destructor will be called both of them, first queue2 will be deleted since it is defined after queue, after that when the 
	program tries to delete queue, it will crash since its memory was already freed when queue2 was deleted. And so scenario 5 works as desired while scenario 6 crashes.

As extra, you can try not to have
copy constructor and assignment operator at all; this should behave as
if there are shallow versions of them since in absence of assignment and
copy constructor, compiler provides such.
	
*/
#ifndef DYNAMICSTRINGQUEUE_H
#define DYNAMICSTRINGQUEUE_H

#include <string>
using namespace std;


#define SCENARIO1

//#define SCENARIO2

//#define SCENARIO3

//#define SCENARIO4

//#define SCENARIO5

//#define SCENARIO6

struct QueueNode //added more information to it
{
	string function;
    string name;
    int id;
	QueueNode *next;
	QueueNode(string n, string f, int i, QueueNode *ptr = NULL) //modified to take 3 values
	{
		next = ptr;
        id = i;
        name = n;
        function = f;
	}
    QueueNode()
    {
        //default constructor
    }
};

class DynamicStringQueue
{
	private:
		QueueNode *front;
		QueueNode *rear;

	public:
		DynamicStringQueue();
		~DynamicStringQueue();
		//Deep Copy or Shallow Copy Constructor (by commenting out necessary parts)
		DynamicStringQueue(const DynamicStringQueue &);

		void enqueue(string n, string f, int i);
		void dequeue(string & n, string &f, int & i);
		bool isEmpty() const; 
		void clear(void);

		QueueNode* GetFront();
		QueueNode* GetRear();
		void createClone(const DynamicStringQueue &);
		const DynamicStringQueue & operator = (const DynamicStringQueue & rhs);

};


#endif
