/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UserList.h
 * Author: kamil
 *
 * Created on January 9, 2016, 2:45 PM
 */

#ifndef USERLIST_H
#define USERLIST_H

#include <vector>
#include "User.h"

using namespace std;

class UserList {
public:
    
    void insertUser(User user);
    string getUsers();
    
    static UserList& getUserList();
    static void destroyUserList();

private:
    
    vector <User> *_userList;
    
    UserList();
    UserList(const UserList& orig);
    virtual ~UserList();
};

#endif /* USERLIST_H */

