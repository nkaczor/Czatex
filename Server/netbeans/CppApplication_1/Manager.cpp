/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Manager.cpp
 * Author: kamil
 * 
 * Created on January 9, 2016, 4:36 PM
 */

#include "Manager.h"
#include <cstddef>
#include <iostream>

Manager::Manager() {
    _userList = &UserList::getUserList();

    //    for (vector<User*>::iterator iterator = _usersList->getUsersList()->begin(); iterator != _usersList->getUsersList()->end(); iterator++)
    //    {  
    //        std::cout<<(*iterator)->getName();
    //    }
}

Manager::Manager(const Manager& orig) {
}

string Manager::receiveMessagesFrom(string who, string from) {
    
    string messages;
    
    for (vector<User*>::iterator iterator = _userList->getUsersList()->begin(); iterator != _userList->getUsersList()->end(); iterator++) {
        User* user = *iterator;
        if (user->getName() == who) {
            messages = user->getMessageFrom(from);
            break;
        }
    }
    
    return messages;
}

 void Manager::insertMessageFrom(Message* msg,string to)
 {
     for (vector<User*>::iterator iterator = _userList->getUsersList()->begin(); iterator != _userList->getUsersList()->end(); iterator++) {
        User* user = *iterator;
        if (user->getName() == to) {
            //cout<<"inserting"<<endl;
            user->insertMessage(msg);
            break;
        }
    }
 }
 



void Manager::leave(string name) {

    for (vector<User*>::iterator iterator = _userList->getUsersList()->begin(); iterator != _userList->getUsersList()->end(); /**/) {
        User* user = *iterator;
        if (user->getName() == name) {
            delete user;
            iterator = _userList->getUsersList()->erase(iterator);
        } else {
            ++iterator;
        }
    }

}

bool Manager::addUser(string name) {
    if (_userList->insertUser(new User(name))) {
        return true;
    } else {
        return false;
    }

}

int Manager::getNumberOfUsers() {
    return _userList->getNumberOfUsers();
}

string Manager::receivePublicMessages(string who) {
    string messages = "";
    for (vector<User*>::iterator iterator = _userList->getUsersList()->begin(); iterator != _userList->getUsersList()->end(); iterator++) {
        User* user = *iterator;
        if (user->getName() == who) {
            messages = user->getPublicMessages();
            break;
        }
    }

    return messages;
}

void Manager::fillPublicMessages(Message *msg) {
    for (vector<User*>::iterator iterator = _userList->getUsersList()->begin(); iterator != _userList->getUsersList()->end(); iterator++) {
        User *user = *iterator;

        if (user->getName() == msg->getAuthor())
            continue;


        user->insertPublicMessage(msg);

    }
}

string Manager::receiveClientList(string who) {
    return _userList->getUsers(who);
}

Manager::~Manager() {
}

Manager& Manager::getManager() {
    static Manager *manager = NULL;

    if (manager == NULL) {
        manager = new Manager();
    }

    return *manager;
}

void Manager::destroyManager() {
    Manager *manager = &getManager();
    delete manager;
}