using Czatex.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Timers;
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
        List<Message> messages = new List<Message>();
        List<Message> publicMessages = new List<Message>();
        List<Client> clients = new List<Client>();
        private Boolean isPublic = true;
        private String selectedUser = "";
        private ChatManager chatManager;
        private string myLogin;
        private void setClientsTimer()
        {
            Timer tmrClients = new Timer();
            tmrClients.Interval = 1000; // 1 second
            tmrClients.Elapsed += getClients;
            tmrClients.AutoReset = true;
            tmrClients.Enabled = true;
        }
        private void setMessagesTimer()
        {
            Timer tmrMessages = new Timer();
            tmrMessages.Interval = 1000; // 1 second
            tmrMessages.Elapsed += getMessages;
            tmrMessages.AutoReset = true;
            tmrMessages.Enabled = true;
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            chatManager.Leave(myLogin);
        }

        private void getClients(Object source, ElapsedEventArgs e)
        {
            this.Dispatcher.Invoke((Action)(() =>
            {
                List<Client> newClients = chatManager.GetAllClients(myLogin);
                foreach (var client in newClients) {
                    if (!clients.Any(x => x.Name == client.Name))
                        clients.Add(client);
                }
                foreach (var client in clients)
                {
                    if (!clients.Any(x => x.Name == client.Name))
                        clients.Remove(client);
                }
                clientsList.ItemsSource = clients;
                clientsList.Items.Refresh();
            }));
        }
        private void getMessages(Object source, ElapsedEventArgs e)
        {
            this.Dispatcher.Invoke((Action)(() =>
            {
                if (isPublic)
                    messages.AddRange(chatManager.GetAllMessages(myLogin));
                else
                {
                    //List<Message> userMessages = clients.First(x => x.Name == selectedUser).Messages;
                    messages.AddRange(chatManager.GetMessagesFrom(myLogin, selectedUser));
                }
                messagesList.ItemsSource = messages;
                messagesList.Items.Refresh();

            }));
        }
        public Chat(ChatManager chatManager, string myLogin)
        {
            this.chatManager = chatManager;
            this.myLogin = myLogin;
            InitializeComponent();
            setClientsTimer();
            setMessagesTimer();
            messages = publicMessages;
        }

        private void sendButton_Click(object sender, RoutedEventArgs e)
        {
            if (isPublic)
                chatManager.SendMessageToAll(myLogin, messageTextBox.Text);
            else
                chatManager.SendMessageTo(myLogin, selectedUser, messageTextBox.Text);
            messages.Add(new Message(messageTextBox.Text, myLogin));
            messagesList.Items.Refresh();
            messageTextBox.Text = "";

        }

        private void clientsList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (e.AddedItems.Count > 0)
            {
                selectedUser = ((Client)e.AddedItems[0]).Name;
                messages = clients.First(x => x.Name == selectedUser).Messages;
                isPublic = false;
                friendLabel.Content = selectedUser;
            }

        }

        private void publicButton_Click(object sender, RoutedEventArgs e)
        {
            selectedUser = "";
            messages = publicMessages;
            isPublic = true;
            friendLabel.Content = "Czat publiczny";
        }
    }
}
