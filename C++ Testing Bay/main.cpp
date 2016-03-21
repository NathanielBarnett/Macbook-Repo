//
//  main.cpp
//  C++ Testing Bay
//
//  Created by Nathan on 3/15/16.
//  Copyright © 2016 Nathan. All rights reserved.
//
#include "User.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;


// function declarations
int ResizeArray(User* &OldArray, int OldSize);

int main()
{
    // Set up files
    ifstream user_info_fh, checkouts_fh, checkins_fh;
    ofstream users2_fh;
    user_info_fh.open("users.txt");
    checkouts_fh.open("checkouts.txt");
    checkins_fh.open("checkins.txt");
    users2_fh.open("users2.txt");
    
    // Did files open succesfully?
    if (!user_info_fh.is_open())
    {
        cerr << "users.txt was unable to open" << endl;
        //exit(1);
    }
    if (!checkouts_fh.is_open())
    {
        cerr << "checkouts.txt was unable to open" << endl;
        //exit(1);
    }
    if (!checkins_fh.is_open())
    {
        cerr << "checkins.txt was unable to open" << endl;
        //exit(1);
    }
    if (!users2_fh.is_open())
    {
        cerr << "Unable to create new text document for output." << endl;
        exit(1);
    }
    
    // variables for file handling
    int num_users = 0, user_array_size = 5; // start the array at 5
    typedef User* UserPtr;
    UserPtr user_array = new User[user_array_size];
    
    // Read through users.txt and grab current list of users and their data
    while (!user_info_fh.eof())
    {
        User transit;
        user_info_fh >> transit;    //read in a user, check if array need be resized
        
        try {
            
            if ((num_users + 1) > user_array_size)
            {
                user_array_size = ResizeArray(user_array, user_array_size);
            }
            
        } catch (User_exception u_error) {
            cerr << u_error.what() << endl;
        }
        
        user_array[num_users] = transit;
        num_users++;
        
    }
    
    //Read through checkouts.txt and analyze the data appropriately
    int transit_ID;
    string transit_book;
    bool user_was_not_found = true;
    while (!checkouts_fh.eof())
    {
        
        checkouts_fh >> transit_ID >> transit_book;
        for (int i = 0; i < (num_users - 1); i++)   // walk through user array
        {
            if (user_array[i].GetIDNumber() == transit_ID)  // if found the right user
            {
                if (user_array[i].HasCheckedOut(transit_book)) // if they have the book checked out
                {
                    cerr << "User " << transit_ID << " has already checked out item "
                    << transit_book << endl;
                    user_was_not_found = false;
                    
                    
                }
                else if (!user_array[i].HasCheckedOut(transit_book))
                {
                    user_array[i].CheckOut(transit_book);
                    user_was_not_found = false;
                    
                }
            }
        }
        
        if (user_was_not_found)
        {
            cerr << "No user can be found with this ID number: " << transit_ID << endl;
        }
    }
    
    
    
    // Read through checkins.txt and analyze the data appropriately
    // *NOTE* Reuse variables 'transit_book'
    int users_with_item;
    bool user_was_found = false;
    while (!checkins_fh.eof())
    {
        users_with_item = 0;
        checkins_fh >> transit_book;
        for (int i = 0; i < (num_users - 1); i++)
        {
            if (user_array[i].HasCheckedOut(transit_book))
            {
                user_array[i].CheckIn(transit_book);
                user_was_found = true;
                if (users_with_item == 1)
                {
                    cerr << endl << "This item " << transit_book
                    << " is checked out by more than one user: "
                    << user_array[i].GetIDNumber() << endl;
                }
                else if (users_with_item > 1)
                {
                    cerr << user_array[i].GetIDNumber() << endl;
                }
                users_with_item++;
            }
            
            
        }
        if (!user_was_found)
        {
            cerr << "No User was found with this item checked out: "
            << transit_book << endl;
        }
    }
    
    for (int i = 0; i < (num_users - 1); i++)
    {
        users2_fh << user_array[i];
    }
    
    
//    
//       for (int i = 0; i < (num_users - 1); i++)    // the last index is 1 before the number of users
//        {
//            cout << user_array[i];
//        }
//    
    
    
    user_info_fh.close();
    checkouts_fh.close();
    checkins_fh.close();
    users2_fh.close();
    return 0;
}



// Resize function for User array
int ResizeArray(User* &OldArray, int OldSize)
{
    int TempSize = OldSize * 2;
    if (User* Newptr = new User[TempSize])
    {
        for (int i = 0; i < OldSize; i++)
        {
            Newptr[i] = OldArray[i];
        }
        delete [] OldArray;
        OldArray = Newptr;
        return TempSize;
    }
    else
    {
        throw (User_exception("User array cannot be resized"));
    }
}

