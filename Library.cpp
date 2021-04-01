//
// Created by ericc on 3/28/2021.
//

#include "Library.h"

#include <utility>




//----------------------------------------------------------------------------------------------------------------------

// Objects for the user input when adding books into the library inventory
string u_isbn;
string u_title;
string u_author;
int u_copyr_yr;
char u_checkin;
char chckOut;
const int frst3Isbn = 5;
Genre u_genre;
string us_genre;

// Misc Variables
char prompt = '>';
string menuOption;
bool u_continue = true;
char i_continue; // For when user is prompted to ask whether they want to continue with program or not

vector<Book> inventory;

//----------------------------------------------------------------------------------------------------------------------

string hey(){
    string test = "Hey what's up my guy";
    return test;
}



Book::Book(string c_isbn, string c_title, string c_author, int c_copyr_yr, char c_checkin, Genre c_genre) {
    for (int i = 0; i < frst3Isbn; i += 2) {
        if (!isdigit(c_isbn[i])){
            error("This is meant to be a digit. Format for ISBN is X-X-X-S where S is digit or letter!");
        }
        if (i != 0 && c_isbn[i-1] != '-'){ // PENDING check this to make sure it works for all variations of incorrect ISBN
            error("This is meant to be a dash. Format for ISBN is X-X-X-S where S is digit or letter!");
        }
    }
    isbn = move(c_isbn); // These may cause an error, need to look further into move()
    title = move(c_title);
    author = move(c_author);
    copyr_yr = c_copyr_yr;
    checkin = c_checkin;
    genre = c_genre;
    // Validate the data for each of these data members and throw error if are not valid
}

Book::Book() {
    isbn = "1-1-1-x";
    title = "Default Book";
    author = "Default Author";
    copyr_yr = 2000;
    checkin = 'y'; // This may need to be set to false then flagged true once the object is properly defined?
    genre = Genre::fiction;
}


Genre genreCheck(const string& s){
    if (s == "fiction"){
        Genre genreChoice = Genre::fiction;
        return genreChoice;
    }
    else if (s == "nonfiction"){
        Genre genreChoice = Genre::nonfiction;
        return genreChoice;
    }
    else if (s == "periodical"){
        Genre genreChoice = Genre::periodical;
        return genreChoice;
    }
    else if (s == "biography"){
        Genre genreChoice = Genre::biography;
        return genreChoice;
    }
    else if (s == "children"){
        Genre genreChoice = Genre::children;
        return genreChoice;
    }
    else {
        error("This Genre type is not acceptable, please try again!");
    }

    return Genre::children; // PENDING remove this, need to make this be fine without a return type or something if all these are incorrect
}

void genrePrint(Genre g){
    switch (static_cast<underlying_type<Genre>::type>(u_genre)) {
        case 0:
            cout << "Fiction";
            break;
        case 1:
            cout << "Non-Fiction";
            break;
        case 2:
            cout << "Periodical";
            break;
        case 3:
            cout << "Biography";
            break;
        case 4:
            cout << "Children";
            break;
        default:
            error("Uhhh, this happened in the genrePrint function idk why");
    }
}

void NewBook(){
    cout << "You are adding a new book into the libraries inventory system.\n";
    cout << "Books ISBN: ";
    cin >> u_isbn;

    // Overloaded operator to check if the ISBN equals any of those already inside the library database
    if (!inventory.empty()) {
        for (int i = 0; i < inventory.size(); ++i) {
            if (u_isbn == inventory[i].isbnPrnt()){
                error("This book's ISBN matches another in our inventory by the name ", inventory[i].isTitle());
                cout << '\n';
            }
        }
    }
    cout << "Books Title: ";
    //This is working! Basically, when I use 'enter' after putting in the ISBN the \n is carried into the stream as garbage, so needs to be removed otherwise getline just grabs it and finishes
    cin.ignore(100,'\n');
    getline(std::cin, u_title);

    cout << "Books Author: ";
    //cin.ignore(100,'\n'); <--- This is not required, as it is not following a cin >> where the users enter aka '\n' is stored and carried over
    getline(cin,u_author);

    cout << "Books Genre (fiction, nonfiction, periodical, biography, children): ";
    cin >> us_genre;
    u_genre = genreCheck(us_genre); // Defines the genre type correctly into the enum class


    cout << "Books Copyright Year: ";
    cin >> u_copyr_yr;
    cout << "Is the book being inserted into inventory? (y/n): ";
    cin >> u_checkin;

    inventory.push_back(Book(u_isbn, u_title, u_author, u_copyr_yr, u_checkin, u_genre));
    cout << "Book inserted into library inventory.\n";

    // cout << inventory[0].isbnPrnt();   <---- how to print out the parts of the book once found in "Search"
}

void CheckOut(){
    cout << "Enter the Author name to find & check out your book: ";
    cin.ignore(5,'\n');
    getline(cin, u_author);

    for (int i = 0; i < inventory.size(); ++i) {

        if (u_author == inventory[i].isAuthor()) {
            cout << "Book's ISBN: " << inventory[i].isbnPrnt() << '\n';
            cout << "Book's Title: " << inventory[i].isTitle() << '\n';
            cout << "Book's Copyright Year: " << inventory[i].iscopyr_yr() << "\n\n";
            cout << "Do you want to check this book out (y/n): "; cin >> chckOut;
            if (chckOut == 'n'){
                continue;
            }
            if (inventory[i].ischeckin() == 'n') {
                cout << "Sorry, this book is already checked out. Come back in 2-3 days time.\n";
            }
            else {
                inventory[i].checkout();
                cout << "\nYou have successfully checked out: " << inventory[i].isTitle() << '\n';
            }
        } else {
            cout << "This Author does not exist in our inventory, sorry!\n";
        }
    }
}

void Search(){
    cout << "Enter the Author name to search for your book: ";
    cin.ignore(5,'\n');
    getline(cin, u_author);


    if (inventory.empty())
    {
        cout << "Sorry, the libraries database currently has no books in it!\n";
    }
    else {
        for (int i = 0; i < inventory.size(); ++i) {

            if (u_author == inventory[i].isAuthor()) {
                cout << "Book's ISBN: " << inventory[i].isbnPrnt() << '\n';
                cout << "Book's Title: " << inventory[i].isTitle() << '\n';
                cout << "Book's Genre: "; genrePrint(inventory[i].isGenre()); cout << '\n';
                cout << "Book's Copyright Year: " << inventory[i].iscopyr_yr() << '\n';
                cout << "Is booked available: ";
                if (inventory[i].ischeckin() == 'y') {cout << "Yes\n";} else {cout << "No\n";}
            } else {
                cout << "This Author does not exist in our inventory, sorry!\n";
            }
        }
    }
}

void Begin(){
    cout << "\nWelcome to the library inventory manager!\n" << "Type the following options: NewBook, CheckOut, or Search\n";
    cout << prompt; cin >> menuOption;
}
