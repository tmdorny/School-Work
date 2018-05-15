using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace AgCubio
{
    public class State
    {
        private Action<State> callback ;
        private Socket socket;
        private byte[] bytes;
        public State(Action<State> callback, Socket Socket)
        {
            this.callback = callback;
            this.socket = Socket;
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
    }
}
