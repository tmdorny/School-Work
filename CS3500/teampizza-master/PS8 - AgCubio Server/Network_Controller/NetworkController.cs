using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Server
{
    public static class NetworkController
    {
        public static ManualResetEvent ManReset = new ManualResetEvent(false);
        public static ManualResetEvent ManReset2 = new ManualResetEvent(false);

        public static Socket Connect_to_Server(Action<State> callback_function, string hostname)
        {
            TcpClient client = new TcpClient(hostname, 11000);
            Socket socket = new Socket(SocketType.Stream, ProtocolType.Tcp);
            State myState = new State(callback_function, socket);
            socket.BeginConnect(hostname, 11000, new AsyncCallback(Connected_to_Server), myState);

            return socket;
        }

        public static void Connected_to_Server(IAsyncResult state_in_an_ar_object)
        {

            State StateObject = state_in_an_ar_object.AsyncState as State;
            Socket socket = StateObject.Socket;

            // Call Callback Function
            StateObject.Callback(StateObject);

            StateObject.Bytes = new byte[1024];
            socket.BeginReceive(StateObject.Bytes, 0, 1024, new SocketFlags(), new AsyncCallback(ReceiveCallback), StateObject);


        }

        public static void ReceiveCallback(IAsyncResult state_in_an_ar_object)
        {
            State StateObject = state_in_an_ar_object.AsyncState as State;
            int BytesRecieved = StateObject.Socket.EndReceive(state_in_an_ar_object);
            //Console.Write(BytesRecieved);
            if (BytesRecieved == 0)
            {
                // Connection has been closed.
            }
            else
            {
                //Console.Write(BytesRecieved);
                Socket socket = StateObject.Socket;

                // Call Callback Function
                StateObject.Callback(StateObject);
            }
        }

        public static void i_want_more_data(State state)
        {
            Socket socket = state.Socket;
            socket.BeginReceive(state.Bytes, 0, 1024, new SocketFlags(), new AsyncCallback(ReceiveCallback), state);
        }

        public static void Send(Socket socket, String data)
        {
            if (socket != null)
            {
                byte[] toBytes = Encoding.ASCII.GetBytes(data);
                //Console.Write(data);
                socket.BeginSend(toBytes, 0, toBytes.Length, new SocketFlags(), new AsyncCallback(SendCallBack), new State(null, socket));
            }
            //Console.WriteLine("Data sent: " + data);
        }

        public static void DatabaseSend(Socket socket, String data, Action<State> callback)
        {
            State sendState = new State(callback, socket);

            if (socket != null)
            {
                byte[] toBytes = Encoding.ASCII.GetBytes(data);
                //Console.Write(data);
                socket.BeginSend(toBytes, 0, toBytes.Length, new SocketFlags(), new AsyncCallback(SendCallBackDatabase), sendState);
            }
            //Console.WriteLine("Data sent: " + data);
        }

        public static void SendCallBack(IAsyncResult state_in_an_ar_object)
        {
            State StateObject = (State)state_in_an_ar_object.AsyncState;
            int sent = StateObject.Socket.EndSend(state_in_an_ar_object);
            //Console.WriteLine("" + sent);
        }

        public static void SendCallBackDatabase(IAsyncResult ar)
        {
            State StateObject = (State)ar.AsyncState;
            int sent = StateObject.Socket.EndSend(ar);
            StateObject.Callback(StateObject);
        }

        // New methods


        /// <summary>
        /// Asks OS to listen for a connection and save callback function with that request. Upon recieving connection request, calls Accept_a_New_Client
        /// </summary>
        /// <param name="callback"></param>
        public static void Server_Awaiting_Client_Loop(Action<State> callback, Action<State> callback2)
        {
            Socket socket = new Socket(SocketType.Stream, ProtocolType.Tcp);
            Socket webSocket = new Socket(SocketType.Stream, ProtocolType.Tcp);
            //socket.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.IPv6Only, false);
            socket.Bind(new IPEndPoint(IPAddress.IPv6Any, 11000));
            webSocket.Bind(new IPEndPoint(IPAddress.IPv6Any, 11100));
            socket.Listen(100);
            webSocket.Listen(10);
            State state = new State(callback, socket);
            State webState = new State(callback2, webSocket);
            try
            {
                // Waits for connection.
                ManReset.Reset();
                Console.WriteLine("Waiting for connection...");
                socket.BeginAccept(new AsyncCallback(Accept_a_New_Client), state);
                Console.WriteLine("Waiting for database...");
                webSocket.BeginAccept(new AsyncCallback(Accept_Database_Connection), webState);
                ManReset.WaitOne();
            }
            catch (Exception e)
            {
                Console.Write(e.Message);
            }
        }

        /// <summary>
        /// Creates a new socket, calls the provided callback method, and awaits a new connection request.
        /// </summary>
        /// <param name="ar"></param>
        public static void Accept_a_New_Client(IAsyncResult ar)
        {
            Console.WriteLine("Connection Recieved.");
            State state = (State)ar.AsyncState;

            // Creates socket
            Socket socket = state.Socket;
            Socket newSocket = socket.EndAccept(ar);



            //Await new connetion request
            //newSocket.BeginReceive(state.Bytes, 0, 1024, new SocketFlags(), new AsyncCallback(ReceiveCallback), state);

            // Create a new state
            State newState = new State(state.Callback, newSocket);
            state.Callback(newState);
            // Allow new client to connect
            socket.BeginAccept(new AsyncCallback(Accept_a_New_Client), state);
        }

        /// <summary>
        /// Creates a new socket, calls the provided callback method, and awaits a new connection request.
        /// </summary>
        /// <param name="ar"></param>
        public static void Accept_Database_Connection(IAsyncResult ar)
        {
            Console.WriteLine("Database contact Recieved.");
            State state = (State)ar.AsyncState;

            // Creates socket
            Socket socket = state.Socket;
            Socket newSocket = socket.EndAccept(ar);



            //Await new connetion request
            //newSocket.BeginReceive(state.Bytes, 0, 1024, new SocketFlags(), new AsyncCallback(ReceiveCallback), state);

            // Create a new state
            State newState = new State(state.Callback, newSocket);
            state.Callback(newState);
            // Allow new client to connect
            socket.BeginAccept(new AsyncCallback(Accept_Database_Connection), state);
        }


    }
}
