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

bool User::ResizeArray()
{
    int TempSize = arr_size;
    do{
        TempSize = TempSize * 2;
    }while(TempSize < books_needed);
    stringptr TempPtr = new string[TempSize];
    
    if (TempPtr != nullptr)
    {
        for (int i = 0; i < books_out; i++)
        {
            TempPtr[i] = s_array_ptr[i];
        }
        delete [] s_array_ptr;
        s_array_ptr = TempPtr;
        arr_size = TempSize;
        return true;
    }
    else{
        throw User_exception("Can't resize array");
    }
}


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
    
    if (s_array_ptr == nullptr || arr_size == 0)  // if array is not yet allocated
    {
        arr_size = 5;
        s_array_ptr = new string[arr_size];
        s_array_ptr[books_out] = BookIDCode;
        books_out++;
    }
    
    for (int i = 0; i < books_out; i++)  // is ID in array?
    {
        if (s_array_ptr[i] == BookIDCode)
        {
            return checked_out;
        }
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
        for (int i = 0; i < Patron.arr_size; i++)
        {
            output << Patron.s_array_ptr[i] << " ";
        }
        output << endl;
    }
    return output;
}

const istream& operator>>(istream& input, User& Patron)
{
    //Patron.Clear();
    input >> Patron.ID >> Patron.u_first >> Patron.u_last >> Patron.books_needed;
    if (Patron.books_needed > 0)
    {
        string Book;
        for (int i = 0; i < Patron.books_needed; i++)
        {
            input >> Book;
            Patron.CheckOut(Book);
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
        delete [] s_array_ptr;
        s_array_ptr = nullptr;
    }
}

User::User(const User& rhs)
{
    //s_array_ptr = nullptr;
    *this = rhs;
}

const User& User::operator=(const User& rhs)
{
    if (this != &rhs)
    {
        this->~User();  // Take care of dynamic data
        u_first = rhs.u_first;  // Copy over static data
        u_last = rhs.u_last;
        ID = rhs.ID;
        books_needed = rhs.books_needed;
        books_out = rhs.books_out;
        arr_size = rhs.arr_size;
        if (books_out > 0)  // If dynamic array need be filled, then fill
        {
            s_array_ptr = new string[arr_size];
            for (int i = 0; i < books_out; i++)
            {
                s_array_ptr[i] = rhs.s_array_ptr[i];
            }
        }
    }
    return *this;   // Return the updated User object
}


