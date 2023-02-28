#include <iostream>
#include "IntQueue.h"
using namespace std;

//*****************************************
// Constructor - creates an empty queue   *
// with given number of elements          *
//*****************************************

IntQueue::IntQueue(int s) //modified to create an array of s number of persons
{
	queueArray = new person[s];
	queueSize = s;
	front = -1;
	rear = -1;
	numItems = 0;
}

//********************************************
// Function enqueue inserts the value in num *
// at the rear of the queue.                 *
//********************************************
void IntQueue::enqueue(person p) //modified for "person"
{
	if (isFull())
    { 
         cout << "The queue is full. " << p.request << " not enqueued\n";
    }
	else
	{
		// Calculate the new rear position circularly.
		rear = (rear + 1) % queueSize;
		// Insert new item.
		queueArray[rear] = p;
		// Update item count.
		numItems++;
	}
}

//**********************************************
// Function dequeue removes the value at the   *
// front of the queue, and copies it into num. *
//**********************************************
void IntQueue::dequeue(person & p) //modified for "person"
{
	if (isEmpty())
	{
       cout << "Attempting to dequeue on empty queue, exiting program...\n";
       exit(1);
    }
	else
	{
		// Move front.
		front = (front + 1) % queueSize;
		// Retrieve the front item.
		p = queueArray[front];
		// Update item count.
		numItems--;
	}
}

//*********************************************
// Function isEmpty returns true if the queue *
// is empty, and false otherwise.             *
//*********************************************
bool IntQueue::isEmpty() const
{
	if (numItems > 0)
		return false;
	else
		return true;	
}

//********************************************
// Function isFull returns true if the queue *
// is full, and false otherwise.             *
//********************************************
bool IntQueue::isFull() const
{
	if (numItems < queueSize)
		return false;
	else
		return true;
}

//*******************************************
// Function clear resets the front and rear *
// indices, and sets numItems to 0.         *
//*******************************************
void IntQueue::clear()
{
	front =  - 1;
	rear =  - 1;
	numItems = 0;
}

IntQueue:: ~IntQueue() //modified to clear the allocated memory
{
    delete [] queueArray ;
}
