using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace AgCubio
{
    public partial class LoginScreen : Form
    {
        private System.Drawing.SolidBrush brush;
        private Socket socket;
        private bool NameSent = false;
        private bool connected = false;
        private World World;
        private string JsonCubes;
        private string DataString;
        private string EndOfDataCutoff;
        private Cube PlayerCube;
        private string PreviousIncomingChanges;
        private int x_dest;
        private int y_dest;

        public LoginScreen()
        {
            InitializeComponent();

            NewGamePanel.Enabled = false;
            NewGamePanel.Hide();

            (NewGamePanel as Control).KeyDown += new KeyEventHandler(GamePanelKeyPress);
            
            //GamePanel.Enabled = false;
            //GamePanel.Hide();
            this.DoubleBuffered = true;
            


        }
        /// <summary>
        /// Handles spacebar press to cause cube to split.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void GamePanelKeyPress(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Space)
            {
                Network.Send(socket, "(split, " + x_dest + ", " + y_dest + ")\n");
            }
        }

        /// <summary>
        /// Handles enter key press when name is entered. Causes the game to start.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Key_down(object sender, KeyEventArgs e)
        {
            if(e.KeyCode == Keys.Return)
            {
                World = new World();
                if (!connected)
                {
                    socket = Network.Connect_to_Server(CallbackName, ServerTextBox.Text);
                    connected = true;
                }
                NewGamePanel.Show();
                NewGamePanel.Enabled = true;
                NewGamePanel.Focus();
                PlayerNameTextBox.Enabled = false;

                //GamePanel.Show();
                //GamePanel.Enabled = true;
            }
        }

        /// <summary>
        /// First callback method when connected to socket. Sends player name to server,
        /// </summary>
        /// <param name="state"></param>
        private void CallbackName(State state)
        {
            if (!(NameSent))
            {
                Network.Send(socket, PlayerNameTextBox.Text + "\n");
                NameSent = true;
            }
            //Console.Out.Write("CALLBACKNAME");
            state.Callback = InitialPlayerRecieve;

            
            
        }
        /// <summary>
        /// Method called when second callback is made from socket connection. Recieves the initial player information.
        /// </summary>
        /// <param name="state"></param>
        private void InitialPlayerRecieve(State state)
        {
            
            // Turn the byte array stored in the state into a string
            string incomingChanges = System.Text.Encoding.UTF8.GetString(state.Bytes);
            //Console.Out.Write(incomingChanges);
            
            PlayerCube = JsonConvert.DeserializeObject<Cube>(incomingChanges);
            
            World.addCube(PlayerCube);
            

            
            //GamePanel.Invalidate();
            


            state.Callback = RepaintData;

            Network.i_want_more_data(state);

        }
        /// <summary>
        /// Method called each time new data is recieved from socket beyond inital player info. Reads info and adds to world.
        /// </summary>
        /// <param name="state"></param>
        private void RepaintData(State state)
        {
            string incomingChanges = System.Text.Encoding.UTF8.GetString(state.Bytes);
            state.Bytes = new byte[1024];
            

            DataString = incomingChanges.Substring(0, incomingChanges.LastIndexOf('\n'));
            if (!(DataString == "") && (!(DataString.First() == '{')))
            {
                string StartOfDataCutoff;
                try
                {
                    StartOfDataCutoff = DataString.Substring(0, DataString.IndexOf('\n'));
                    DataString = DataString.Substring(DataString.IndexOf('\n') + 1);
                }
                catch (ArgumentOutOfRangeException)
                {
                    StartOfDataCutoff = DataString;
                    DataString = "";
                }


                string MergedJson = EndOfDataCutoff + StartOfDataCutoff;
                lock (World)
                {
                    World.addCube(JsonConvert.DeserializeObject<Cube>(MergedJson));
                }
            }

            try
            {
                EndOfDataCutoff = incomingChanges.Substring(incomingChanges.LastIndexOf('\n') + 1);
            }
            catch (NullReferenceException)
            {
                EndOfDataCutoff = "";
            }

            // Game Over
            if (PlayerCube.CubeMass == 0)
            {
                MessageBox.Show(null, "GAME OVER", "GAMEOVER");
            }

            // Name of player cube.


            if (!(DataString == ""))
            {
                char[] Splitta = { '\n' };
                string[] CubeStrings = DataString.Split(Splitta);
                lock (World)
                {
                    foreach (string cubeJson in CubeStrings)
                    {
                        Cube NewCube = JsonConvert.DeserializeObject<Cube>(cubeJson);
                            World.addCube(NewCube);



                    }
                }
                
            }
            PreviousIncomingChanges = incomingChanges;
            NewGamePanel.Invalidate();
            Network.i_want_more_data(state);
            
        }
        /// <summary>
        /// Closes application. Button disappeared ????
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void CloseButton_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }
        /// <summary>
        /// Closes application.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void close_button_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }
        /// <summary>
        /// Paints the world onto the game panel.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void NewGamePanel_Paint(object sender, PaintEventArgs e)
        {
            //Console.Out.WriteLine("Paint");
            Dictionary<int, Cube> WorldCubes = World.getCubes();

            if (PlayerCube == null)
            {
                return;
            }


            //try
            //{


                lock (World)
                {
                    // Coordinates of player cube, used to draw player centered view.
                    double PlayerX = PlayerCube.XCoord;
                    double PlayerY = PlayerCube.YCoord;
                    double PlayerSize = PlayerCube.WidthHeight;
                    // "Scale" of cubes
                    double ViewScalar = 1;


                    foreach (int key in WorldCubes.Keys)
                    {
                        Color color = Color.FromArgb((int)WorldCubes[key].RGBColor);

                        brush = new System.Drawing.SolidBrush(color);

                        // Values to convert values for player-centered screen view.
                        double CubeXCoord = WorldCubes[key].XCoord - PlayerX + (((750 - (PlayerSize * ViewScalar)) / 2)) - (PlayerSize / 2);
                        double CubeYCoord = WorldCubes[key].YCoord - PlayerY + (((750 - (PlayerSize * ViewScalar)) / 2)) - (PlayerSize / 2);
                        double CubeSize = WorldCubes[key].WidthHeight * ViewScalar;
                        Rectangle CubeTangle = new Rectangle(0, 0, 0, 0);
                        bool IsDrawn = false;
                        // If cube will be displayed, draw it.
                        //if (!(CubeXCoord + CubeSize < 0 && CubeYCoord + CubeSize < 0) && !(CubeXCoord > 750 && CubeYCoord > 750))
                        //{
                            if (CubeXCoord < 0)
                            {

                            }

                            CubeTangle = new Rectangle((int) CubeXCoord, (int) CubeYCoord, (int) CubeSize, (int) CubeSize);
                            IsDrawn = true;
                            e.Graphics.FillRectangle(brush, CubeTangle);
                        //}

                        //CubeTangle = new Rectangle((int)WorldCubes[key].XCoord, (int)WorldCubes[key].YCoord, WorldCubes[key].WidthHeight, WorldCubes[key].WidthHeight);
                        //e.Graphics.FillRectangle(brush, CubeTangle);
                        //Console.Out.WriteLine("x: " + cube.XCoord + " " + "y: " + cube.YCoord);
                        // Name of player cube.
                        if ((!(WorldCubes[key].Food) && WorldCubes[key].CubeMass > 0) && IsDrawn)
                        {
                            color = Color.FromArgb((int)WorldCubes[key].RGBColor + 50000);
                            //int RectX = (int)WorldCubes[key].XCoord + ((int)WorldCubes[key].WidthHeight / 2) - ((((int)WorldCubes[key].XCoord + ((int)WorldCubes[key].WidthHeight) / 2)) / 2);

                            StringFormat stringFormat = new StringFormat();
                            stringFormat.Alignment = StringAlignment.Center;
                            stringFormat.LineAlignment = StringAlignment.Center;

                            e.Graphics.DrawString(WorldCubes[key].CubeName, new Font("Arial", 12), new System.Drawing.SolidBrush(color), CubeTangle, stringFormat);
                        }

                        if (WorldCubes[key].UID == PlayerCube.UID)
                        {
                            PlayerCube = WorldCubes[key];
                            MassLabel.Text = PlayerCube.CubeMass.ToString();
                        }
                    }
                }
            //}
            //catch (Exception ex)
            //{
            //    Console.Out.WriteLine("DAMN");
            //}
            if (NameSent)
            {
                Network.Send(socket, "(move, " + x_dest + ", " + y_dest + ")\n");
            }

            NewGamePanel.Invalidate();
        }
        /// <summary>
        /// Updates the postion of the mouse over the screen.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void NewGamePanel_MouseMove(object sender, MouseEventArgs e)
        {
            x_dest = e.X;
            y_dest = e.Y;
        }
    }
}
