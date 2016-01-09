/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Message.h
 * Author: kamil
 *
 * Created on January 9, 2016, 3:58 PM
 */

#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
using namespace std;

class Message {
public:
    Message(string author, string text);
    Message(const Message& orig);
    virtual ~Message();
    
    string getMessage();
    string getAuthor();
    
private:
    string _author;
    string _text;

};

#endif /* MESSAGE_H */

