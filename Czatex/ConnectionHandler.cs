using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
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
                    
                    
                }
                 
                receiveDone.Set();
                
            }
            catch (Exception exc)
            {
                MessageBox.Show("Exception:\t\n" + exc.Message.ToString());
            }
        }



        private ManualResetEvent connectDone = new ManualResetEvent(false);
        private ManualResetEvent sendDone = new ManualResetEvent(false);
        private ManualResetEvent receiveDone = new ManualResetEvent(false);
        public void SendData(String message)
        {
            
            sendDone.Reset();
            try
            {
                byte[] dataBuf = Encoding.ASCII.GetBytes(message);
                Socket socketFd = currentSocketFd;
                /* begin sending the date */
                
                socketFd.BeginSend(dataBuf, 0, dataBuf.Length, 0,
                                   new AsyncCallback(SendCallback), socketFd);
                
                sendDone.WaitOne();
            }
            catch (Exception exc)
            {
                Console.WriteLine(exc.Message.ToString());
            }
        }
        private void SendCallback(IAsyncResult ar)
        {
            try
            {
                // Retrieve the socket from the state object.
                Socket client = (Socket)ar.AsyncState;
                
                // Complete sending the data to the remote device.
                int bytesSent = client.EndSend(ar);
                Console.WriteLine("Sent {0} bytes to server.", bytesSent);

                // Signal that all bytes have been sent.
                sendDone.Set();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }
        }

        public string Receive()
        {
            receiveDone.Reset();
            /* begin receiving the data */
            SocketStateObject state = new SocketStateObject();
            
            state.m_SocketFd = currentSocketFd;
            

            Socket socketFd = currentSocketFd;
            
            socketFd.BeginReceive(state.m_DataBuf, 0, SocketStateObject.BUF_SIZE, 0,
                                 new AsyncCallback(ReceiveCallback), state);
            
            receiveDone.WaitOne();
            
            return state.m_StringBuilder.ToString();

        }
        private void ConnectCallback(IAsyncResult ar)
        {
            
            try
            {

                
                /* retrieve the socket from the state object */
                currentSocketFd = (Socket)ar.AsyncState;

                /* complete the connection */
                currentSocketFd.EndConnect(ar);
                
                /* create the SocketStateObject */

                connectDone.Set();
               

            }
            catch (Exception exc)
            {
                MessageBox.Show("Exception:\t\n" + exc.Message.ToString());
               
            }
           
        }
        private Socket currentSocketFd = null;
        public void Connect()
        {
            connectDone.Reset();
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

                connectDone.WaitOne();
                
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

