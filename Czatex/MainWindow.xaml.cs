using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Czatex
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        ChatManager chatManager;
        public MainWindow()
        {
            InitializeComponent();
            chatManager = new ChatManager();
        }

   
        private void button_Click(object sender, RoutedEventArgs e)
        {
            string login = loginTextBox.Text;

            if (login.Length == 0)
            {
                alertLabel.Content = "Wpisz jakiś login";
            }
            else if (login.Any(x => Char.IsWhiteSpace(x))) {
                alertLabel.Content = "Login zawiera białe znaki.";
            }
            else
            {
                int status = chatManager.Join(login);
                if (status == 1) { 
                    var chat = new Chat();
                    chat.Show();
                    this.Close();
                }
                else if (status == 2)
                {
                    alertLabel.Content = "Login zajęty";
                }
                else
                {
                    alertLabel.Content = "Wystąpił błąd";
                }
            }
            
        }
    }
}
