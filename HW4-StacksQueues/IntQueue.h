#ifndef INTQUEUE_H
#define INTQUEUE_H
#include <string>

using namespace std;

struct person //to create an array of persons
{
    string name;
    int id;
    string request;
    person(string n, string r, int i)
    {
        id = i;
        name = n;
        request = r;
    }
    person()
    {
        //default constructor
    }
};

class IntQueue
{
private:
	person *queueArray;
	int queueSize;  //capacity of queue
	int front;
	int rear;
	int numItems;  //# of elements currently in the queue
public:
	IntQueue(int);  //constructor, parameter is capacity
  	void enqueue(person);
  	void dequeue(person &);
  	bool isEmpty() const; 
  	bool isFull() const;
  	void clear();  //removes all elements
    ~IntQueue(); //added destructor 
};
#endif
