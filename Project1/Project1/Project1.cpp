// Project1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <climits>
#include <limits>
#include <stdexcept>

using namespace std;

string name1 = "Bob Jones";
string name2 = "Sarah Davis";
string name3 = "Amy Friendly";
string name4 = "Johnny Smith";
string name5 = "Carol Spears";

int num1 = 1;
int num2 = 2;
int num3 = 1;
int num4 = 1;
int num5 = 2;

// vulnerability fixed (partially): adding a username to validate against
string username = "shayne";
string password = "123";

/*
* Function that will validate CIN values
* Throws runtime error if input is not numeric
*
*/
double safeCinDouble() {

    double numValue = 0.0;

    // Checks for a valid cin input (numeric values)
    if (!(cin >> numValue)) {

        // clear the input buffer
        cin.clear();
        // ignore anything in the input buffer until a newline is hit
        // or max streamsize is reached
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // throw an exception to be caught and handled 
        throw runtime_error("Not a valid numeric value.");
    }

    // return the input value if no errors occur
    return numValue;
}

/*
* Check the users permision
* Returns 2 if username / password is not correct
*/

int CheckUserPermissonAccess() {
    string tempUser = "";
    string tempPass = "";

    // Get the username
    cout << "Enter your username:" << endl;
    cin >> tempUser;

    // get the password
    cout << "Enter your password:" << endl;
    cin >> tempPass;

    // vulnerability fixed: Checking both the username and password
    if (tempPass == password && tempUser == username) {
        return 1;
    }
    else {
        return 2;
    }

}

/*
* Display the Clients and choices
*/
void DisplayInfo() {

    cout << " Client's Name    Service Selected (1 = Brokerage, 2 = Retirement)" << endl;

    cout << "1. " << name1 << " selected option " << num1 << endl;
    cout << "2. " << name2 << " selected option " << num2 << endl;
    cout << "3. " << name3 << " selected option " << num3 << endl;
    cout << "4. " << name4 << " selected option " << num4 << endl;
    cout << "5. " << name5 << " selected option " << num5 << endl << endl;
}

/*
*
* Update a clients Service choice
*/
void ChangeCustomerChoice() {
    // Initialize variables with zero to avoid garbage data
    int changechoice = -1;
    int newservice = -1;


    // Validate the choice to the available options.
    while (changechoice < 0 || changechoice > 5) {
        cout << "Enter the number of the client that you wish to change" << endl;
        cout << "(Enter 0 to Exit)" << endl;

        // vulnerability fixed: try / catch block to validate the users input 
        try {
            changechoice = safeCinDouble();
            if (changechoice < 0 || changechoice > 5) {

                // prompt if the client valid is not valid.
                cout << "Please enter a valid client (1-5) or (0) to exit" << endl;
            }
        }

        catch (const runtime_error& e) {
            cerr << e.what() << endl;
        }
        
    }

    // If the selection was not Exit
    if (changechoice != 0) {
        cout << "Please enter the client's new service choice (1 = Brokerage, 2 = Retirement)" << endl;

        newservice = safeCinDouble();

        if (changechoice == 1) {
            num1 = newservice;
        }
        else if (changechoice == 2) {
            num2 = newservice;
        }
        else if (changechoice == 3) {
            num3 = newservice;
        }
        else if (changechoice == 4) {
            num4 = newservice;
        }
        else if (changechoice == 5) {
            num5 = newservice;
        }
    }
}

/*
* Main
*/
int main()
{
    // vulnerability fixed: initializing variables to avoid garbage data
    int answer = 0;
    int choice = 0;

    string banner(45, '-');

    // Display the main banner
    cout << banner << endl;
    cout << "Hello! Welcome to our Investment Company" << endl;
    cout << banner << endl;
    cout << "     Program (re)created by Shayne Greene" << endl << endl;

    // Keep prompting for username and password until password matches
    while (answer != 1) {
        answer = CheckUserPermissonAccess();
        if (answer != 1) {
            // vulnerability fixed?: Adding some obsurity for what was incorrect in the 
            // login attempt
            cout << "Invalid Username or Password.Please try again" << endl;
        }
    }

    // Display the menu until the user exits the program (3)
    while (choice != 3) {
        cout << "What would you like to do?" << endl;
        cout << "DISPLAY the client list(enter 1)" << endl;
        cout << "CHANGE a client's choice (enter 2)" << endl;
        cout << "Exit the program.. (enter 3)" << endl;
        
        
        // vulnerability fixed: Adding a try catch for input validation
        try {

            // vulnerability fixed: Using function that will safely use CIN for 
            // doubles 
            choice = safeCinDouble();
            if (choice < 0 || choice > 3) {
                cout << "Please enter a valid client (1-3)" << endl;
            }
        }
        // Catch that will display the error thrown in  the safeCinDouble method
        catch (const runtime_error& e) {
            cerr << e.what() << endl;
        }

        cout << "You chose " << choice << endl;

        if (choice == 1) {
            DisplayInfo();
        }
        else if (choice == 2) {
            ChangeCustomerChoice();
        }

    }

}

