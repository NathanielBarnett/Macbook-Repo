//
//  User.cpp
//  C++ Testing Bay
//
//  Created by Nathan on 3/16/16.
//  Copyright © 2016 Nathan. All rights reserved.
//

#include "User.h"
#include <iostream>
using namespace std;

// Class function definitions

string User::GetFullName() const
{
    string f_name = u_last + ", " + u_first;
    return f_name;
}

void User::SetIDNumber(unsigned int ID_num)
{
    if (100 <= ID_num && ID_num < 1000000)
    {
        ID = ID_num;
    }
}

bool User::CheckOut(const string& BookIDCode)
{
    bool checked_out = false;
    
    if (arr_size <= 0)  // if array is not yet allocated
    {
        arr_size = 5;
        s_array_ptr = new string[arr_size];
        s_array_ptr[books_out] = BookIDCode;
        books_out++;
    }
    
    try
    {
        if ((books_out + 1) > arr_size) // if number of items in array are size of array
        {
            ResizeArray();
        }

    }
    catch (User_exception err)
    {
        cerr << err.what() << endl;
        return checked_out;
    }
  
    for (int i = 0; i < books_out; i++)  // is ID in array?
    {
        if (s_array_ptr[i] == BookIDCode)
        {
            return checked_out;
        }
    }
    
    s_array_ptr[books_out] = BookIDCode;
    books_out++;
    checked_out = true;
    return checked_out;
    
}

bool User::CheckIn(const string& BookIDCode)
{
    for (int i = 0; i < books_out; i++)
    {
        if (s_array_ptr[i] == BookIDCode)
        {
            s_array_ptr[i] = "";
            books_out--;
            return true;
        }
    }
    
    if (books_out == 0)
    {
        User::~User();
        return true;
    }
    else
    {
        return false;
    }
}

bool User::HasCheckedOut(const string& BookIDCode) const
{
    for (int i = 0; i < books_out; i++)
    {
        if (s_array_ptr[i] == BookIDCode)
        {
            return true;
        }
    }
    
    return false;
}

void User::Clear()
{
    u_first = ""; u_last = "";
    ID = 0; books_out = 0;
    arr_size = 0;
    User::~User();
}

// Overload operators and friend functions

const ostream& operator<<(ostream& output, const User& Patron)
{
    output << Patron.ID << " " << Patron.u_first << " " << Patron.u_last << endl;
    output << Patron.books_out << endl;
    if (Patron.books_out > 0)
    {
        for (int i = 0; i < Patron.books_out; i++)
        {
            output << Patron.s_array_ptr[i] << " ";
        }
        output << endl;
    }
    return output;
}

const istream& operator>>(istream& input, User& Patron)
{
    
    Patron.Clear();
    input >> Patron.ID >> Patron.u_first >> Patron.u_last >> Patron.books_out;
    if (Patron.books_out > 0)
    {
        string Book;
        for (int i = 0; i < Patron.books_out; i++)
        {
            input >> Book;
            Patron.CheckIn(Book);
        }
    }
    return input;
}

const User User::operator+(string rhs)
{
    User Fred;
    Fred = *this;
    Fred.CheckOut(rhs);
    return Fred;
}

void User::operator+=(string rhs)
{
    User::CheckOut(rhs);
}

bool User::operator==(const User& rhs)
{
    if (ID == rhs.ID)
    {
        return true;
    }
    else
    {
        return true;
    }
}

bool User::operator!=(const User& rhs)
{
    if (ID == rhs.ID)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Overloaded assignment operator, destructor, and copy constructor

User::~User()
{
    if (s_array_ptr != nullptr)
    {
        
    }
}


/*
 private:
 string u_first, u_last;
 stringptr s_array_ptr;
 unsigned int ID, books_out, arr_size;
 bool ResizeArray() ; // Need to fill and write code for function
// Constructor and class utility functions
User(string first = "", string last = "", unsigned int ID_num = 0)
{ u_first = first; u_last = last; ID = ID_num;}
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
bool HasCheckedOut(const string& BookIDCode);
void Clear(); // Clears all data for object

// Overloeaded operators and friend functions
friend const ostream& operator<<(ostream& output, const User& Patron);
friend const istream& operator>>(istream& input, const User& Patron);
const User operator+(unsigned int rhs);
void operator+=(unsigned int rhs);
bool operator==(const User& rhs);
bool operator!=(const User& rhs);


// Overloaded assignment operator and destructor

const User& operator=(const User& rhs);
~User();
*/
