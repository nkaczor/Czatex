using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Czatex.Model
{
    public class Client
    {
        public Client(string name) {
            _name = name;
            Messages = new List<Message>();
        }
        private string _name;
        public List<Message> Messages { get; set; }
        public string Name
        {
            get { return _name; }
            set { _name = value; }
        }
       
    }
}
