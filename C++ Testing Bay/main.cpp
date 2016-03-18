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
using namespace std;

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
    int num_users = 0;
    typedef User* UserPtr;
    UserPtr user_array = new User[num_users];
    while (!user_info_fh.eof())
           {
               User transit;
               
           }
    
    user_info_fh.close();
    checkouts_fh.close();
    checkins_fh.close();
    users2_fh.close();
}



int ResizeArray(User* &OldArray, int OldSize)
{
    int TempSize = OldSize * 2;
    if (User* TempPtr = new User[TempSize])
    {
        for (int i = 0; i < OldArray->CheckoutCount(); i++)
        {
            TempPtr[i] = OldArray[i];
        }
        delete [] OldArray;
        OldArray = TempPtr;
        return TempSize;
    }
}







