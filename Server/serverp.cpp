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
  struct cln *c = (struct cln*) arg;
  //read(c->cfd, readbuffer[0],sizeof(readbuffer));
    //read(c->cfd, readbuffer[0],12);
    read(c->cfd, readbuffer,sizeof(readbuffer));
      
  if (strncmp(readbuffer, "117189",6)==0) write(c->cfd,buffer,250);
  else write(c->cfd,"Unknown",10);
  close(c->cfd);
  free(c);
  return 0;
  
}

int main(int argc, char *argv[]){

  int on =1;
  pthread_t tid;
  socklen_t slt;
  struct sockaddr_in saddr, caddr;
  saddr.sin_family=PF_INET;
  saddr.sin_port=htons(1234);
  saddr.sin_addr.s_addr=INADDR_ANY;
  
  int sfd=socket(PF_INET,SOCK_STREAM,0);
  setsockopt(sfd, SOL_SOCKET,SO_REUSEADDR, (char*)&on, sizeof(on));



  bind(sfd, (struct sockaddr*)&saddr, sizeof(saddr));
  listen(sfd, 10);
  while(1){
    struct sockaddr_in client_sa;
    
    //struct cln *c = malloc(sizeof(struct cln));
    //struct cln *c = new cln(sizeof(struct cln));
    struct cln* c = (struct cln*)malloc(sizeof(struct cln));
    
    
    slt=sizeof(c->caddr);
    c->cfd = accept(sfd, (struct sockaddr*)&c->caddr, &slt);
    pthread_create(&tid, NULL, cthread, c);
    pthread_detach(tid);
  }

  close(sfd);

  return 0;
}