/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   User.h
 * Author: kamil
 *
 * Created on January 9, 2016, 2:39 PM
 */

#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
public:
    User(string name);
    
    void setName(string name);
    string getName();
    
    User(const User& orig);
    virtual ~User();
private:
    string _name; 

};


#endif /* USER_H */

