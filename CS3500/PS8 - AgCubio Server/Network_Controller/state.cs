
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace Server
{
    public class State
    {
        private Action<State> callback;
        private Socket socket;
        private byte[] bytes;
        private Cube StatePlayer;
        
        public State(Action<State> callback, Socket Socket)
        {
            this.callback = callback;
            this.socket = Socket;
            
            this.Bytes = new byte[1024];

        }

        public Action<State> Callback
        {
            get { return callback; }
            set { callback = value; }
        }

        public Socket Socket
        {
            get { return socket; }
        }

        public byte[] Bytes
        {
            get { return bytes; }
            set { bytes = value; }
        }
        public Cube Player
        {
            get { return StatePlayer; }
            set { StatePlayer = value; }
        }
    }
}
