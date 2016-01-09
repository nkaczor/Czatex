/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   User.cpp
 * Author: kamil
 * 
 * Created on January 9, 2016, 2:39 PM
 */

#include "User.h"

User::User(string name) {
    _name = name;
}

void User::setName(string name)
{
    _name = name;
}
    
string User::getName()
{
    return _name;
}


User::User(const User& orig) {
}

User::~User() {
}

