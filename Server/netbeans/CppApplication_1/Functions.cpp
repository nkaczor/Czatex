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



struct sockaddr_in fillSocketAddress(int port)
{
  struct sockaddr_in socketAddress;
  
  socketAddress.sin_family = PF_INET;
  socketAddress.sin_port = htons(port);
  socketAddress.sin_addr.s_addr = INADDR_ANY;
  
  return socketAddress;
}


void test()
{
    std::cout<<"test"<<std::endl;
}
