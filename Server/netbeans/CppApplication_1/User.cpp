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
    _publicMessagesList = new vector <Message*>();
}

string User::getPublicMessages()
{
    string messages;
    
    for (vector<Message*>::iterator iterator = _publicMessagesList->begin(); iterator != _publicMessagesList->end(); iterator++)
    {  
        
        
        if (std::distance(iterator, _publicMessagesList->end())-1 == 0)
        {
           messages = messages +(*iterator)->getAuthor()+";"+(*iterator)->getMessage(); 
        }else
        {
            messages = messages +(*iterator)->getAuthor()+";" + (*iterator)->getMessage() + "\n";
        }  
    }
    
    removePublicMessages();
    return messages;
}

void User::insertPublicMessage(Message* msg)
{
    _publicMessagesList->push_back(msg);
}


void User::removePublicMessages()
{
    _publicMessagesList->clear();
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

