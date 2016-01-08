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
        public MainWindow()
        {
            InitializeComponent();
            TcpClient client = new TcpClient("192.168.0.105", 1234);

            Stream stream = client.GetStream();

            StreamWriter writer = new StreamWriter(stream);

            writer.WriteLine("Testing...");

            client.Close();

            //try
            //{

            //    ConnectionHandler cHandler = new ConnectionHandler(); 

            //        /* get DNS host information */
            //        Dns.BeginGetHostEntry("192.168.0.105",
            //                              new AsyncCallback(cHandler.GetHostEntryCallback), null);


            //}
            //catch (Exception exc)
            //{
            //    MessageBox.Show("Exception:\t\n" + exc.Message.ToString());
            //}
        }

        private void textBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

        private void button_Click(object sender, RoutedEventArgs e)
        {
            var chat = new Chat();
            chat.Show();
            this.Close();
        }
    }
}
