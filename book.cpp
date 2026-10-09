#ifndef BOOK_H
#define BOOK_H

#include <string>

using namespace std;

class Book {
private:
    string title;
    string author;
    string isbn;
    bool isAvailable;
    string borrowerId;

public:
    // Constructors
    Book() {
        this->title = "";
        this->author = "";
        this->isbn = "";
        this->isAvailable = false;
        this->borrowerId = "";
    }
    Book(const string& title, const string& author, const string& isbn){
        this->title = title;
        this->author = author;
        this->isbn = isbn;
        this->isAvailable = false;
        this->borrowerId = "";
    }

    // Getters
    string getTitle() const{
        return this->title;
    }
    string getAuthor() const{
        return this->author;
    }
    string getISBN() const{
        return this->isbn;
    }
    bool getAvailability() const{
        return this->isAvailable;
    }
    string getBorrowerId() const{
        return this->borrowerId;
    }

    // Setters
    void setTitle(const string& title){
        this->title = title;
    }
    void setAuthor(const string& author){
        this->author = author;
    }
    void setISBN(const string& isbn){
        this->isbn = isbn;
    }
    void setAvailability(bool available){
        this->isAvailable = available;
    }
    void setBorrowerId(const string& id){
        this->borrowerId = id;
    }

    // Methods
    void checkOut(const string& borrowerId){}
    void returnBook(){}
    string toString() const{return "";}
    string toFileFormat() const{return "";}
    void fromFileFormat(const string& line){}
};

#endif
