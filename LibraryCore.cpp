#include "Library.h"


int main() {

  // Create new book object -> enter information -> add into vector.

    try {
        while (u_continue) { // While loop for the core main menu

            Begin();


            if (menuOption == "NewBook") // Adding a new book into inventory
            {
                NewBook();

            }
            else if (menuOption == "CheckOut") // User wants to check out a book
            {
                CheckOut();
            }
            else if (menuOption == "Search") // User wants to search for a book and have all its info presented
            {
                Search();
            }
            else
            {
                cout << "Incorrect menu option, please enter the options presented to you at the start of the program\n";
            }

            cout << "Would you like to execute another action?(y/n): "; cin >> i_continue;

            if (i_continue == 'n')
            {
                u_continue = false;
            }

        }
    }
    catch (const runtime_error& error) {
        cout << '\n' << "ERROR: "<< error.what();
        Begin();
    }
    

    return 0;
}
