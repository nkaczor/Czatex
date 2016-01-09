using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Czatex.Model
{
    public class Message
    {
        public Message(string messageText, Client from, Client to)
        {
            _messageText = messageText;
            _from = from;
            _to = to;
        }
        public Message(string messageText, Client from)
        {
            _messageText = messageText;
            _from = from;
            _to = null;
        }
        private string _messageText;
        private Client _from;
        private Client _to;
        public string MessageText
        {
            get { return _messageText; }
            set { _messageText = value; }
        }
        public Client From
        {
            get { return _from; }
            set { _from = value; }
        }
        public Client To
        {
            get { return _to; }
            set { _to = value; }
        }
    }
}
