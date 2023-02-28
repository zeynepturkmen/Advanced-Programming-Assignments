//Zeynep Turkmen - 29541

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct busStop //given struct with added constructor
{
       string busStopName;
       busStop *left;
       busStop *right;
    busStop::busStop(string stopname, busStop * l = NULL, busStop * r = NULL)
    {
        left = l;
        right = r;
        busStopName = stopname;
    }
};

struct busLine //given struct with added constructor
{
       string busLineName;
       busLine *next;
       busStop *busStops;
    busLine::busLine(string name, busLine * n = NULL, busStop * Stops = NULL)
    {
        busLineName = name;
        next = n;
        busStops = Stops;
    }
};

busLine * head = nullptr; //global variable to keep the head

bool consistencyCheck()
{
    busLine* currBL = head;
    while(currBL)
    {
        busStop* currBS = currBL->busStops;
        while(currBS)
        {
            busStop* rightBS = currBS->right;
            if(rightBS && rightBS->left != currBS)
            {
                cout << "Inconsistency for " << currBL->busLineName << " " << currBS->busStopName << endl;
                return false;
            }
            currBS = currBS->right;
        }
        currBL = currBL->next;
    }
    return true;
}

void printMainMenu()
{
    cout << endl;
    cout <<"I***********************************************I" << endl
         <<"I 0 - EXIT PROGRAM I" << endl
         <<"I 1 - PRINT LINES I" << endl
         <<"I 2 - ADD BUS LINE I" << endl
         <<"I 3 - ADD BUS STOP I" << endl
         <<"I 4 - DELETE BUS LINE I" << endl
         <<"I 5 - DELETE BUS STOP I" << endl
         <<"I 6 - PATH FINDER I" << endl
         <<"I***********************************************I" << endl
         <<">>";
    cout << endl;
}

busLine * prevBusLine (string name) //returns the previous busLine if it exists, otherwise it returns NULL
{
    busLine * temp = head;
    while (temp != NULL)
    {
        if (temp->next->busLineName == name)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void printSingleLine(busLine * temp) //given a BusLine, it prints the name of the busline and all the stops it has
{
    busStop * ptr;
    cout << temp->busLineName << ": ";
    ptr = temp->busStops;
    
    while (ptr->right != NULL)
    {
        cout << ptr->busStopName << "<->";
        ptr = ptr->right;
    }
    cout << ptr->busStopName << endl;
}

void printBusLines() //goes over the whole linkedlist and prints every line using the previous function
{
    busLine * temp = head;
    while(temp != NULL)
    {
        printSingleLine(temp);
        temp = temp->next;
    }
}

busStop * BusStopLocation(busLine * temp, string name) //given the name of the bus stop and the busline it is in, the function returns a ptr that points to the requested stop (returns NULL if it does not exist)
{
    busStop * ptr = temp->busStops;
    while (ptr)
    {
        if(ptr->busStopName == name)
            return ptr;
        ptr = ptr->right;
    }
    return NULL;
}

busLine * BusLineLocation(string name) //Given the name of the busline, it returns a ptr that points to it (NULL otherwise)
{
    busLine * temp = head;
    while (temp)
    {
        if (temp->busLineName == name)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void deleteSingleLine(busLine * temp) //deletes a single line without messing with the list
{
    busStop * ptr = temp->busStops;
    delete temp;
    while (ptr->right != NULL)
    {
        ptr = ptr->right;
        delete ptr->left;
    }
    delete ptr;
}

void LineDelete(busLine * temp) //deletes the given busline with its stops while keeping the list linked
{
    if (temp == head) //the head needs to be modified
    {
        head = temp->next; //modify the head
        busStop * ptr;
        ptr = temp->busStops;
        while (ptr->right != NULL) //deletes the bus stops
        {
            ptr = ptr->right;
            delete ptr->left;
        }
        delete ptr;
    }
    else //if its not the head
    {
       busLine * prev = prevBusLine(temp->busLineName); //find its prev node
       prev->next = prev->next->next; //connect the prev node to the next node in order to remove a line and keep the list linked
        deleteSingleLine(temp);
    }
}

void addBusLine()
{
    string busline,stop;
    
    cout << "Enter the name of the new bus line (0 for exit to main menu).";
    cin >> busline;

    if (busline != "0") //if the user does not exit
    {
        while (BusLineLocation(busline) != NULL) //check if it exists in the current list
        {
            cout << "Bus line already exists: enter a new one (0 for exit)";
            cin >> busline;
            if (busline == "0")
                return;
        } //keeps going until it gets a valid name or 0 for exit
        
        cout << "Enter the name of the next bus stop (enter 0 to complete)";
        cin >> stop;
        if (stop == "0") //if the first stop entered is 0, it exits
        {
            cout << "You are not allowed to add an empty bus line" << endl;
            return;
        }
        else
        {
            busStop * ptr = new busStop(stop);
            busLine * temp = new busLine(busline, NULL, ptr);
            
            while (stop != "0")
            {
               cout << "Enter the name of the next bus stop (enter 0 to complete)";
               cin >> stop;
                
               if (BusStopLocation(temp, stop) != NULL) //if it was added
               {
                   cout << "Bus stop already exists in the line" << endl;
               }
               else if (stop != "0")
               {
                   ptr->right = new busStop(stop); //create a new node
                   ptr->right->left = ptr; //connect it to the rest
                   ptr = ptr -> right; //increment the ptr
               }
            }
            char sure;
            cout << "The bus line information is shown below" << endl;
            printSingleLine(temp); //prints the created line
            cout << "Are you sure? Enter (y/Y) for yes (n/N) for no?" << endl;
            cin >> sure;
            
            if (sure == 'Y' || sure == 'y')
            {
                temp -> next = head; //connect it to the beginning of the list
                head = temp;
            }
            else //delete the line user created but did not wanna add for some reason
                deleteSingleLine(temp);
        }
    }
}

void addBusStop()
{
    string name;
    cout << "Enter the name of the bus line to insert a new bus stop (0 for main menu)" << endl;
    cin >> name;

    if (name != "0") //if the user did not ezit
    {
        busLine * temp = BusLineLocation(name); //find the busline location
      
        if (temp != NULL) //if it finds the busline
        {
            cout << "The bus line information is shown below" << endl;
            printSingleLine(temp);
            cout << "Enter the name of the new bus stop" << endl;
            cin >> name;
            
            if (BusStopLocation(temp, name) != NULL) //if bus stop already exists
            {
                cout << "Bus stop already exists. Going back to previous menu." << endl;
            }
            else
            {
                string desired;
                cout << "Enter the name of the previous bus stop to put the new one after it (0 to put the new one as the first bus stop)" << endl;
                cin >> desired; //the desired location to put the bus stop
                
                if (desired == "0") //add to beginning
                {
                    busStop * ptr = new busStop(name); //new node to insert
                    temp->busStops->left = ptr; //connect the next node to the new one
                    ptr->right = temp->busStops; //connect this node to the next one
                    temp ->busStops = ptr; //connect it to the busline
                }
                while(desired != "0") //add to a desired location
                {
                    busStop * ptr = BusStopLocation(temp, desired);
                    if(ptr != NULL && ptr->right != NULL) //it found the desired location and its somewhere in the middle (there are 4 pointers to connect)
                    {
                        busStop * ptr2 = new busStop(name);
                        ptr2->right = ptr->right;
                        ptr2->right->left = ptr2;
                        ptr2->left = ptr;
                        ptr->right = ptr2;
                        break;
                    }
                    else if (ptr->right == NULL) //its the last bus stop (there are 2 pointers to connect)
                    {
                        busStop * ptr2 = new busStop(name);
                        ptr->right= ptr2;
                        ptr2->left = ptr;
                        break;
                    }
                    else //it couldnt find the desired loc
                    {
                        cout << "Bus stop does not exist. Typo? Enter again (0 for main menu)" << endl;
                        cin >> desired;
                    }
                }
            }
        }
        else
            cout << "Bus line cannot be found. Going back to previous menu." << endl;
    }
}

void deleteBusLine()
{
    string name;
    cout << "Enter the name of the bus line to delete" << endl;
    cin >> name;
    
    busLine * temp = BusLineLocation(name); //finds the location of the line to be deleted
    if (temp == NULL)
        cout << "Bus line cannot be found. Going back to the previous (main) menu." << endl;
    else
        LineDelete(temp); //deletes the line
}

void deleteBusStop()
{
    string name;
    cout << "Enter the name of the bus line to delete a new bus stop (0 for main menu)" << endl;
    cin >> name;
    
    if (name != "0") //if user does not exist
    {
        busLine * temp = BusLineLocation(name); //location of busline
        
        if(temp == NULL)
        {
            cout << "Bus line cannot be found. Going back to previous (main) menu." << endl;
        }
        else //if the busline is found
        {
            cout << "The bus line information is shown below" << endl;
            printSingleLine(temp); //print the busline
            bool flag = true; //to keep track of deletion
            string stop;
            while (flag)
            {
                cout << "Enter the name of the bus stop to delete (0 for main menu)" << endl;
                cin >> stop;
                if (BusStopLocation(temp, stop) == NULL && stop != "0")
                    cout << "Bus stop cannot be found. ";
                else
                    flag = false;
            }
            //after we get a valid name or 0 to exit
            if(stop != "0") //if we exited cuz we got a valid name
            {
                busStop * ptr = BusStopLocation(temp,stop);
                if (temp->busStops == ptr && ptr->right == NULL) //if it is the only busstop in a line
                {
                    LineDelete(temp);
                }
                else if(temp->busStops == ptr) //its the one right after temp
                {
                    temp->busStops = ptr->right;
                    ptr->right->left = NULL;
                    delete ptr;
                }
                else if (ptr->right == NULL) //if its the last one
                {
                    ptr->left->right = NULL;
                    delete ptr;
                }
                else //its somewhere in the middle
                {
                    ptr->left->right = ptr->right;
                    ptr->right->left = ptr->left;
                    delete ptr;
                }
            }
        }
    }
}

void pathfinder()
{
    string start, stop;
    cout << "Where are you now ?" << endl;
    cin >> start;
    cout << "Where do you want to go ?" << endl;
    cin >> stop;
    
    busStop * ptr, * startloc = NULL, * stoploc = NULL;
    busLine * temp = head, * busname = NULL;
    
    bool flag = false, findStart = false, findStop = false;
    int cstart, cstop, count; //checks to see if we got the starting point before the stopping point -> helps us to see which direction the bus will take
    
    while (temp != NULL && !flag)
    {
        startloc = NULL;
        stoploc = NULL;
        count = 0;
        
        for (ptr = temp->busStops; ptr != NULL && flag == false ; ptr = ptr->right ) //in a busline it looks for the stop and start points
        {
               if(ptr->busStopName == start)
               {
                   startloc = ptr;
                   cstart = count;
                   findStart=true; //record that you found the starting bus stop
               }
               else if (ptr->busStopName == stop)
               {
                   stoploc = ptr;
                   busname = temp;
                   cstop = count;
                   findStop=true; //record that you found the stopping bus stop
               }
            if (stoploc != NULL && startloc != NULL) //if we got both busstops in the sameline
                flag = true;
        count++;
        }
        temp = temp->next;
    }
    
    if(!findStart && !findStop) //if either of the stops were never found
    {
        cout << "Bus stop does not exist in the table. Going back to previous menu.";
    }
    else
    {
        if (flag == true) //if we found both in the same line
        {
            cout << "You can go there by " << busname->busLineName << ":";
    
            if (cstart < cstop) //if start was found first
            {
               while (startloc != stoploc)
               {
                   cout << startloc->busStopName << "->";
                   startloc = startloc->right; //we go in the right direction
               }
                cout << stoploc->busStopName;
            }
            else //stop was found first
            {
                while (startloc != stoploc)
                {
                    cout << startloc->busStopName << "->";
                    startloc = startloc->left; //we go in the left direction
                }
                 cout << stoploc->busStopName;
            }
        }
        else //they were not found in the same bus line
        {
            cout << "Sorry no path from " << start << " to " << stop << " could be found"<< endl;
        }
    }
}

void processMainMenu() //given in the hw document
{
    char input;
    do
    {
        if(!consistencyCheck())
        {
            cout << "There are inconsistencies. Exit." << endl;
            return;
        }
        printMainMenu();
        cout << "Please enter your option " << endl;
        cin >> input;
        
        switch (input)
        {
            case '0':
                    cout << "Thanks for using our program" << endl;
                    return;
            case '1':
                    printBusLines();
                    break;
            case '2':
                    addBusLine();
                    break;
            case '3':
                    addBusStop();
                    break;
            case '4':
                    deleteBusLine();
                    break;
            case '5':
                    deleteBusStop();
                    break;
            case '6':
                    pathfinder();
                    break;
            default:
            cout << "Invalid option: please enter again" << endl;
        } //switch
    } while (true);
}

void terminator() //terminates the list to avoid memory leaks
{
    while (head != NULL)
        LineDelete(head);
}

int main()
{
    string filename = "busLines.txt";
    fstream input;
    input.open(filename.c_str());
    
    string line, busname, stop;
    
    busLine * temp = NULL;
    busStop * ptr = NULL;
    
    while (getline(input, line))
    {
        istringstream ss(line); //to read the line word by word
        ss >> busname;
        busname = busname.substr(0,busname.length()-1); //to get rid of ;
        
        if (head == NULL) //if nothing was added before
        {
            temp = new busLine(busname);
            head = temp;
        }
        else
        {
            temp->next = new busLine(busname);
            temp = temp->next;
        }
        ss >> stop;
        temp->busStops = new busStop(stop);
        ptr = temp->busStops;
        
        while(ss >> stop) //until the end of bus stops
        {
            ptr->right = new busStop(stop); //create a new node
            ptr->right->left = ptr; //connect it to the rest
            ptr = ptr -> right;
        }
    }
    processMainMenu();
    terminator();

    return 0;
}
