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


//char buffer[250] = "Natalia Kaczor \n";
//char readbuffer[250];
char sentence [250];

using namespace std;

struct cln {
    int cfd;
    struct sockaddr_in caddr;
};

void* cthread(void *arg) {
    struct cln *client = (struct cln*) arg;


    printf("Polaczono z serwerem\n");
    int id = 0;
    while (id != 4) {//connection

        read(client->cfd, sentence, sizeof (sentence));
        //char sentence [250] = "4 Kaczor";
        char user [250];
        

        sscanf(sentence, "%d %s", &id, user);
        string userName = string(user);
        //cout<<userName<<endl;

        cout << "instrukcja: " << id << endl;

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
                cout << "dodano" << endl;
                write(client->cfd, "1\n", 2);
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
            case 6:
            {//Send message to
                sendMessageTo(sentence);
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


    //    printf("Polaczono z serwerem\n");
    //    read(client->cfd, readbuffer, sizeof (readbuffer));
    //    printf("char %s\n", readbuffer);
    //    string msg = string(readbuffer);
    //    cout << msg << "rututu" << endl;
    //    write(client->cfd, "1\n", 2);


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
    //
    //    map<string, vector<Message*> > _messageBox;
    //    //_messageBox = new map<string, vector<Message*> >;
    //
    //    //map<string, string>::iterator it = _audioFiles->find(audioName);
    //    //char* patch = new char[it->second.length() + 1];
    //    //strcpy_s(patch, it->second.length() + 1, it->second.c_str());
    //
    //    map<string, vector<Message*> >::iterator it2 = _messageBox.find("Kaczor");
    //    if (it2 == _messageBox.end())
    //        cout<<"Nie ma kaczora";
    //    
    //    _messageBox["Kaczor"];
    //    // _messageBox["Kaczor"];
    //    _messageBox["Kaczor"].push_back(new Message("Kaczor", "Wiadomosc w mapie1"));
    //    _messageBox["Kaczor"].push_back(new Message("Kaczor", "Wiadomosc w mapie2"));
    //    _messageBox["Kaczor"].push_back(new Message("Kaczor", "Wiadomosc w mapie3"));
    //
    //    map<string, vector<Message*> >::iterator it = _messageBox.find("Kaczor");
    //    if (it != _messageBox.end()) {
    //        //cout<< it->second.at(0)->getMessage();
    //
    //        for (vector<Message*>::iterator iterator = it->second.begin(); iterator != it->second.end(); iterator++) {
    //            Message *message = *iterator;
    //            cout << message->getMessage() << endl;
    //        }
    //
    //    } else {
    //        cout << "element nie istnieje" << endl;
    //    }
    //    //_messageBox->insert(pair<string, vector<Message*> >("Kaczor",));
    //    //_messageBox["kaczor"];
    //
    //    //_audioFiles->insert(pair<string, string>("exterminate", "Audio/exterminate.mp3"));
    //
    //    //    families["Jones"];
    //    //    families["Smith"];
    //    //    families["Doe"];
    //    //
    //    //    // add children
    //    //    families["Jones"].push_back("Jane");
    //    //    families["Jones"].push_back("Jim");


    //testyyy

    Manager* manager = &Manager::getManager();

    manager->addUser("Kamil");
    manager->addUser("Tomys");
    manager->addUser("Kaczor");


    //string list = manager->receiveClientList();
    //cout<<list<<endl;

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
    manager->fillPublicMessages(new Message("Kaczor", "To ja kaczor"));
    manager->fillPublicMessages(new Message("Kaczor", "To znowu ja kaczor"));
    manager->fillPublicMessages(new Message("Kamil", "Tu owca"));
    //    
    //    string mymsg = manager->receivePublicMessages("Kaczor");
    //    cout << mymsg << endl


    //cout<<manager->receivePublicMessages("Tomys")<<endl;
    //cout<<manager->receiveClientList()<<endl;
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



    //    char sentence [250] = "4 Kaczor";
    //    char user [250];
    //    int id;
    //
    //    sscanf(sentence, "%d %s", &id, user);
    //    string userName = string(user);
    //    //cout<<userName<<endl;
    //
    //    switch (id) {
    //        case 1:
    //        {//GetAllMessages
    //            string allMessages = getAllMessages(sentence);
    //            break;
    //        }
    //        case 2:
    //        {//GetMessagesFrom
    //            string messages = getMessagesFrom(sentence);
    //            break;
    //        }
    //        case 3:
    //        {//Join
    //            int flag = join(sentence);
    //            break;
    //        }
    //        case 4:
    //        {//Leave
    //            leave(sentence);
    //            break;
    //        }
    //        case 5:
    //        {//Send message to all
    //            sendMessageToAll(sentence);
    //            break;
    //        }
    //        case 6:
    //        {//Send message to
    //            sendMessageTo(sentence);
    //            break;
    //        }
    //        case 7:
    //        {//GetClients
    //            string clients;
    //            clients = getClients(sentence);
    //            break;
    //        }
    //
    //
    //        default:
    //            cout << "nieznana komenda" << endl;
    //    }

    //string mymsg = manager->receivePublicMessages("Tomys");
    //cout << mymsg << endl;

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