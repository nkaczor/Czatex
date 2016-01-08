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

char buffer[250] = "Natalia Kaczor \n";
char readbuffer[250];

using namespace std;

struct cln{
  int cfd;
  struct sockaddr_in caddr;
};

void* cthread(void *arg){
  struct cln *client = (struct cln*) arg;

    printf("Polaczono z serwerem\n");
    
    read(client->cfd, readbuffer,sizeof(readbuffer));
      
  if (strncmp(readbuffer, "117189",6)==0) write(client->cfd,buffer,18);
  else write(client->cfd,"Unknown",10);
  
  write(client->cfd,"Koniec wiadomosci!\n",20);
  //write(client->cfd,"asd\n",4);
  
  close(client->cfd);
  free(client);
  return 0;
  
}

int main(int argc, char *argv[]){

  int on =1;
  pthread_t tid;
  //socklen_t slt;
  struct sockaddr_in saddr;
  
  saddr.sin_family=PF_INET;
  saddr.sin_port=htons(1234);
  saddr.sin_addr.s_addr=INADDR_ANY;
  
  int sfd=socket(PF_INET,SOCK_STREAM,0);
  setsockopt(sfd, SOL_SOCKET,SO_REUSEADDR, (char*)&on, sizeof(on));



  bind(sfd, (struct sockaddr*)&saddr, sizeof(saddr));
  listen(sfd, 10);
  
  
  while(1){

    struct cln* client = (struct cln*)malloc(sizeof(struct cln));
    
    socklen_t slt;
    slt=sizeof(client->caddr);
    client->cfd = accept(sfd, (struct sockaddr*)&client->caddr, &slt);
    
    pthread_create(&tid, NULL, cthread, client);
    pthread_detach(tid);
  }

  close(sfd);

  return 0;
}