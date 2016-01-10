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
        public int Join(string login) {
           
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
            Console.WriteLine(response);
            //string[] users = reponse.trim(" ");
            List<Client> clients = new List<Client>();
           
            return clients;
        }

        public List<Message> GetAllMessages(string myLogin) {
            List<Message> messages = new List<Message>();
            return messages;
        }

        private ConnectionHandler cHandler;
        public ChatManager() {
           cHandler = new ConnectionHandler();

            /* get DNS host information */
            cHandler.Connect();
           
        }
    }
}
