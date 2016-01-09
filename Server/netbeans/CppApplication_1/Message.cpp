/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Message.cpp
 * Author: kamil
 * 
 * Created on January 9, 2016, 3:58 PM
 */

#include "Message.h"

Message::Message(string text) {
_text = text;
}

string Message::getMessage()
{
    return _text;
}

Message::Message(const Message& orig) {
}

Message::~Message() {
}

