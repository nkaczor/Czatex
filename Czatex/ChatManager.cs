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
            return Int32.Parse(cHandler.Receive());
        }
        public void Leave(string login)
        {
            cHandler.SendData("4 " + login);
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
