//
// Created by ericc on 3/28/2021.
//

#include "C:/Development/Libraries/std_lib_facilities.h"

#pragma once


string hey();

enum class Genre {
    fiction, nonfiction, periodical, biography, children

};

// Objects for the user input when adding books into the library inventory
extern string u_isbn;
extern string u_title;
extern string u_author;
extern int u_copyr_yr;
extern char u_checkin;
extern char chckOut; // For when the user is prompted if they want to check the book out
extern const int frst3Isbn; // The first 3 digits in the ISBN X-X-X-S where X have to be digits and S can be digit or string
extern Genre u_genre;
extern string us_genre;

// Misc Variables
extern char prompt;
extern string menuOption;
extern bool u_continue;
extern char i_continue; // For when user is prompted to ask whether they want to continue with program or not




//-----------------------------------------------------------------------------------------
class Book{
public:
    Book(string c_isbn, string c_title, string c_author, int c_copyr_yr, char c_checkin, Genre c_genre);
    Book();
    [[nodiscard]] string isbnPrnt() {return isbn;}
    [[nodiscard]] string isAuthor() {return author;}
    [[nodiscard]] string isTitle() {return title;}
    [[nodiscard]] int iscopyr_yr() const {return copyr_yr;} // nodiscord basically says, "Hey, this return value should not be ignored" aka because its the *only* purpose of this function to use it
    [[nodiscard]] char ischeckin() const {return checkin;}
    [[nodiscard]] Genre isGenre() const {return genre;}
    void checkout() {checkin = 'n';}

private:
    string isbn;
    string title;
    string author;
    int copyr_yr; // Year in which the book was copyrighted.
    char checkin; // Set to true/false depending on if the booked is checked in/out of stock
    Genre genre;


    bool operator==(const Book &rhs) const{
        if (u_author == rhs.isbn){
            return true;
        }
        else {
            return false;
        }
    }


};
//-----------------------------------------------------------------------------------------




// Core Functions
extern Genre genreCheck(const string& s); // Takes the users string input, returns it based on the enum class int # then converts into string
extern void genrePrint(Genre g);
extern void Begin();
extern void CheckOut();
extern void Search();
extern void NewBook();
extern vector<Book> inventory;