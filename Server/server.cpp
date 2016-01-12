#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

#include <pthread.h>
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <string.h>

#include "functions.h"

char buffer[250] = "Natalia Kaczor \n";
char readbuffer[250];
char readbuffer2[250];
char readbuffer3[250];


using namespace std;

struct cln{
  int cfd;
  struct sockaddr_in caddr;
};


struct sockaddr_in fillSocketAddress(int port)
{
  struct sockaddr_in socketAddress;
  
  socketAddress.sin_family = PF_INET;
  socketAddress.sin_port = htons(port);
  socketAddress.sin_addr.s_addr = INADDR_ANY;
  
  return socketAddress;
}


void* cthread(void *arg){
  struct cln *client = (struct cln*) arg;

  printf("Polaczono z serwerem\n");
    
  //read(client->cfd, readbuffer,sizeof(readbuffer));
   
  //printf("%s\n",readbuffer);

  read(client->cfd, readbuffer,sizeof(readbuffer)); 
  printf("%s\n",readbuffer);

  printf("%s\n","przdwrite");   
  write(client->cfd, "Hello world!\n", 13);
	
  printf("%s\n","przedread2");    
  read(client->cfd, readbuffer2,sizeof(readbuffer2)); 
  printf("%s\n",readbuffer2);	
  
  printf("%s\n","przdwrite2");   
  write(client->cfd, "Hello GHFSW!\n", 13);

  printf("%s\n","przedread3");    
  read(client->cfd, readbuffer3,sizeof(readbuffer3)); 
  printf("%s\n",readbuffer3);	

  //if (strncmp(readbuffer, "117189",6)==0) write(client->cfd,buffer,250);
  //else write(client->cfd,"Unknown",10);
  
  //write(client->cfd,"Koniec wiadomosci!\n",20);
  //write(client->cfd,"asd\n",4);
  
  //read(client->cfd, readbuffer, sizeof(readbuffer));
  //printf("%s",readbuffer);
  
  
  close(client->cfd);
  free(client);
  return 0;
  
}

int main(int argc, char *argv[]){

  int on =1;
  struct sockaddr_in saddr;
  
  saddr = fillSocketAddress(1234);
  
  //test();
  
  int sfd=socket(PF_INET,SOCK_STREAM,0);
  setsockopt(sfd, SOL_SOCKET,SO_REUSEADDR, (char*)&on, sizeof(on));

  bind(sfd, (struct sockaddr*)&saddr, sizeof(saddr));
  listen(sfd, 10);
  
  
  while(1){

    struct cln* client = (struct cln*)malloc(sizeof(struct cln));
    
    socklen_t slt;
    slt=sizeof(client->caddr);
    client->cfd = accept(sfd, (struct sockaddr*)&client->caddr,&slt);
        
    pthread_t tid;        
    pthread_create(&tid, NULL, cthread, client);
    pthread_detach(tid);
  }

  close(sfd);

  return 0;
}
