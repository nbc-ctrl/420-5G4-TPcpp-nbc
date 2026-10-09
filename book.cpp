#include "book.h"
#include <string>
#include <iostream>

using namespace std;

// Constructors
Book::Book() {
    this->title = "";
    this->author = "";
    this->isbn = "";
    this->isAvailable = false;
    this->borrowerId = "";
}
Book::Book(const string& title, const string& author, const string& isbn){
    this->title = title;
    this->author = author;
    this->isbn = isbn;
    this->isAvailable = false;
    this->borrowerId = "";
}

// Getters
string Book::getTitle() const{
    return this->title;
}
string Book::getAuthor() const{
    return this->author;
}
string Book::getISBN() const{
    return this->isbn;
}
bool Book::getAvailability() const{
    return this->isAvailable;
}
string Book::getBorrowerId() const{
    return this->borrowerId;
}

// Setters
void Book::setTitle(const string& title){
    this->title = title;
}
void Book::setAuthor(const string& author){
    this->author = author;
}
void Book::setISBN(const string& isbn){
    this->isbn = isbn;
}
void Book::setAvailability(bool available){
    this->isAvailable = available;
}
void Book::setBorrowerId(const string& id){
    this->borrowerId = id;
}

// Methods
void Book::checkOut(const string& borrowerId){}
void Book::returnBook(){}
string Book::toString() const{return "";}
string Book::toFileFormat() const{
    return this->title + "|" 
    + this->author + "|" 
    + this->isbn + "|" 
    + (this->isAvailable ? "1" : "0") + "|" // source : (1)
    + this->borrowerId; 
}
void Book::fromFileFormat(const string& line){

}


// ====== SOURCE(S) ====== 
// (1) : https://stackoverflow.com/questions/11953200/concatenate-a-string-and-a-boolean-in-c