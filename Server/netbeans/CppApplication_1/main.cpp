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
#include <string>

#include "Functions.h"
#include "UserList.h"
#include "Manager.h"


#include <cstdio>
#include <cstdlib>

//char buffer[250] = "Natalia Kaczor \n";
//char readbuffer[250];


using namespace std;

struct cln {
    int cfd;
    struct sockaddr_in caddr;
};

void* cthread(void *arg) {
    struct cln *client = (struct cln*) arg;
    char sentence [250];
    
    //memset(sentence, 0, sizeof(sentence));
    
    printf("Polaczono z serwerem\n");
    int id = 0;
    while (id != 4) {//connection
        memset(sentence, 0, sizeof(sentence));
        read(client->cfd, sentence, sizeof (sentence));
        //char sentence [250] = "4 Kaczor";
        char user [250];
        
        cout<<"sentence: "<<sentence<<endl;
        
        sscanf(sentence, "%d %s", &id, user);
        string userName = string(user);
        cout<<"Login: "<<userName<<endl;

        cout << "instrukcja: " << id << endl;

        switch (id) {
            case 1:
            {//GetAllMessages
                string allMessages = getAllMessages(sentence);
                //cout<<allMessages<<endl;
                //string allMessages = "Kaczor; to ja !\nTomys;tomysem jestem";
                //cout<<allMessages<<endl;
                cout<<allMessages<<endl;
                cout<<"przed wyslaniem all msg"<<endl;
                write(client->cfd,  allMessages.c_str(), allMessages.length());
                cout<<"o wyslaniu all msg"<<endl;
                 //Manager* manager = &Manager::getManager();
                 //manager->fillPublicMessages(new Message("Kaczor", "To ja kaczor"));
                
                 break;
            }
            case 2:
            {//GetMessagesFrom
                string messages = getMessagesFrom(sentence);
                cout<<"GET Wiadomosc prywatna dla "<<userName<<" "<<messages<<endl;
                write(client->cfd,  messages.c_str(), messages.length());
                break;
            }
            case 3:
            {//Join
                string flag = join(sentence);
                //cout<<"dodano usera"<<endl;
                write(client->cfd,  flag.c_str(), flag.length());
                break;
            }
            case 4:
            {//Leave
                leave(sentence);
                break;
            }
            case 5:
            {//Send message to all
                cout<<"Od klienta: "<<sentence<<endl;
                sendMessageToAll(sentence);
                break;
            }
            case 6:
            {//Send message to
                cout<<"SEND prywatna FROM"<<userName<<endl;
                string status;
                status = sendMessageTo(sentence);
                write(client->cfd, status.c_str(), status.length());
                break;
            }
            case 7:
            {//GetClients
                string clients;
                clients = getClients(sentence);
                write(client->cfd, clients.c_str(), clients.length());
                break;
            }


            default:
                cout << "nieznana komenda" << endl;
        }
    }



    close(client->cfd);
    free(client);
    return 0;

}

int main(int argc, char *argv[]) {

//
    Manager* manager = &Manager::getManager();

    manager->addUser("Admin");
  
    int on = 1;
    struct sockaddr_in saddr;

    saddr = fillSocketAddress(1234);

    test();

    int sfd = socket(PF_INET, SOCK_STREAM, 0);
    setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, (char*) &on, sizeof (on));

    bind(sfd, (struct sockaddr*) &saddr, sizeof (saddr));
    listen(sfd, 10);


    while (1) {

        struct cln* client = (struct cln*) malloc(sizeof (struct cln));

        socklen_t slt;
        slt = sizeof (client->caddr);
        client->cfd = accept(sfd, (struct sockaddr*) &client->caddr, &slt);

        pthread_t tid;
        pthread_create(&tid, NULL, cthread, client);
        pthread_detach(tid);
    }

    close(sfd);

    return 0;
}