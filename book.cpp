#include "book.h"
#include <string>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

// Constructors
Book::Book() {
    this->title = "";
    this->author = "";
    this->isbn = "";
    this->isAvailable = true;
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
string Book::toString() const{
    return "Titre : " + this->title + "\n" +
    "Auteur : " + this->author + "\n" +
    "ISBN : " + this->isbn + "\n" +
    "Statut : " + (this->isAvailable ? "Disponible" : "Non disponible") + "\n";}
string Book::toFileFormat() const{
    return this->title + "|" 
    + this->author + "|" 
    + this->isbn + "|" 
    + (this->isAvailable ? "1" : "0") + "|" // source : (1)
    + this->borrowerId; 
}
void Book::fromFileFormat(const string& line){
    stringstream ss(line);
    string elem;
    int cmptr = 0;

    while (getline(ss, elem, '|')) {
        cmptr++;
        switch (cmptr) {
            case 1 : 
                this->title = elem;
                break;
            case 2 :
                this->author = elem;
                    break;
            case 3 :
                this->isbn = elem;
                    break;
            case 4 :
                this->isAvailable = ((elem=="1") ? true : false); //!! NE FONCTIONNE PAS, À CORRIGER
                    break;
        }
        cout << elem << endl;
    } // source : (2)
}


// ====== SOURCE(S) ====== 
// (1) : https://stackoverflow.com/questions/11953200/concatenate-a-string-and-a-boolean-in-c
// (2) : https://www.geeksforgeeks.org/cpp/how-to-split-string-by-delimiter-in-cpp/