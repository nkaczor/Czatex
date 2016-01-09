#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <pthread.h>

struct cln {
	int cfd;
	struct sockaddr_in caddr;
};

//char readbuffer[250];

void* cthread(void* arg) {
  struct cln* c = (struct cln*) arg;
  
  printf("New connection: %s\n", inet_ntoa((struct in_addr)c->caddr.sin_addr));
  
  //read(c->cfd, readbuffer,sizeof(readbuffer));
  //printf("%s\n",readbuffer);
  
  
  write(c->cfd, "Hello world!\n", 13);
  
  
  close(c->cfd);
  free(c);
  return 0;
}

int main(int argc, char** argv) {
  pthread_t tid;
  socklen_t slt;
  int sfd, on=1;
  
  struct sockaddr_in saddr;
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(1234);
  saddr.sin_addr.s_addr = INADDR_ANY;

  sfd = socket(AF_INET, SOCK_STREAM, 0);

  setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
  bind(sfd, (struct sockaddr*) &saddr, sizeof(saddr));
  
  listen(sfd, 5);
  
  while(1) {
    struct cln* c = malloc(sizeof(struct cln));
    slt = sizeof(c->caddr);
    c->cfd = accept(sfd, (struct sockaddr*)&c->caddr, &slt);
    pthread_create(&tid, NULL, cthread, c);
    pthread_detach(tid);
  }
  close(sfd);

  return 0;
}


