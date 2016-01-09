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
        }
        private string _name;
      
        public string Name
        {
            get { return _name; }
            set { _name = value; }
        }
       
    }
}
