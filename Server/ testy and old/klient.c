#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){


char buffer[250]="117189";

int fd=socket(PF_INET,SOCK_STREAM,0);

struct hostent* hostname = gethostbyname(argv[1]); 
struct sockaddr_in sa;
sa.sin_family=PF_INET;
sa.sin_port=htons(atoi(argv[2]));
memcpy(&sa.sin_addr.s_addr,hostname->h_addr, hostname->h_length);

connect(fd, (struct sockaddr*)&sa, sizeof(sa));
write(fd, argv[3], sizeof(argv[3]));
int n=read(fd, buffer, sizeof(buffer));
buffer[n]='\0';
write(1,buffer,100);
close(fd);



return 0;
}
