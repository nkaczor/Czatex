using Czatex.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Czatex
{
    public class ChatManager
    {
        private ConnectionHandler cHandler;
        public int Join(string login) {
            Console.WriteLine(login);
            cHandler.SendData("3 "+ login);
            int status = Int32.Parse(cHandler.Receive());
           
            return status;
           
        }
        public void Leave(string login)
        {
            cHandler.SendData("4 " + login);
        }
        public List<Client> GetAllClients(string myLogin)
        {
            cHandler.SendData("7 " + myLogin);
            string response = cHandler.Receive();
            string[] users = response.Split(' ');
            
            List<Client> clients = new List<Client>();
            foreach (var user in users)
            {
                if(user.Length>0)
                    clients.Add(new Client(user));
            }
            return clients;
        }

        public List<Message> GetAllMessages(string myLogin) {
            List<Message> messages = new List<Message>();
            cHandler.SendData("1 " + myLogin);
            string response = cHandler.Receive();
            string[] messagesResponse = response.Split('\n');
            if (messagesResponse[0] == "1")
            {

                foreach (var message in messagesResponse.Skip(1))
                {
                    string[] args = message.Split(';');
                    messages.Add(new Message(args[1], args[0]));
                }
               
            }
            return messages;
        }
        public void SendMessageToAll(string myLogin, string message)
        {
            cHandler.SendData("5 " + myLogin + " " + message);
        }


        public List<Message> GetMessagesFrom(string myLogin, string from)
        {
            List<Message> messages = new List<Message>();
            cHandler.SendData("2 " + myLogin + " " + from);
            string response = cHandler.Receive();
            string[] messagesResponse = response.Split('\n');
            if (messagesResponse[0] == "1")
            {
                messagesResponse = messagesResponse[1].Split(';');
                foreach (var message in messagesResponse)
                {
                    if(message.Length>0)
                        messages.Add(new Message(message, from));
                }


            }
            return messages;
        }
        public void SendMessageTo(string myLogin, string to, string message)
        {
            cHandler.SendData("6 " + myLogin + " " + to + " " + message);
            string response = cHandler.Receive();
        }
        public void Connect(string ip) {
            cHandler.Connect(ip);
        }

        public ChatManager() {
           cHandler = new ConnectionHandler();
                    
        }
    }
}
