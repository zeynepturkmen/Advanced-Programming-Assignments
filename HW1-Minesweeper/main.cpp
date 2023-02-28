// Zeynep Türkmen - 29541

#include <iostream>
#include <iomanip>     // for setw
#include <vector>     //for the matrices
#include "randgen.h" // to set bomb locations randomly

using namespace std;


void Print(const vector<vector<char>> & mat)  //prints the matrix
{
    for (int y = 0; y < mat.size(); y++)
    {
        for (int x = 0; x < mat[0].size(); x++)
        {
            cout << setw(4) << mat[y][x];
        }
        cout << endl;
    }
}

char SurroundingChecker(vector<vector<char>> & mat, int j, int k)
{
    char surrounding = '0';
    unsigned long int y = mat.size()-1;       //denotes the limit index of the matrix on the y axis
    unsigned long int x = mat[0].size()-1;   //denotes the limit index of the matrix on the x axis
    
    
    /*  There are 8 different locations to check around a.
                                 a b c
                                 h X d
                                 g f e
     Important thing to consider is that some of those can be out of the limits of the matrix.
     Each if statement checks one of those 8 different locations (until/if I come up with sth better)
     The if checks prevent the code from exceeding those limits. */
    
    
    if ((j-1) >= 0 && (k-1) >= 0 ) //if its within the limits, it checks location a
        
    {
        if (mat[j-1][k-1] == 'B')  //and if it is a bomb
            surrounding++;          //increments the value
    }
    if ((j-1) >= 0) //similarly, checks b
    {
        if (mat[j-1][k] == 'B')
            surrounding++;
    }
    if ((j-1) >= 0 && (k+1) <= x) //checks c
    {
        if (mat[j-1][k+1] == 'B')
            surrounding++;
    }
    if ((k+1) <= x) //checks d
    {
        if (mat[j][k+1] == 'B')
            surrounding++;
    }
    if ((j+1) <=y && (k+1) <=x) //checks e
    {
        if (mat[j+1][k+1] == 'B')
            surrounding++;
    }
    if ((j+1) <= y ) //checks f
    {
        if (mat[j+1][k] == 'B')
            surrounding++;
    }
    if ((j+1) <= y && (k-1) >= 0) //checks g
    {
        if (mat[j+1][k-1] == 'B')
            surrounding++;
    }
    if ((k-1) >= 0) //checks h
    {
        if (mat[j][k-1] == 'B')
            surrounding++;
    }
    return surrounding; //returns the total bomb count in the surrounding cells
}


void btsMaker(vector<vector<char>> & mat) //checks for the bombs in the surroundings of all cells and updates                                             the numbers accordingly, filling the bts matrix
{
    for (int j = 0; j < mat.size(); j++)
    {
        for (int k = 0; k < mat[0].size(); k++) //goes through all elements of the matrix
        {

            if (mat[j][k] != 'B') //If the current element is not a bomb, it checks all possible surroundings
            {
                mat[j][k] = SurroundingChecker(mat, j, k); //fills the matrix
            }
        }
    }
}

int main()
{
    int y, x; //dimensions of the matrix determined by the user
    cout << "Give the dimensions of the matrix: ";
    cin >> y >> x ;
    cout << endl;
    
    int bombcount;
    
    cout << "How many bombs: ";
    cin >> bombcount;
    
    while (!(0 < bombcount && bombcount < y * x)) //repeats until the user enters a valid value, assuming user doesn't enter 1 both for row and column (would create an infinite loop)
    {
        if (bombcount < 1)
            cout << "The number of bombs could not be less than one. Please give the number of bombs again: ";
        else
        {
            cout << "The number of bombs can not be greater than the whole number of cells minus one. Please give the number of bombs again: ";
            
        }
        cin >> bombcount;
    }

    vector<vector<char>> bts(y, vector<char>(x, '0'));   //to hold the bombs and numbers (works behind the scenes)
    vector<vector<char>> display(y, vector<char>(x, 'X'));  //to display to the user without revealing bts
    
    RandGen r;
    int g, h;
    int i=1;
    
    while( i <= bombcount) //adds bombs in random locations until the required amount is met
    {
        g = r.RandInt(y); //picks the row randomly
        h = r.RandInt(x); //picks the column randomly
        
        if (bts[g][h] != 'B') //if it doesn't already have a bomb
        {
            bts[g][h] = 'B'; //adds the bomb
            i++; //increments the number of added bombs
        }
    }
    
    btsMaker(bts); //fill the non-bomb cells with the calculated mine count
    cout << endl << endl << endl;
    Print(display);

    bool flag = true; //check if user steps on a mine or chooses to exit
    int y1, x1, count = 0; //count of the opened cells, user inputted coordinates
    char option;
    
    while (flag && count != (y * x - bombcount))
    {   cout << endl << endl << endl;
        cout << "Press: " << endl << "1. If you want to find out the surrounding of a cell" << endl << "2. If you want to open the cell" << endl << "3. If you want to exit." << endl;
        cin >> option;
        
        while (!(option == '1' || option == '2' || option == '3'))
        {
            cout << "Your input is wrong. Please select one of the options: 1, 2 or 3." << endl;
            cin >> option;
        }
    
        if (option == '1')
        {
            cout << "Give the coordinates: ";
            cin >> y1 >> x1;
            
            while (!(y1 >= 0 && y1 <= y-1 && x1 >= 0 && x1 <= x-1))
            {
                cout << "It is out of range. Please give a valid coordinates: ";
                cin >> y1 >> x1;
            }
            
            cout << endl << endl;
            cout << "Displaying the surrounding of (" << y1 << "," << x1 << "): "<< endl;
            
            char surrounding = '0';
           
            if (bts[y1][x1] != 'B') //if the selected cell is not a bomb
            {
                surrounding = bts[y1][x1]; //save the corresponding value from bts matrix as we already calculated
            }
            else //its a bomb
            {
                surrounding = SurroundingChecker(bts, y1, x1); //check surroundings and store the value temperarily
            }
            for (int j = 0; j < display.size(); j++) //prints display matrix, changing the selected cell with calculated value
            {
                for (int k = 0; k < display[0].size(); k++)
                {
                    if (j == y1 && k == x1)
                    {
                        cout << setw(4) << surrounding; //the user selected cell, prints the calculated value
                    }
                    else
                    {
                        cout << setw(4) << display[j][k];
                    }
                }
                cout << endl;
            }
            cout << endl << endl << endl;
            cout << "Around (" << y1 << "," << x1 << ") you have " << surrounding << " bomb(s)";
            
        }
        else if (option == '2')
        {
            cout << "Give the coordinates: ";
            cin >> y1 >> x1;
            while (!(y1 >= 0 && y1 <= y-1 && x1 >= 0 && x1 <= x-1))
            {
                cout << "It is out of range. Please give a valid coordinates: ";
                cin >> y1 >> x1;
            }
            cout << "Opening cell (" << y1 << "," << x1 << "): "<< endl;
            
            if (display[y1][x1] != bts[y1][x1]) //if its not already open
            {
                display[y1][x1] = bts[y1][x1]; //open it (change its value to the bts value)
                
                if (display[y1][x1] != 'B') //if not a bomb
                {
                   count ++; //increment the number of opened cells
                }
            }
            
            Print(display); //display the adjusted matrix to the user
            cout << endl;
            
            if (display[y1][x1] == 'B') //if picked a bomb cell
            {
                cout << "Unfortunately, you stepped on a mine" << endl;
                cout << "Arrangement of mines: " << endl;
                
                Print(bts);
                flag = false; //to end the game loop
                cout << endl << ">>>>> Game Over! <<<<<" << endl;
            }
            
            
        }
        else
        {
            cout << "Program exiting ..." << endl;
            flag = false; //to end the game loop
        }
    }
    
    if (count == (y * x) - bombcount) //if the user won by opening all non-bomb cells
    {
        cout << "Congratulations! All the non-mined cells opened successfully" << endl;
        cout << "You won!" << endl;
        cout << endl << ">>>>> Game Over! <<<<<" << endl;
    }
    
    cin.ignore();
    cin.get();
    
    
    return 0;
}
