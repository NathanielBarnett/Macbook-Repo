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
    ifstream user_info_fh;
    user_info_fh.open("users.txt");
    ofstream 
    if (!user_info_fh.is_open())
    {
        cerr << "users.txt was unable to open" << endl;
        exit(1);
    }
    
    
}


