// Zeynep Turkmen - 29541

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

struct courseNode
{
    string courseCode, courseName;
    vector<int> studentsAttendingIDs;
    courseNode * next;
};

void vecprint(vector<int> vec) //prints the vector
{
    for (int i = 0; i< vec.size(); i++)
    {
        cout << vec[i] << " ";
    }
}

void Printer(courseNode * ptr) //prints the linked list
{
    while (ptr != NULL)
    {
        cout << ptr->courseCode << " " << ptr->courseName << ": ";
        vecprint(ptr->studentsAttendingIDs);
        cout << endl;
        ptr = ptr -> next;
    }
}

void add(vector<int> & vec, int num) //adds numbers to vector while keeping its order
{
    int size = vec.size(); //size of the vector before adding the new
    vec.push_back(num);   //increase the size
    int x = size;        //index to be searched
    while (x > 0 && vec[x-1] > num) //starts from the end, goes until it finds the right place to add the number
    {
        vec[x] = vec[x-1]; //shift the numbers to right
        x--;
    }
    vec[x] = num;  //add the number to the reserved spot
}

int bsearch(const vector<int> & list, const int & key) //binary search algorithm taken from computersciencetapestry (page 377). Modified so that vector consists of integers and key is an integer.
{
    // pre: list.size() == # elements in list
    // post: returns index of key in list, -1 if key not found
    int low = 0;
    int high = list.size()-1; int mid;
    while (low <= high)
    {
        mid = (low + high)/2;
        if (list[mid] == key)
            return mid;
        else if (list[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

void drop(vector<int> & vec, int location) //drops numbers from a sorted vector without breaking the order
{
    int x, y = vec.size()-1;
    for (x = location; x < y; x++) //for all numbers on the right side of location
    {
        vec[x] = vec[x+1]; //shifts the numbers to the left
    }
    
    vec.pop_back(); // deletes the last element
}

void DeleteOneNode (courseNode * toBeDeleted, courseNode * & head) //borrowed from CS204 slides of week 4
/* pre: toBeDeleted points to the node to be deleted from the list
   post: deletes the node pointed by toBeDeleted, updates head if changes */
{
    courseNode * & ptr = head;
    if (toBeDeleted == head)  //if the node to be deleted is the first node
    {     head = head->next;
        delete toBeDeleted;
    }
    else  //if the node to be deleted is in the middle or at the end
    {
        while (ptr->next != toBeDeleted)
            ptr = ptr->next;
        
        //after the while loop, ptr points to the node just before toBeDeleted
        //connect the previous node to the next node and delete toBeDeleted
        ptr->next = toBeDeleted->next;
        delete toBeDeleted;
    }
}

courseNode * AddInOrder(courseNode * head,string name, string code, int id) //borrowed from CS204 slides of week 4, modified for courseNode
{
    courseNode * ptr;
    if (head == NULL || name < head->courseName)
    {
        courseNode * temp = new courseNode;  //new node to insert
        temp->courseName = name;
        temp->courseCode = code;
        temp->studentsAttendingIDs.push_back(id);
        temp->next = head; //connect the rest
        return temp;
    }
    else
    {
        ptr = head;
        while (ptr->next != NULL && ptr->next->courseName < name)
        {
            ptr = ptr->next;
        }
        //after the loop, new node to be inserted just after the node ptr points
        //now insert new node with newkey after where ptr points to
        courseNode * temp = new courseNode;  //node to be inserted
        temp->courseName = name;
        temp->courseCode = code;
        temp->studentsAttendingIDs.push_back(id);
        temp->next = ptr->next; //connect the rest
        ptr->next = temp;
        return head;
    }
}

int main()
{
    string filename;
    cout << "Please enter file name: ";
    cin >> filename;

    ifstream input;
    input.open(filename.c_str());
    cout << "Successfully opened file " << filename << endl;
    
    string line, name, code;
    int id;
    courseNode * head = NULL ; //dont lose the head of our list
    courseNode * ptr; //to use for loops
    
    while(!input.eof())
    {
        getline(input, line);
        istringstream ss(line); //to read word by word
        ptr = head;
        bool flag = true; //flag for if the course is not in our linked list
        
        ss >> code >> name >> id;
        
        while (ptr != NULL && flag) //go over every item in the linked list
        {
            if (ptr->courseCode == code) //if the course is in the list
            {
                add (ptr->studentsAttendingIDs, id); //we only add the corresponding id
                flag = false; //stops the loop
            }
            ptr = ptr->next;
        }
        
        if (flag) //if the course was not already in the list
        {
           head = AddInOrder(head, name, code, id);
        }
    }
    
    cout << "The linked list is created." << endl;
    cout << "The initial list is: "<< endl;

    Printer(head);
    
    int choice = 0;
    
    while (choice != 4) //continues until the user chooses to exit
    {
        cout << "Please select one of the choices: " << endl;
        cout << "1. Add to List" << endl;
        cout << "2. Drop from List" << endl;
        cout << "3. Display List" << endl;
        cout << "4. Finish Add/Drop and Exit" << endl;
        cin >> choice;
        
        if (choice == 1)
        {
            string addstring;
            cin.ignore();
            getline(cin, addstring);
            
            istringstream ss(addstring); //read the input word by word
            
            while (ss >> code)
            {
                ss >> name;
                while (ss >> id) //results true if the input is an integer
                {
                    bool flag = true;
                    ptr = head;
                    while (ptr != NULL && flag)
                    {
                        if (ptr->courseCode == code) //if its in the list
                        {
                            if (bsearch(ptr->studentsAttendingIDs, id)!= -1) //binary search to see if the student is enrolled
                            {
                                cout << "Student with id " << id << " already is enrolled to " << code << ". No action taken." << endl;
                            }
                            else //if student is not enrolled
                            {
                                add (ptr->studentsAttendingIDs, id); //we add the student
                                cout << "Student with id " << id << " is enrolled to " << code << "." << endl;
                            }
                            flag = false; //if its in the list we are done so no need to continue
                        }
                        ptr = ptr->next;
                    }
                    if (flag) //if it wasn't in the list
                    {
                        head = AddInOrder(head, name, code, id); //add the course with the student
                        cout << code << " does not exist in the list of Courses. It is added up." << endl;
                        cout << "Student with id " << id << " is enrolled to " << code << "." << endl;
                    }
                }
                ss.clear(); //if it fails it means we are getting another course code. So we clear the flag and go to the upper loop
            }
        }
        else if (choice == 2)
        {
            string deletestring;
            cin.ignore();
            getline(cin, deletestring);
            
            istringstream ss(deletestring);
            
            while (ss >> code)
            {
                ss >> name;
                while (ss >> id)
                {
                    bool flag = true;
                    ptr = head;
                    while (ptr != NULL && flag)
                    {
                        if (ptr->courseCode == code)
                        {
                            int location = bsearch(ptr->studentsAttendingIDs, id);
                            
                            if (location != -1) //if it is in the vector
                            {
                                drop(ptr->studentsAttendingIDs, location); //we delete it from the vector
                                cout << "Student with id " << id << " has dropped " << code << "." << endl;
                            }
                            else
                            {
                                cout << "Student with id " << id << " is not enrolled to " << code << ", thus he can't drop that course." << endl;
                            }
                            flag = false;
                        }
                        ptr = ptr->next;
                    }
                    if (flag)
                    {
                        cout << "The " << code << " course is not in the list, thus student with id " << id << " can’t be dropped" << endl;
                    }
                }
                ss.clear();
            }
        }
        else if (choice == 3)
        {
            cout << "The current list of course and the students attending them: " << endl;
            Printer(head);
        }
        else if (choice == 4)
        {
            cout << "The add/drop period is finished. Printing the final list of courses and students attending them." << endl;
            cout << " NOTE: Courses with less than 3 students will be closed this semester." << endl;
            
            ptr = head;
            while (head != NULL) //we go over every item in the list
            {
                if (ptr->studentsAttendingIDs.size() < 3) //if the vector has less than 3 elements print it as "closed"
                {
                    cout << ptr->courseCode << " " << ptr->courseName << " ";
                    cout << "-> This course will be closed";
                }
                else
                {
                    cout << ptr->courseCode << " " << ptr->courseName << ": ";
                    vecprint(ptr->studentsAttendingIDs);
                }
                cout << endl;
                ptr = head -> next;
                delete head; //after we are done printing we free the allocated memory
                head = ptr;
            }
        }
    }
    system("pause");
    return 0;
}
