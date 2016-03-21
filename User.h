//
//  User.h
//  C++ Testing Bay
//
//  Created by Nathan on 3/15/16.
//  Copyright © 2016 Nathan. All rights reserved.
//

#ifndef User_h
#define User_h
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class User
{
    typedef string* stringptr;
    
private:
    string u_first, u_last;
    string* s_array_ptr;
    unsigned int ID, books_out, books_needed, arr_size;
    bool ResizeArray() ; // Need to fill and write code for function
    
public:
    
    // Constructor and class utility functions
    User(string first = "", string last = "", unsigned int ID_num = 0)
    { u_first = first; u_last = last; ID = ID_num; s_array_ptr = nullptr;
        books_out = 0; books_needed = 0; arr_size = 0; }
    int GetIDNumber() const {return ID;}
    string GetFirstName() const {return u_first;}
    string GetLastName() const {return u_last;}
    string GetFullName() const;
    void SetIDNumber(unsigned int ID_num);   // Verify between correct range
    void SetFirstName(string first) {u_first = first;}
    void SetLastName(string last) {u_last = last;}
    int CheckoutCount() const {return books_out;}
    bool CheckOut(const string& BookIDCode);
    bool CheckIn(const string& BookIDCode);
    bool HasCheckedOut(const string& BookIDCode) const;
    void Clear(); // Clears all data for object
    
    // Overloaded operators and friend functions
    friend const ostream& operator<<(ostream& output, const User& Patron);
    friend const istream& operator>>(istream& input, User& Patron);
    const User operator+(string rhs);
    void operator+=(string rhs);
    bool operator==(const User& rhs);
    bool operator!=(const User& rhs);
    
    
    // Overloaded assignment operator and destructor
    User(const User& rhs);
    const User& operator=(const User& rhs);
    ~User();
    
};

class User_exception
{
private:
    string message;
    
public:
    User_exception(const string& msg = "exception in user class") {message = msg;}
    string what() const {return message;}
};

#endif /* User_h */