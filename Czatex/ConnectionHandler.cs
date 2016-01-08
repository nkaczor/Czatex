using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Czatex
{
    class ConnectionHandler
    {
        private void ReceiveCallback(IAsyncResult ar)
        {
            
            try
            {

                /* retrieve the SocketStateObject */
                SocketStateObject state = (SocketStateObject)ar.AsyncState;
                Socket socketFd = state.m_SocketFd;
                
                
                /* read data */
                int size = socketFd.EndReceive(ar);

                if (size > 0)
                {
                    
                    state.m_StringBuilder.Append(Encoding.ASCII.GetString(state.m_DataBuf, 0, size));

                    /* get the rest of the data */
                    socketFd.BeginReceive(state.m_DataBuf, 0, SocketStateObject.BUF_SIZE, 0,
                                          new AsyncCallback(ReceiveCallback), state);
                }
                else
                {
                   
                    /* all the data has arrived */
                    if (state.m_StringBuilder.Length > 1)
                    {
                        Console.WriteLine(state.m_StringBuilder.ToString());

                        /* shutdown and close socket */
                        socketFd.Shutdown(SocketShutdown.Both);
                        socketFd.Close();
                    }
                }
            }
            catch (Exception exc)
            {
                MessageBox.Show("Exception:\t\n" + exc.Message.ToString());
            }
        }

        private void ConnectCallback(IAsyncResult ar)
        {
            
            try
            {
                
                /* retrieve the socket from the state object */
                Socket socketFd = (Socket)ar.AsyncState;

                /* complete the connection */
                socketFd.EndConnect(ar);

                /* create the SocketStateObject */
                SocketStateObject state = new SocketStateObject();
                state.m_SocketFd = socketFd;


                
                /* begin receiving the data */
                socketFd.BeginReceive(state.m_DataBuf, 0, SocketStateObject.BUF_SIZE, 0,
                                     new AsyncCallback(ReceiveCallback), state);
                
            }
            catch (Exception exc)
            {
                MessageBox.Show("Exception:\t\n" + exc.Message.ToString());
               
            }
        }

        public void GetHostEntryCallback(IAsyncResult ar)
        {
            try
            {
                
              
                Socket socketFd = null;
                IPEndPoint endPoint = null;
              
                /* create a socket */
                socketFd = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

                /* remote endpoint for the socket */
                System.Net.IPAddress LongIp = System.Net.IPAddress.Parse("192.168.0.105");

                endPoint = new IPEndPoint(LongIp.Address, Int32.Parse("1234"));

              

                /* connect to the server */
                socketFd.BeginConnect(endPoint, new AsyncCallback(ConnectCallback), socketFd);
            }
            catch (Exception exc)
            {
                MessageBox.Show("Exception:\t\n" + exc.Message.ToString());
            }
        }

       
    }

    public class SocketStateObject
    {
        public const int BUF_SIZE = 1024;
        public byte[] m_DataBuf = new byte[BUF_SIZE];
        public StringBuilder m_StringBuilder = new StringBuilder();
        public Socket m_SocketFd = null;
    }
}

