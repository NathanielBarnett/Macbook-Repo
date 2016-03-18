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
    user_info_fh.open("users.txt");
    checkouts_fh.open("checkouts.txt");
    checkins_fh.open("checkins.txt");
    
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
}


