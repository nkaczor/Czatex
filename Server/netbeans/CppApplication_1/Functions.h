/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Functions.h
 * Author: kamil
 *
 * Created on January 9, 2016, 2:24 PM
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <vector>
#include "Message.h"

void test();

struct sockaddr_in fillSocketAddress(int port);

string getAllMessages(char* sentence);
string getMessagesFrom(char* sentence);


#endif /* FUNCTIONS_H */

