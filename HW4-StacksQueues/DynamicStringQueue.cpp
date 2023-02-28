/*Author: Zeynep Dogmus
 *Date: March 2013
 *Operator Overloading with Queue
*/
#include <iostream>
#include "DynamicStringQueue.h"
using namespace std;
#include <string>
//********************************************
// Constructor. Generates an empty queue     *
//********************************************

DynamicStringQueue::DynamicStringQueue()
{
	front = NULL;
	rear = NULL;
}

QueueNode* DynamicStringQueue::GetFront()
{
	return front;
}

QueueNode* DynamicStringQueue::GetRear()
{
	return rear;
}

//********************************************
// Deep Copy Constructor                     *
//********************************************

#if defined(SCENARIO1) || defined(SCENARIO3) || defined(SCENARIO5) || defined(SCENARIO6)
DynamicStringQueue::DynamicStringQueue(const DynamicStringQueue & copy)
{
	createClone(copy);
}
#endif

//******************************************************************
// Shallow Copy Constructor:									   *
// Queue that is copied with a shallow copy will be problematic.   *
// Since it only copies the front and rear of the original queue.  *
// Copied queue will be modified as the original queue is modified.*
//******************************************************************
#if defined(SCENARIO2) || defined(SCENARIO4)
DynamicStringQueue::DynamicStringQueue(const DynamicStringQueue & q)
{
	front = q.front;	//front copy
	rear = q.rear;		//rear copy
}
#endif

void DynamicStringQueue::createClone(const DynamicStringQueue & copy)
{
	if (copy.front == NULL) 
	{
		front = NULL;
		rear = NULL;
	}
	else
	{
		QueueNode * temp = copy.front;
		front = new QueueNode(temp->name, temp->function, temp->id, NULL);
		rear = front;

		while(temp->next != NULL) 
		{
			temp = temp->next;
			rear->next = new QueueNode(temp->name, temp->function, temp->id, NULL);
			rear = rear->next;
		}
	}
}

//****************************************************
// Assignment operator                               *                                    
//****************************************************
#if defined(SCENARIO1) || defined(SCENARIO2) || defined(SCENARIO3) || defined(SCENARIO4) || defined(SCENARIO5)
const DynamicStringQueue & DynamicStringQueue::operator=(const DynamicStringQueue & rhs)
{
	//Check whether the rhs object is different than our queue
	if (this != &rhs)
	{
		clear(); 
		createClone(rhs);
	}
	return *this;
}
#endif

#if defined(SCENARIO6)
const DynamicStringQueue& DynamicStringQueue::operator=(const DynamicStringQueue& rhs)
{
	//Check whether the rhs object is different than our queue
	if (this != &rhs)
	{
		clear();
		this->rear = rhs.rear;
		this->front = rhs.front;
	}
	return *this;
}
#endif
//********************************************
// Function enqueue inserts the value in num *
// at the rear of the queue.                 *
//********************************************
void DynamicStringQueue::enqueue(string n, string f, int i) //modified to take 3 values
{
	if (isEmpty())   //if the queue is empty
	{	//make it the first element
		front = new QueueNode(n,f,i); //modified to take 3 values
		rear = front;
	}
	else  //if the queue is not empty
	{	//add it after rear
		rear->next = new QueueNode(n,f,i); //modified to take 3 values
		rear = rear->next;
	}
}

//**********************************************
// Function dequeue removes the value at the   *
// front of the queue, and copies it into num. *
//**********************************************
void DynamicStringQueue::dequeue(string & n, string & f, int & i) //modified to take 3 values
{
	QueueNode *temp;
	if (isEmpty())
	{
		cout << "Attempting to dequeue on empty queue, exiting program...\n";
		exit(1);
	}
	else //if the queue is not empty
	{	//return front's value, advance front and delete old front
		f = front->function;
        n = front->name;
        i = front->id;
		temp = front;
		front = front->next;
		delete temp;      
	}
}

//*********************************************
// Function isEmpty returns true if the queue *
// is empty, and false otherwise.             *
//*********************************************
bool DynamicStringQueue::isEmpty() const
{
	if (front == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//********************************************
// Function clear dequeues all the elements  *
// in the queue.                             *
//********************************************

void DynamicStringQueue::clear(void)
{
	string n,f;   // Dummy variable for dequeue
    int i;

	while(!isEmpty())
	{
		dequeue(n, f, i); //delete all elements
	}
}

DynamicStringQueue::~DynamicStringQueue() //destroys the que
{
	clear();
}
