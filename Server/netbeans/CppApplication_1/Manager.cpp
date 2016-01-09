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

void Manager::fillPublicMessages(string who, Message *msg)
{
    for (vector<User*>::iterator iterator = _userList->getUsersList()->begin(); iterator != _userList->getUsersList()->end(); iterator++)
    {  
        User *user = *iterator;
        
        if (user->getName() == who)
            continue;
        
        user->insertPublicMessage(msg);
        
    }
}





Manager::~Manager() {
}

Manager& Manager::getManager()
{
	static Manager *manager = NULL;

	if (manager == NULL){
		manager = new Manager();
	}

	return *manager;
}

void Manager::destroyManager()
{
	Manager *manager = &getManager();
	delete manager;
}