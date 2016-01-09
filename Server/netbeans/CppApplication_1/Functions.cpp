/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Functions.cpp
 * Author: kamil
 * 
 * Created on January 9, 2016, 2:24 PM
 */

#include "Functions.h"

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

#include "Manager.h"

string getAllMessages(char* sentence) {
    int id;
    char name [250];

    Manager* manager = &Manager::getManager();
    sscanf(sentence, "%d %s", &id, name);

    return manager->receivePublicMessages(string(name));
}

string getMessagesFrom(char* sentence) {
    char name [250];
    char from [250];
    int id;

    sscanf(sentence, "%d %s %s", &id, name, from);

    Manager* manager = &Manager::getManager();

    //cout<<string(name)<<endl<<string(from)<<endl;

    return "not yet - getMessagesFrom";
}

int join(char* sentence) {
    char name [250];
    int id;

    sscanf(sentence, "%d %s", &id, name);

    Manager* manager = &Manager::getManager();
    if (manager->addUser(name))
        return 1;
    else 
        return 2;
}

void leave(char* sentence)
{
    char name [250];
    int id;

    sscanf(sentence, "%d %s", &id, name);
    
    //cout<<name<<endl;
    cout<<"not yet - leave";
}

void sendMessageToAll(char* sentence)
{
    char name [250];
    char msg [250];
    int id;

    sscanf(sentence, "%d %s %[^\t]", &id, name, msg);

    Manager* manager = &Manager::getManager();

    manager->fillPublicMessages(new Message(string(name),string(msg)));
    //cout<<"from: "<<string(name)<<endl;
    //cout<<"msg: "<<string(msg)<<endl;
    
    //cout<<string(name)<<endl<<string(from)<<endl;

    //return "not yet - getMessagesFrom";
}

struct sockaddr_in fillSocketAddress(int port) {
    struct sockaddr_in socketAddress;

    socketAddress.sin_family = PF_INET;
    socketAddress.sin_port = htons(port);
    socketAddress.sin_addr.s_addr = INADDR_ANY;

    return socketAddress;
}

void test() {
    std::cout << "test" << std::endl;
}
