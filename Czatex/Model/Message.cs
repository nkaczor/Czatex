using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Czatex.Model
{
    public class Message
    {
        public Message(string messageText, string from, string to)
        {
            _messageText = messageText;
            _from = from;
            _to = to;
        }
        public Message(string messageText, string from)
        {
            _messageText = messageText;
            _from = from;
            _to = null;
        }
        private string _messageText;
        private string _from;
        private string _to;
        public string MessageText
        {
            get { return _messageText; }
            set { _messageText = value; }
        }
        public string From
        {
            get { return _from; }
            set { _from = value; }
        }
        public string To
        {
            get { return _to; }
            set { _to = value; }
        }
    }
}
