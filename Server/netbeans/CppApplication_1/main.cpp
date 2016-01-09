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

#include "Functions.h"
#include "UserList.h"
#include "Manager.h"


char buffer[250] = "Natalia Kaczor \n";
char readbuffer[250];


using namespace std;

struct cln {
    int cfd;
    struct sockaddr_in caddr;
};

void* cthread(void *arg) {
    struct cln *client = (struct cln*) arg;

    printf("Polaczono z serwerem\n");


    read(client->cfd, readbuffer, sizeof (readbuffer));

    printf("char %s\n", readbuffer);
    string msg = string(readbuffer);

    cout << msg << "rututu" << endl;
    //Manager* manager =&Manager::getManager();

    //printf("%s\n",buf);

    //manager->addUser("Kamil");

    write(client->cfd, "1\n", 2);


    //read(client->cfd, readbuffer,sizeof(readbuffer));

    //printf("%s\n",readbuffer);
    //write(client->cfd, "Helyo world!\n", 13);

    //if (strncmp(readbuffer, "117189",6)==0) write(client->cfd,buffer,250);
    //else write(client->cfd,"Unknown",10);

    //write(client->cfd,"Koniec wiadomosci!\n",20);
    //write(client->cfd,"asd\n",4);

    //read(client->cfd, readbuffer, sizeof(readbuffer));
    //printf("%s\n",readbuffer);


    close(client->cfd);
    free(client);
    return 0;

}

int main(int argc, char *argv[]) {

    //    UserList* userList = &UserList::getUserList();
    //      
    //    User *kamil = new User("Kamil");
    //    User *tomys = new User("Tomys");
    //    User *kaczor = new User("Kaczor");
    //    
    //    userList->insertUser(kamil);
    //    userList->insertUser(tomys);
    //    userList->insertUser(kaczor);

    //string listOfUsers = userList->getUsers();
    //cout<<listOfUsers<<endl;


    Manager* manager = &Manager::getManager();

    manager->addUser("Kamil");
    manager->addUser("Tomys");
    manager->addUser("Kaczor");

    //    if(manager->addUser("Kamil"))
    //    {
    //        cout<<"dodano nowego usera\n";
    //    }else
    //    {
    //        cout<<"Taki user juz istnieje\n";
    //    }
    //    
    //    cout<<manager->getNumberOfUsers()<<endl;

        Message* msg = new Message("Tomys", "To ja tomys!");
        manager->fillPublicMessages(msg);
        manager->fillPublicMessages(new Message("Kaczor","To ja kaczor"));
        manager->fillPublicMessages(new Message("Kaczor","To znowu ja kaczor"));
        manager->fillPublicMessages(new Message("Kamil","Tu owca"));
    //    
    //    string mymsg = manager->receivePublicMessages("Kaczor");
    //    cout << mymsg << endl


        
        //testy
//    char sentence [250] = "2 Kamil Kaczor";
//    char name [250];
//    char from [250];
//    int id;
//        
//    sscanf(sentence, "%d %s %s", &id, name, from);  
//        
//    cout<<name<<endl<<from<<endl;
        
        //testy


    char sentence [250] = "5 Kaczor\n Owca jest genialny";
    char text [250];
    int id;

    sscanf(sentence, "%d %[^\n\t]", &id, text);
    //printf("%s->%d\n", text, id);
    
    //string nick;
    switch (id) {
        case 1:
        {//GetAllMessages
            string allMessages = getAllMessages(sentence);
            break;
        }
        case 2:
        {//GetMessagesFrom
            string messages = getMessagesFrom(sentence);
            break;
        }
        case 3:
        {//Join
            int flag = join(sentence);
            break;
        }
        case 4:
        {//Leave
            leave(sentence);
            break;
        }
        case 5:
        {//Send message to all
            sendMessageToAll(sentence);
            break;
        }
            

        default:
            cout << "nieznana komenda" << endl;
    }
    
    string mymsg = manager->receivePublicMessages("Tomys");
    cout << mymsg << endl;


    //        int on = 1;
    //        struct sockaddr_in saddr;
    //    
    //        saddr = fillSocketAddress(1234);
    //    
    //        test();
    //    
    //        int sfd = socket(PF_INET, SOCK_STREAM, 0);
    //        setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, (char*) &on, sizeof (on));
    //    
    //        bind(sfd, (struct sockaddr*) &saddr, sizeof (saddr));
    //        listen(sfd, 10);
    //    
    //    
    //        while (1) {
    //    
    //            struct cln* client = (struct cln*) malloc(sizeof (struct cln));
    //    
    //            socklen_t slt;
    //            slt = sizeof (client->caddr);
    //            client->cfd = accept(sfd, (struct sockaddr*) &client->caddr, &slt);
    //    
    //            pthread_t tid;
    //            pthread_create(&tid, NULL, cthread, client);
    //            pthread_detach(tid);
    //        }
    //    
    //        close(sfd);

    return 0;
}