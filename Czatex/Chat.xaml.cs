using Czatex.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace Czatex
{
    /// <summary>
    /// Interaction logic for Window1.xaml
    /// </summary>
    public partial class Chat : Window
    {
        private Client natalia, kamil, duka, sebastian;
        List<Message> messages = new List<Message>();
        public Chat()
        {
            InitializeComponent();
            List <Client> clients = new List<Client>();
           
            natalia = new Client("Natalia");
            kamil = new Client("Kamil");
            duka = new Client("Duka");
            sebastian = new Client("Sebastian");

            clients.Add(natalia);
            clients.Add(kamil);
            clients.Add(duka);
            clients.Add(sebastian);
            clientsList.ItemsSource = clients;
            messagesList.ItemsSource = messages;
            messages.Add(new Message("Co Tam Duka porabiasz", natalia));
            messages.Add(new Message("Wpierdol?", duka));
            messages.Add(new Message("JEDZIEEEEEMY!!!", kamil));
            messages.Add(new Message("O TY", natalia));
            messages.Add(new Message("ggdgfdfgdfgdg fdff  df dsf ds fds f sdf sd fd sf dsf sd f sdf sd f sdf sd f sdf  sdf sd f sdf sd fs df s f sf  fs", sebastian));
           

        }

        private void sendButton_Click(object sender, RoutedEventArgs e)
        {
            
            messages.Add(new Message(messageTextBox.Text, kamil));
            messagesList.Items.Refresh();
            messageTextBox.Text = "";

        }
    }
}
