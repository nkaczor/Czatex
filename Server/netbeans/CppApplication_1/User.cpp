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

//using namespace std;

User::User(string name) {
    _name = name;
    _publicMessagesList = new vector <Message*>();
    _publicMessagesList->push_back(new Message("Admin","Witamy na platformie Czatex! Udanej konwersacji"));
}


string User::getMessageFrom(string who)
{
    //string msg = "1\n";
    string msg;
    map<string, vector<Message*> >::iterator it = _messageBox.find(who);
    
    if (it != _messageBox.end())
    {
        msg = "1\n";
        for (vector<Message*>::iterator iterator = it->second.begin(); iterator != it->second.end(); iterator++) {
                Message *message = *iterator;
                //cout << message->getMessage() << endl;
                msg = msg +(*iterator)->getMessage()+";"; 
        }
        removePrivateMessages(who);
        
        if(msg.length()<3)
            msg="0\n";
    }else
    {//Nie ma takiego usera
        msg = "2\n";
    }
    
    
    
    
    
    return msg;
}


void User::insertMessage(Message* msg)
{
    
    //cout<<"inserting"<<endl;
    
        map<string, vector<Message*> >::iterator it = _messageBox.find(msg->getAuthor());
        if (it == _messageBox.end())
        {
             //cout<<"dodaje klucz"<<endl;
            _messageBox[msg->getAuthor()]; //add key
        }

        _messageBox[msg->getAuthor()].push_back(msg);
        
}


 void User::removePrivateMessages(string from)
 {
      //map<string, vector<Message*> >::iterator it = _messageBox.find(from);
      _messageBox[from].clear();
 }


string User::getPublicMessages()
{
    string messages="1\n";
    
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
    
    if(messages.length()<3)
        messages="0\n";
    
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

