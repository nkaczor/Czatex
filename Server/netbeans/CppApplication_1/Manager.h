/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Manager.h
 * Author: kamil
 *
 * Created on January 9, 2016, 4:36 PM
 */

#ifndef MANAGER_H
#define MANAGER_H

#include "UserList.h"


class Manager {
public:

    void fillPublicMessages(string who, Message *msg);
    string receivePublicMessages(string who);
    void addUser(string name);
    
    
    static Manager& getManager();
    static void destroyManager();
private:
    
    UserList *_userList;
    
    Manager();
    Manager(const Manager& orig);
    virtual ~Manager();
};

#endif /* MANAGER_H */

