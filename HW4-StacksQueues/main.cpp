// Zeynep Turkmen - 29541

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "IntQueue.h" //From the lecture codes, to use with instructors que (modified to store more information (added struct) and added a destructor)
#include "DynamicStringQueue.h" //From the lecture codes, to use with students que (modified the QueNode to have more values, and added a destructor)
#include "strutils.h" //only for stripping white characters (felt like using it)
#include "DynamicStringStack.h" //From the lecture codes, to create the main stack (not modified)

using namespace std;

struct node
{
    string info;
    node * down;
    node * right;
    node(string i, node * d = NULL, node * r = NULL)
    {
        down = d;
        right = r;
        info = i;
    }
    node()
    {
      //default constructor
    }
};

node * head = NULL; //head for the list that consists of available functions and their contents
DynamicStringQueue studentQue = DynamicStringQueue(); //unknown amount of students hence the dynamic que
IntQueue instructorQue = IntQueue(5); //known amount of instructors hence the static que (hoca said 5 is enough)
DynamicStringStack theStack = DynamicStringStack(); //to store all the data

node * functionFinder(string function) //checks if a function exists within the inputted information
{
    node * ptr = head;
    while (ptr)
    {
        if (ptr->info == function)
            return ptr; //returns a pointer pointing to it (if found)
        ptr = ptr->right;
    }
    return NULL; //returns NULL if it was not found
}

void printStack() //prints the data stack without messing with its order
{
    string a; //dummy string to store the value
    DynamicStringStack dummy; //dummy stack to keep the values
    
    while (!theStack.isEmpty())
    {
        theStack.pop(a);
        dummy.push(a);
    }
    while (!dummy.isEmpty())
    {
        dummy.pop(a);
        cout << a << endl; //print the value
        theStack.push(a); //push the values back in
    }
}

void stackClearer(string functionName) //clears the stack from the given function
{
    string dummy,name;
    if (!theStack.isEmpty()) //no need to do anything if the stack is empty
    {
        theStack.pop(dummy); //pop a value, its something like function_a: define b
        istringstream ss(dummy); //we need to seperate it to get only the function name
        ss >> name; //now name = function_a:
        name = name.substr(0,name.length()-1); //we get rid of the ":"
        
        while (name == functionName && !theStack.isEmpty()) //if the popped function is the same as inputted one
        {
            theStack.pop(dummy); //we remove another one
            istringstream ss(dummy);
            ss >> name;
            name = name.substr(0,name.length()-1); //get another name
        } //after the while loop we popped one unnecessary value
        if (!theStack.isEmpty())
            theStack.push(dummy); //we pop it back in
        else
            cout << "The stack is empty." << endl;
    }
}

void addStudentRequest()
{
    string function, name;
    int id;
    
    cout << "Add a service <function> that the student wants to use: ";
    cin >> function;

    if (functionFinder(function) != NULL) //if it is found
    {
        cout << "Give student's name: ";
        cin >> name;
        cout << "Give student's id: ";
        cin >> id;
        
        studentQue.enqueue(name, function, id); //modified function from the DynamicStringQue class to store all 3 values
        
        cout << name << "'s request of " << function << " has been put in the student's queue." << endl;
        cout << "Waiting to be served..." << endl;
    }
    else
    {
        cout << "The requested service <function> does not exist." << endl;
        cout << "GOING BACK TO MAIN MENU" << endl;
    }
}

void addInstructorRequest()
{
    string function, name;
    int id;
    
    cout << "Add a service <function> that the instructor wants to use: " ;
    cin >> function;

    if(functionFinder(function) != NULL) //if the function is found
    {
        cout << "Give instructor's name: ";
        cin >> name;
        cout << "Give instructor's id: ";
        cin >> id;
        
        person p(name,function,id); //create a person
        instructorQue.enqueue(p);   //modified the static que class to have an array of persons instead. (wanted to try structs with classes)
        
        cout << "Prof. " << name << "'s request of " << function << " has been put in the instructor's queue." << endl;
        cout << "Waiting to be served..." << endl;
    }
    else
    {
        cout << "The requested service <function> does not exist." << endl;
        cout << "GOING BACK TO MAIN MENU" << endl;
    }
}

void processARequest(string functionName)
{
     string whatToDo, stackInfo;
     node * ptr = functionFinder(functionName)->down; //points to the first content of a function

    while (ptr != NULL)
    {
        whatToDo = ptr->info; //whatToDo is sth like "define x", "call function_x", "print_stack"
        istringstream ss(whatToDo); //turn it into stringstream to read word by word
        string code,value;
        ss >> code; //read the code giving us what to do
        
        if(code == "define")
        {
            ss >> value; //read the second word and assign it to value
            stackInfo = functionName + ": " + code + " " + value; //create a stack info sth like "function_1: define x"
            theStack.push(stackInfo); //push the info into the stack
        }
        else if (code == "call")
        {
            string secondFunction;
            ss >> secondFunction; //the name of the second function
            cout << "Calling " << secondFunction << " from " << functionName << endl;
            processARequest(secondFunction); //recursion
        }
        else
        {
            cout << "PRINTING THE STACK TRACE: " << endl;
            if (theStack.isEmpty())
            {
                cout << "The stack is empty."<< endl;
            }
            else
                printStack(); //prints the stack without messing with the order
        }
        ptr = ptr->down; //keeps going through the contents of the function
    }
    
    cout << functionName << " is finished. Clearing the stack from it's data... " << endl;
    stackClearer(functionName); //clears the top of the stack from the finished funciton
    system("pause");
}

void processARequest()
{
    string name, function;
    int id;
    
    if (!instructorQue.isEmpty())
    {
        person p;
        instructorQue.dequeue(p);
        name = p.name;
        id = p.id;
        function = p.request;
        cout << "Processing Prof. " << name << "'s request " << "<with ID " << id << "> of service <function> :" << function << endl;
        processARequest(function);
        cout << "GOING BACK TO MAIN MENU" << endl;
    }
    else if (!studentQue.isEmpty())
    {
        cout << "Instructors queue is empty. Proceeding with students queue..." << endl;
        studentQue.dequeue(name, function, id);
        cout << "Processing " << name << "'s request " << "<with ID " << id << "> of service <function> :" << function << endl;
        processARequest(function);
        cout << "GOING BACK TO MAIN MENU" << endl;
    }
    else
    {
        cout << "Both instructor's and student's queue is empty.\nNo request is processed." << endl;
        cout << "GOING BACK TO MAIN MENU" << endl;
    }
}

void addFile(string filename)
{
    fstream input;
    input.open(filename.c_str());
    string info;
    
    static node * temp = NULL;

    getline(input, info);
    StripWhite(info); //strip the white characters off
    info = info.substr(0,info.length()-1); //removes the ";"
    
    if (temp == NULL) //if nothing was added before
    {
        temp = new node(info);
        head = temp;
    }
    else
    {
        temp->right = new node(info); //new node to its right (contains the function name)
        temp = temp->right;
    }
    node * ptr = temp; //points to the newly added temp
    while (getline(input, info)) //while getting the contents of a function
    {
        StripWhite(info); //strips off "\n"
        info = info.substr(0,info.length()-1); //removes ";"
        ptr->down = new node(info); //new node with the information
        ptr = ptr->down;
    }
    input.close(); //close the file
}

void printList() //prints the functions along with their contents
{
    node * nodePtr = head;
    while (nodePtr != NULL) //runs through the functions
    {
        node * ptr;
        cout << nodePtr->info << ":" << endl;
        ptr = nodePtr->down;
        
        while (ptr->down != NULL) //runs through the contents
        {
            cout << ptr->info << ", ";
            ptr = ptr->down;
        }
        cout << ptr->info << "." << endl << endl;
        nodePtr = nodePtr->right;
    }
}

void destroyer() //destroys the linked list and pretty much everything
{
    while (head != NULL) //runs through the functions
    {
        node * nodePtr = head;
        node * ptr, * del; //dummy pointers for deletion
        ptr = nodePtr->down;
        
        while (ptr != NULL) //runs through the contents of the functions
        {
            del = ptr;
            ptr = ptr->down;
            delete del;
        }
        head = nodePtr->right;
        delete nodePtr;
    }
}

int main()
{
    char choice;
    cout << "If you want to open a service <function> defining file, then press <Y/y> for 'yes', otherwise press any single key " << endl;
    cin >> choice;
    
    string filename; //for the file name
    
    while (choice == 'y' || choice == 'Y')
    {
        cout << "Enter the input file name: ";
        cin >> filename;
        addFile(filename); //adds the file to the linked list
        cout << "Do you want to open another service defining file?" << endl;
        cout << "Press <Y/y> for 'yes', otherwise press anykey " << endl;
        cin >> choice; //users choice
    }
    
    cout << "-----------------------------------------------------------------" << endl;
    cout << "PRINTING AVAILABLE SERVICES <FUNCTIONS> TO BE CHOSEN BY THE USERS" << endl;
    cout << "-----------------------------------------------------------------" << endl;
    cout << endl << endl;
    printList(); //prints the functions and their contents
    while (true) {
        cout << endl;
        cout <<"**********************************************************************"<< endl
             <<"**************** 0 - EXIT PROGRAM                        *************"<< endl
             <<"**************** 1 - ADD AN INSTRUCTOR SERVICE REQUEST   *************"<< endl
             <<"**************** 2 - ADD A STUDENT SERVICE REQUEST       *************"<< endl
             <<"**************** 3 - SERVE (PROCESS) A REQUEST           *************"<< endl
             <<"**********************************************************************"<< endl;
        cout << endl;
        int option;
        cout << "Pick an option from above (int number from 0 to 3): ";
        cin >> option;
        switch (option)
        {
                case 0:
                        cout << "PROGRAM EXITING ... " << endl;
                        destroyer(); //clears the allocated memory by destroying the linked list
                        system("pause");
                        exit(0); //destroyers destroy the staticque and dynamicque
                case 1:
                        addInstructorRequest();
                        break;
                case 2:
                        addStudentRequest();
                        break;
                case 3:
                        processARequest();
                        break;
                default:
                        cout <<"INVALID OPTION!!! Try again" << endl;
            }//switch
    }//while (true)
    return 0;
}
