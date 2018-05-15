
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Timers;
using System.Text.RegularExpressions;
using System.Net.Sockets;
using System.Diagnostics;
using MySql.Data.MySqlClient;

namespace Server
{
    class Server
    {
        /// <summary>
        /// Represents the game world.
        /// </summary>
        private static World World;
        /// <summary>
        /// Set to true once player cube is sent to client
        /// </summary>
        private static bool PlayerSent = false;
        /// <summary>
        /// Contains sockets of all client connections.
        /// </summary>
        private static List<Socket> Sockets;
        /// <summary>
        /// Contains the current destination for cube.
        /// </summary>
        private static Tuple<int, int> Destination;
        /// <summary>
        /// Split player cube.
        /// </summary>
        private static Cube SplitPlayer;
        /// <summary>
        /// Timer used to control cube merges after split
        /// </summary>
        public static Timer RejoinTimer;
        /// <summary>
        /// Used for random number generation.
        /// </summary>
        private static Random rand = new Random();
        /// <summary>
        /// Used to connect to the server.
        /// </summary>
        public const string connectionString = "server=atr.eng.utah.edu;database=cs3500_tannerm;uid=cs3500_tannerm;password=PSWRD";

        static void Main(string[] args)
        {
            World = new World();
            Sockets = new List<Socket>();
            start();
        }

        public static void start()
        {
            // Set up timers
            // Second one is every heart beat
            Timer HeartBeatTimer = new System.Timers.Timer();
            HeartBeatTimer.Interval = 1000 / World.HPS;
            HeartBeatTimer.Elapsed += OnHeartBeatTimer;
            HeartBeatTimer.AutoReset = true;
            HeartBeatTimer.Enabled = true;

            RejoinTimer = new System.Timers.Timer();
            RejoinTimer.Enabled = false;
            RejoinTimer.Interval = 10000;
            RejoinTimer.Elapsed += OnRejoinTimer;

            NetworkController.Server_Awaiting_Client_Loop(handeNewClientConnections, DatabaseConnected);
        }
        /// <summary>
        /// Called when a connection request is recieved from database.
        /// </summary>
        /// <param name="state"></param>
        private static void DatabaseConnected(State state)
        {
            state.Callback = DatabaseRecieve;
            string InitialString = Encoding.UTF8.GetString(state.Bytes);
            NetworkController.i_want_more_data(state);
        }
        /// <summary>
        /// Called once the first bit of data has been recieved from the database.
        /// </summary>
        /// <param name="state"></param>
        private static void DatabaseRecieve(State state)
        {
            // Initialize strings used to send HTML to web server
            string InitialString = Encoding.UTF8.GetString(state.Bytes);
            StringBuilder HTMLToSend = new StringBuilder();
            string HTMLStart = "HTTP/1.1 200 OK\r\nConnection: close\r\nContent-Type: text/html; charset=UTF-8/r/n";
            string Buffer = "\r\n";

            // If connection requests the overall playeres stat sheet.
            if (InitialString.Contains("GET /players HTTP/1.1"))
            {
                // Build HTML
                string HTMLCode = World.getStats(1, null);

                HTMLToSend.Clear();
                HTMLToSend.Append(HTMLStart);
                HTMLToSend.Append(Buffer);
                HTMLToSend.Append(HTMLCode);

                // Send HTML to web
                NetworkController.DatabaseSend(state.Socket, HTMLToSend.ToString(), SendCallback);
            }
            // If web server requests a particular player's stats.
            else if (InitialString.Contains("GET /games?player="))
            {
                // Utilize indexes to get name of player out of recieved string.
                int FirstSpace = InitialString.IndexOf(' ');
                int SecondSpace = InitialString.IndexOf(' ', FirstSpace + 1);
                int NameLength = SecondSpace - InitialString.IndexOf('=') - 1;
                string PlayerName = InitialString.Substring(InitialString.IndexOf('=') + 1, NameLength);
                
                // Build HTML
                string HTMLCode = World.getStats(2, PlayerName);

                HTMLToSend.Clear();
                HTMLToSend.Append(HTMLStart);
                HTMLToSend.Append(Buffer);
                HTMLToSend.Append(HTMLCode);

                // Send HTML
                NetworkController.DatabaseSend(state.Socket, HTMLToSend.ToString(), SendCallback);
            }
            else if (InitialString.Contains("GET /eaten?id="))
            {
                // Get game session from recieved string
                int FirstSpace = InitialString.IndexOf(' ');
                int SecondSpace = InitialString.IndexOf(' ', FirstSpace + 1);
                int IDLength = SecondSpace - InitialString.IndexOf('=') - 1;
                string GameID = InitialString.Substring(InitialString.IndexOf('=') + 1, IDLength);

                // Build HTML
                string HTMLCode = World.getStats(3, GameID);

                HTMLToSend.Clear();
                HTMLToSend.Append(HTMLStart);
                HTMLToSend.Append(Buffer);
                HTMLToSend.Append(HTMLCode);

                // Send HTML
                NetworkController.DatabaseSend(state.Socket, HTMLToSend.ToString(), SendCallback);
            }
            else
            {
                // Build HTML for error message.
                string HTMLCode = World.getStats(4, null);

                HTMLToSend.Clear();
                HTMLToSend.Append(HTMLStart);
                HTMLToSend.Append(Buffer);
                HTMLToSend.Append(HTMLCode);

                NetworkController.DatabaseSend(state.Socket, HTMLToSend.ToString(), SendCallback);
            }


            //string DataSubstring = InitialString.Substring(InitialString.IndexOf('/'));

            //if (DataSubstring == "/ games ? player = Joe HTTP / 1.1)
        }
        /// <summary>
        /// Closes the socket once data is sent to web server.
        /// </summary>
        /// <param name="state"></param>
        private static void SendCallback (State state)
        {
            state.Socket.Close();
        }
        /// <summary>
        /// Called when a client initially connects.
        /// </summary>
        /// <param name="state"></param>
        private static void handeNewClientConnections(State state)
        {
            state.Callback = receivePlayerName;
            NetworkController.i_want_more_data(state);
        }
        /// <summary>
        /// Called when player name is sent from client.
        /// </summary>
        /// <param name="state"></param>
        private static void receivePlayerName(State state)
        {
            lock (World)
            {
                string Player = Encoding.UTF8.GetString(state.Bytes);
                Player = Player.Substring(0, Player.IndexOf('\n'));

                int PlayerID = ((Player.First() + Player.Last()) * 37) % 10000;
                

                Cube PlayerCube = new Cube(Player, PlayerID);
                World.addCube(PlayerCube);
                state.Player = PlayerCube;
                NetworkController.Send(state.Socket, JsonConvert.SerializeObject(PlayerCube));
                PlayerSent = true;

                // Add socket
                Sockets.Add(state.Socket);

                World.addFood(10);
                //Console.WriteLine("Player Name Added");
            }
            state.Callback = recieveMoveOrSplit;
            //updateWorld(state);
            
            NetworkController.i_want_more_data(state);
        }
        /// <summary>
        /// Handles reception of move or split requests.
        /// </summary>
        /// <param name="state"></param>
        private static void recieveMoveOrSplit(State state)
        {
            string ClientRequest = Encoding.UTF8.GetString(state.Bytes);
            //Console.WriteLine(ClientRequest);
            // do stuff
            Destination = formatDestination(ClientRequest);
            if(ClientRequest.Contains("split"))
            {
                lock (World)
                {
                    if(state.Player.NumberOfSplits < World.MaximumSplits)
                        World.splitPlayer(Destination, state.Player);
                }

                
                RejoinTimer.Enabled = true;
                RejoinTimer.Stop();
                RejoinTimer.Start();
                
                SplitPlayer = state.Player;
            }
            NetworkController.i_want_more_data(state);
        }
        /// <summary>
        /// Handles cubes rejoining
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private static void OnRejoinTimer(object sender, ElapsedEventArgs e)
        {
            lock (World)
            {
                double CombinedMass = 0;
                HashSet<int> keysToRemove = new HashSet<int>();
                foreach (int key in SplitPlayer.teamSet.Keys)
                {
                    Cube Current = SplitPlayer.teamSet[key];
                    CombinedMass += Current.Mass;
                    Current.Mass = 0;
                    keysToRemove.Add(key);
                    
                }

                foreach (int removeKey in keysToRemove)
                {
                    SplitPlayer.teamSet.Remove(removeKey);
                    World.Players.Remove(removeKey);
                }
                SplitPlayer.Mass += CombinedMass;
                World.Cubes[SplitPlayer.Uid] = SplitPlayer;
                World.Players[SplitPlayer.Uid] = SplitPlayer;
                SplitPlayer.NumberOfSplits = 0;
            }
            RejoinTimer.Enabled = false;
            
        }

        /// <summary>
        /// This is called when the heartbeat timer runs out
        /// </summary>
        /// <param name="source"></param>
        /// <param name="e"></param>
        public static void OnHeartBeatTimer(Object source, System.Timers.ElapsedEventArgs e)
        {
            lock (World)
            {
                // Update each player cube's position using their velocity.
                foreach (int key in World.Players.Keys)
                {
                    Cube CurrentCube = World.Cubes[key];
                    Tuple<int, int> CurrentDesitnation = Destination;

                    // Update move destination.
                    if (!(Destination == null))
                    {
                        Dictionary<int, Cube> debug = World.Players;
                        World.movePlayer(CurrentDesitnation, CurrentCube);
                    }

                    // Attrition.
                    if (CurrentCube.Mass > 800)
                        CurrentCube.Mass -= (World.AttritionRate / 5) * 2;
                    else if (CurrentCube.Mass > 200)
                        CurrentCube.Mass -= (World.AttritionRate / 5);

                    // Update cube position.
                    CurrentCube.X += CurrentCube.XVelocity;
                    CurrentCube.Y += CurrentCube.YVelocity;

                    // Ensure that cube stays within boundaries
                    if (CurrentCube.X < 0)
                    {
                        CurrentCube.X = 0;
                    }
                    else if (CurrentCube.X + CurrentCube.Width > World.Width)
                    {
                        CurrentCube.X = World.Width - CurrentCube.Width;
                    }
                    if (CurrentCube.Y < 0)
                    {
                        CurrentCube.Y = 0;
                    }
                    else if (CurrentCube.Y + CurrentCube.Width > World.Width)
                    {
                        CurrentCube.Y = World.Width - CurrentCube.Width;
                    }
                }
                // Add a food every beat
                if (World.Cubes.Count < 200)
                {
                    World.addFood(1);
                }

                // Have a chance at adding a virus to game screen.
                if (rand.Next(0, 100) < World.VirusChance)
                {
                    Cube Virus = new Cube(rand.Next(World.Width), rand.Next(World.Width));
                    if (!(World.Cubes.Keys.Contains(Virus.Uid)) && World.VirusCount < World.VirusLimit)
                    {
                        World.Cubes.Add(Virus.Uid, Virus);
                        World.VirusCount++;
                    }
                }
                // Send world to every player
                foreach (Socket socket in Sockets)
                {
                    NetworkController.Send(socket, World.sendWorld());
                }
            }
        }

        public static void updateWorld(State state)
        {
            lock (World)
            {
                if (PlayerSent)
                {
                    NetworkController.Send(state.Socket, World.sendWorld());
                }
            }
        }

        private static Tuple<int, int> formatDestination(string dest)
        {
            string[] numbers = Regex.Split(dest, @"\D+");
            int x_dest = int.Parse(numbers[1]);
            int y_dest = int.Parse(numbers[2]);
            Tuple<int, int> results = new Tuple<int,int>(x_dest, y_dest);
            return results;
        }
    }
}
