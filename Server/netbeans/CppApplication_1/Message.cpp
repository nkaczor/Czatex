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

Message::Message(string author,string text) {
_text = text;
_author = author;
}

string Message::getMessage()
{
    return _text;
}

string Message::getAuthor()
{
    return _author;
}

Message::Message(const Message& orig) {
}

Message::~Message() {
}

