using MySql.Data.MySqlClient;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Server
{
    /// <summary>
    /// Represents the game world of AgCubio.
    /// </summary>
    public class World
    {
        /// <summary>
        /// Used to connect to server.
        /// </summary>
        public const string connectionString = "server=atr.eng.utah.edu;database=cs3500_tannerm;uid=cs3500_tannerm;password=PSWRD";
        
        /// <summary>
        /// Width, Height - the game size of the world
        /// </summary>
        public const int Width = 750, Height = 750;
        /// <summary>
        /// Heartbeats per second - how many updates the server should attempt to execute per second.
        /// Note: adequate work will simply update the world as fast as possible.
        /// </summary>
        public const int HPS = 60;
        /// <summary>
        /// Top speed - how fast cubes can move when small
        /// Low speed - how fast the biggest cubes move
        /// </summary>
        public const int TopSpeed = 10, LowSpeed = 1;
        /// <summary>
        /// Attrition rate - how fast cubes lose mass
        /// </summary>
        public const int AttritionRate = 1;
        /// <summary>
        /// Food value - the default mass of food
        /// </summary>
        public const int FoodValue = 10;
        /// <summary>
        /// Player start mass - the default starting mass of the player.
        /// </summary>
        public const int PlayerStartMass = 200;
        /// <summary>
        /// Max food - how many food to maintain in the world.Server should update one food per heartbeat if below this.
        /// </summary>
        public const int MaxFood = 200;
        /// <summary>
        /// Minimum split mass - players are not allowed to split if below this mass
        /// </summary>
        public const int MinimumSplitMass = 100;
        /// <summary>
        /// Maximum split distance - how far a cube can be "thrown" when split
        /// </summary>
        public const int MaximumSplitDistance = 20;
        /// <summary>
        /// Maximum splits - how many total cubes a single player is allowed.
        /// Note: our test server does not implement this. Try setting it to around 10-20.
        /// </summary>
        public const int MaximumSplits = 5;
        /// <summary>
        /// Absorb distance delta - how close cubes have to be in order for the larger to eat the smaller
        /// </summary>
        public const int AbsorbDistanceDelta = 1;
        /// <summary>
        /// Momentum the cube being split off starts with
        /// </summary>
        public const int SplitMomentum = 30;

        /// <summary>
        /// Chance of a Virus being spawned per heartbeat (percentage).
        /// </summary>
        public const int VirusChance = 1;
        /// <summary>
        /// Amount of virus' on the screen.
        /// </summary>
        public const int VirusLimit = 3;
        public int VirusCount;
        /// <summary>
        /// Data to send to client
        /// </summary>
        private StringBuilder worldData = new StringBuilder();


        // Non constant member variables
        public Dictionary<int, Cube> Cubes;
        public Dictionary<int, Cube> Players;

        public World()
        {
            Cubes = new Dictionary<int, Cube>();
            Players = new Dictionary<int, Cube>();
            VirusCount = 0;
        }

        
        /// <summary>
        /// Add cube to the world
        /// </summary>
        /// <param name="cube"></param>
        public void addCube(Cube cube)
        {
            int CubeID = cube.Uid;
            while (Cubes.Keys.Contains(CubeID))
            {
                CubeID = (CubeID + 1) % 10000;
            }
            cube.Uid = CubeID;
            Cubes.Add(cube.Uid, cube);
            if (!cube.Food)
            {
                Players.Add(CubeID, cube);
            }
        }

        
        /// <summary>
        /// Move player to the given destination
        /// </summary>
        /// <param name="destination"></param>
        /// <param name="player"></param>
        public void movePlayer(Tuple<int, int> destination, Cube player)
        {
            // Get the destinations
            int x_dest = destination.Item1;
            int y_dest = destination.Item2;
            bool isNegativeX = false;
            bool isNegativeY = false;
            // Set ratios
            double XRatio = (x_dest - player.X) / Width;
            double YRatio = (y_dest - player.Y) / Height;
            if (XRatio < 0)
            {
                isNegativeX = true;
                XRatio *= (-1);
            }
            if (YRatio < 0)
            {
                isNegativeY = true;
                YRatio *= (-1);
            }

            double CubeVelocity = 10000 / player.Mass;

            double XVelocity = XRatio * CubeVelocity;
            double YVelocity = YRatio * CubeVelocity;

            if (XVelocity < LowSpeed)
            {
                XVelocity = LowSpeed;
            }
            else if (XVelocity > TopSpeed)
            {
                XVelocity = TopSpeed;
            }

            if (YVelocity < LowSpeed)
            {
                YVelocity = LowSpeed;
            }
            else if (YVelocity > TopSpeed)
            {
                YVelocity = TopSpeed;
            }
            // Reset velocities to negative if necessary.
            if (isNegativeX)
            {
                player.XVelocity = player.XMomentum + (XVelocity * (-1));
            }
            else
            {
                player.XVelocity = player.XMomentum + XVelocity;
            }
            if (isNegativeY)
            {
                player.YVelocity = player.YMomentum + (YVelocity * (-1));
            }
            else
            {
                player.YVelocity = player.YMomentum + YVelocity;
            }
            // If cursor is close to cube, velocity is simply momentum.
            if (Math.Abs(player.X - x_dest) < 5)
            {
                player.XVelocity = player.XMomentum;
            }
            if (Math.Abs(player.Y - y_dest) < 5)
            {
                player.YVelocity = player.YMomentum;
            }
            // Decrease momentum each tick
            if (player.XMomentum > 0)
            {
                player.XMomentum -= 1;
            }
            if (player.YMomentum > 0)
            {
                player.YMomentum -= 1;
            }
            Cubes[player.Uid] = player;
            
        }
        /// <summary>
        /// Handles splitting of players
        /// </summary>
        /// <param name="destination"></param>
        /// <param name="player"></param>
        public void splitPlayer(Tuple<int, int> destination, Cube player)
        {
            Random rand = new Random();
            int uidForNewSplit = rand.Next(10000);
            double XDest;
            double YDest;
            double XRatio;
            double YRatio;

            HashSet<Cube> AddCubesToTeam = new HashSet<Cube>();

            // SPLIT ALL CUBES UNDER PLAYER'S TEAMID
            if (!(player.teamSet == null))
            {
                foreach (int teamKey in player.teamSet.Keys)
                {
                    Cube TeamCube = player.teamSet[teamKey];
                    if (TeamCube.Mass < MinimumSplitMass)
                        continue;

                    while (Cubes.Keys.Contains(uidForNewSplit))
                    {
                        uidForNewSplit = rand.Next(10000);
                    }
                    TeamCube.Mass = TeamCube.Mass / 2;

                    Cube SplitCube = new Cube(TeamCube.X, TeamCube.Y, uidForNewSplit, player.Uid, TeamCube.Mass, TeamCube.Name, TeamCube.IntColor, false, TeamCube.Parent);

                    XDest = destination.Item1;
                    YDest = destination.Item2;
                    XRatio = (XDest - SplitCube.X) / World.Width;
                    YRatio = (YDest - SplitCube.Y) / World.Width;

                    SplitCube.XMomentum = SplitMomentum * XRatio;
                    SplitCube.YMomentum = SplitMomentum * YRatio;

                    AddCubesToTeam.Add(SplitCube);
                    //player.teamSet.Add(SplitCube.Uid, SplitCube);
                    Cubes.Add(SplitCube.Uid, SplitCube);
                    Players.Add(SplitCube.Uid, SplitCube);
                }
            }

            foreach (Cube cube in AddCubesToTeam)
            {
                player.teamSet.Add(cube.Uid, cube);
            }

            if (player.Mass < MinimumSplitMass)
                return;

            // SPLIT PLAYER CUBE
            player.Mass = player.Mass / 2;
            while (Cubes.Keys.Contains(uidForNewSplit))
            {
                uidForNewSplit = rand.Next(10000);
            }
            Cube NewSplit = new Cube(player.X, player.Y, uidForNewSplit, player.Uid, player.Mass, player.Name, player.IntColor, false, player);

            XDest = destination.Item1;
            YDest = destination.Item2;
            XRatio = (XDest - NewSplit.X) / World.Width;
            YRatio = (YDest - NewSplit.Y) / World.Width;

            NewSplit.XMomentum = SplitMomentum * XRatio;
            NewSplit.YMomentum = SplitMomentum * YRatio;

            if (!(player.teamSet == null))
            {
                player.teamSet.Add(NewSplit.Uid, NewSplit);
            }
            
            Cubes.Add(NewSplit.Uid, NewSplit);
            Players.Add(NewSplit.Uid, NewSplit);

            // Update split count
            player.NumberOfSplits++;
            

        }
        /// <summary>
        /// Adds the specified amount of food to random parts of the world.
        /// </summary>
        /// <param name="amountOfFood"></param>
        public void addFood(int amountOfFood)
        {
            Random rand = new Random();
            for(int i = 0; i < amountOfFood; i++)
            {
                int uid = rand.Next(10000);
                if (!Cubes.Keys.Contains(uid))
                {
                    Cubes[uid] = new Cube(rand.Next(Width), rand.Next(Height), uid);
                }
                
            }
        }
        /// <summary>
        /// Prepares a JSON string to send to the client of the current gamestate.
        /// </summary>
        /// <returns></returns>
        public string sendWorld()
        {
            worldData.Clear();
            //worldData = new StringBuilder();
            HashSet<int> keysToRemove = new HashSet<int>();
            HashSet<int> playerKeysToRemove = new HashSet<int>();
            HashSet<int> playerCubesToSplit = new HashSet<int>();
            
            lock (Cubes)
            {
                lock (Players)
                {
                    // Iterate through each cube in the world. (all cubes, food, players, and viruses are stored in this dictionary.
                    foreach (int key in Cubes.Keys)
                    {
                        // For each cube in the world, check if any player cubes initiate a collision. If so, handle accordingly.
                        foreach (int playerKey in Players.Keys)
                        {
                            // Create the range of X coordinates that would initiate a collision.
                            double playerXRange1 = Players[playerKey].X;
                            double playerXRange2 = playerXRange1 + Players[playerKey].Width;

                            // Create the range of Y coordinates that would initiate a collision.
                            double playerYRange1 = Players[playerKey].Y;
                            double playerYRange2 = playerYRange1 + Math.Sqrt(Players[playerKey].Mass);

                            // If the coordinates of the current cube fall within both X and Y ranges, then a collision is initiated.
                            if (Cubes[key].X > playerXRange1 && Cubes[key].X < playerXRange2)
                            {
                                if (Cubes[key].Y > playerYRange1 && Cubes[key].Y < playerYRange2)
                                {
                                    // The collsion method returns the uid of any player that is eaten
                                    int RemovedUID = collision(Players[playerKey], Cubes[key]);
                                    // If the returned uid is indeed a player in the world that is not colliding with itself, that cube is removed.
                                    if (Players.Keys.Contains(RemovedUID) && RemovedUID != key)
                                    {
                                        playerKeysToRemove.Add(RemovedUID);
                                    }
                                    // If colliding cube is a virus, the player cube is marked to split once foreach loop completes.
                                    if (Cubes[key].Virus)
                                    {
                                        playerCubesToSplit.Add(Players[playerKey].Uid);
                                        keysToRemove.Add(key);
                                        Cubes[key].Mass = 0;
                                    }

                                }
                            }
                        }
                        // StringBuilder built from each cube's data.
                        worldData.Append(JsonConvert.SerializeObject(Cubes[key]));
                        worldData.Append("\n");
                        // If food is eaten, set mass to 0 so that it is removed.
                        if (Cubes[key].Mass == 0 && Cubes[key].Food)
                        {
                            keysToRemove.Add(key);
                        }
                        // If player is eaten, set mass to 0 so that it is removed,
                        else if (Cubes[key].Mass == 0 && !(Cubes[key].Food) && !Cubes[key].Virus)
                        {
                            playerKeysToRemove.Add(key);
                            keysToRemove.Add(key);

                            if (Cubes[key].teamSet != null && Cubes[key].teamSet.Count == 0)
                            {
                                playerDied(Cubes[key]);
                            }
                            
                        }

                    }

                    // Rank each player
                    List<Cube> playersTobeRanked = new List<Cube>();
                    foreach(int playerKey in Players.Keys)
                    {
                        playersTobeRanked.Add(Cubes[playerKey]);
                    }
                    playersTobeRanked.OrderBy(p => p.Mass);
                    int playerI = 0;
                    foreach(Cube player in playersTobeRanked)
                    {
                        if (playerI < 5)
                            player.HighestRank = playerI + 1;
                        else
                            break;
                    }
                }

                // Remove each 0-mass cube from the dictionary.
                foreach (int key in keysToRemove)
                {
                    Cube Current = Cubes[key];
                    if (!(Current.teamSet == null) && Current.teamSet.Count > 0)
                    {
                        bool ReplacementFound = false;
                        Cube NewParent = null;
                        // If player cube has outstanding "splits" with mass greater than 0, then control is transfered to the earliest cube.
                        foreach (int NewKey in Current.teamSet.Keys)
                        {
                            if (Current.teamSet[NewKey].Mass > 0 && !ReplacementFound)
                            {
                                Cubes[NewKey].Uid = Current.Uid;
                                Cubes[NewKey].Stopwatch = Current.Stopwatch;
                                Cubes[NewKey].Parent = null;
                                NewParent = Cubes[NewKey];
                                ReplacementFound = true;
                            }
                            // Set all cubes in team set parent to new "main" cube.
                            if (ReplacementFound)
                            {
                                Cubes[NewKey].Parent = NewParent;
                            }
                        }

                    }

                    Cubes.Remove(key);
                    //Players.Remove(key);
                }

            }
            foreach (int virusKey in playerCubesToSplit)
            {
                splitPlayer(new Tuple<int, int>((int)Cubes[virusKey].X, (int)Cubes[virusKey].Y), Cubes[virusKey]);
            }
            foreach (int playerKey in playerKeysToRemove)
            {
                Players.Remove(playerKey);
            }
            return worldData.ToString();
        }
        /// <summary>
        /// Updates database every time a player dies.
        /// </summary>
        /// <param name="cube"></param>
        private void playerDied(Cube cube)
        {
            // Get time of life
            cube.Stopwatch.Stop();
            int elapsedTime = cube.Stopwatch.Elapsed.Seconds;

            // Get max mass of player
            double maxMass = cube.MaxMass;

            // Get Highest rank
            int rank = cube.HighestRank;

            // Get list of players eaten
            HashSet<String> playersEaten = cube.PlayersEaten;

            // Number of cubes eaten
            int numberOfCubesEaten = cube.CubesEaten;

            // Get time of Death
            DateTime timeOfDeath = DateTime.Now;
            // Connect to the DB
            using (MySqlConnection conn = new MySqlConnection(connectionString))
            {
                try
                {
                    // Open a connection
                    conn.Open();

                    // Get the Sessionid
                    MySqlCommand lastSessionId = new MySqlCommand("select max(id) from MainTable", conn);
                    int sessionId;
                    if (lastSessionId == null)
                        sessionId = 0;
                    else
                        sessionId = Int32.Parse(lastSessionId.ExecuteScalar().ToString()) + 1;

                    // Create a command
                    MySqlCommand command = conn.CreateCommand();
                    
                    command.CommandText = "insert into MainTable(id, Name, LifeTime, TimeOfDeath, MaxMass, MaxRank, CubesEaten, NumberOfPlayersEaten) values("
                            + sessionId + ", '" + cube.Name + "', " + elapsedTime + ", '" + timeOfDeath.ToString("H:mm") +  "', " + maxMass + ", " + rank + ", "
                            + numberOfCubesEaten + ", " + playersEaten.Count + ");";
                   
                    command.CommandText += "select * from MainTable;";

                    foreach(String eaten in playersEaten)
                    {
                        command.CommandText += "insert into PlayersEaten(id, EatenPlayer) values(" + sessionId + ", '" + eaten + "');";
                    }

                    // Execute the command and cycle through the DataReader object
                    using (MySqlDataReader reader = command.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            Console.WriteLine(reader["id"] + " : " + reader["Name"]);
                        }
                        reader.Close();
                    }
                }
                catch (Exception e)
                {
                    Console.WriteLine(e.Message);
                }

                //sendStats(1);
            }
        }

        /// <summary>
        /// Handles collisions of cubes. If a cube is removed, its uid is returned, otherwise -1 is returned.
        /// </summary>
        /// <param name="cube1"></param>
        /// <param name="cube2"></param>
        /// <returns></returns>
        private int collision(Cube cube1, Cube cube2)
        {
            // Check if the cubes colliding are on the same team
            if (cube1.Team == cube2.Team)
                return -1;
            //Check if hit virus
            if (cube1.Virus || cube2.Virus)
            {
                return -1;
            }
            
            // Food and cube collided
            if(cube1.Food && !cube2.Food)
            {
                cube2.Mass += cube1.Mass;
                cube2.CubesEaten++;
                cube1.Mass = 0;
                return cube1.Uid;
            }
            // Food and cube collided
            else if(cube2.Food && !cube1.Food)
            {
                cube1.Mass += cube2.Mass;
                cube1.CubesEaten++;
                cube2.Mass = 0;
                return cube2.Uid;
            }
            // Two players collided
            else if(!cube1.Food && !cube2.Food)
            {
                double XDiff = Math.Abs(cube1.X - cube2.X);
                double YDiff = Math.Abs(cube1.Y - cube2.Y);

                Cube BigGuy;
                Cube LittleGuy;
                // Find out which cube is bigger
                if (cube1.Width > cube2.Width && Math.Abs(cube1.Width - cube2.Width) > 2)
                {
                    BigGuy = cube1;
                    LittleGuy = cube2;
                }
                else if (cube1.Width < cube2.Width && Math.Abs(cube1.Width - cube2.Width) > 2)
                {
                    BigGuy = cube2;
                    LittleGuy = cube1;
                }
                else
                {
                    return -1;
                }
                // If cubes are too close in size don't eat
                if (XDiff < 10 && YDiff < 10)
                {
                    BigGuy.Mass += LittleGuy.Mass;
                    BigGuy.CubesEaten++;

                    // If cube is eaten by "main" cube, add name to eaten list. If cube is eaten by split cube, add name of eaten cube to parent's list.
                    if (BigGuy.Parent == null)
                    {
                        BigGuy.PlayersEaten.Add(LittleGuy.Name);
                    }
                    else
                    {
                        BigGuy.Parent.PlayersEaten.Add(LittleGuy.Name);
                    }
                    
                    LittleGuy.Mass = 0;
                    //Players.Remove(LittleGuy.Uid);
                    return LittleGuy.Uid;
                }
                
            }
            return -1;
        }
        /// <summary>
        /// Creates the HTML string to be sent to the web server.
        /// </summary>
        /// <param name="i"></param>
        /// <param name="dataString"></param>
        /// <returns></returns>
        public string getStats(int i, string dataString)
        {


            // Essential HTML part 
            string BeginningHTML = @"
<html>
	<head><!-- Latest compiled and minified CSS -->
<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css' integrity='sha384-1q8mTJOASx8j1Au+a5WDVnPi2lkFfwwEAa8hDDdjZlpLegxhjVME1fgjWPGmkzs7' crossorigin='anonymous'>
<!-- Optional theme -->
<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap-theme.min.css' integrity='sha384-fLW2N01lMqjakBkx3l/M9EahuwpSfeNvV63J5ezn3uZzapT0u7EYsXMjQV+0En5r' crossorigin='anonymous'>
<!-- Latest compiled and minified JavaScript -->
<script src='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js' integrity='sha384-0mSbJDEHialfmuBBQP6A4Qrprq5OVfW37PRR3j5ELqxss1yVqOtnepnHVP9aJ7xS' crossorigin='anonymous'></script></head>
	<body>
		<nav class='navbar navbar-default'>
			<div class='container-fluid'>
				<a class='navbar-brand' href='#'>AgCubio</a>
			</div>
		</nav>
{0}
	</body>
</html>";
            // Initialize variables.
            string data = "";

            string table = " ";

            string FormatString = "";

            string ReturnLink = "";

            string PlayerReturnLink = "";

            using (MySqlConnection conn = new MySqlConnection(connectionString))
            {
                try
                {
                    // Open a connection
                    conn.Open();

                    // Create a command
                    MySqlCommand command = conn.CreateCommand();




                    // Execute the command and cycle through the DataReader object
                    //using (MySqlDataReader reader = command.ExecuteReader())
                    //{
                    switch (i)
                    {
                        // Case where overall player stats are requested.
                        case 1:

                            command.CommandText = "select * from MainTable;";
                            // Execute the command and cycle through the DataReader object
                            using (MySqlDataReader reader = command.ExecuteReader())
                            {
                                

                                data = @"<div class='bs-example' data-example-id='simple-table'> <table class='table table-striped'> 
			<caption>AgCubio Player Scores!!!!!!!!!!!!!!!!!!!!!!!!!!!!</caption> 
			<thead> 
				<tr> 
					<th>Name</th> 
					<th>Life Time</th>
					<th>Maximum Mass</th>
					<th>Max Rank</th>
					<th>Cubes Eaten</th>
					</tr> </thead> 
					<tbody> 
                        {0}
					</tbody> </table> </div>";
                                while (reader.Read())
                                {
                                    table += string.Format(@"<tr>
                                <td>{0}</td>
                                <td>{1}</td>
                                <td>{2}</td>
                                <td>{3}</td>
                                <td>{4}</td>
                                </tr>", "<a href=\"http://localhost:11100/games?player=" + reader["Name"] + "\">" + reader["Name"] + "</a>", 
                                    reader["LifeTime"], reader["MaxMass"], reader["MaxRank"], reader["CubesEaten"]);
                                }

                                FormatString = String.Format(data, table);
                                reader.Close();
                                break;
                            }
                        // Case where a particular player's games are requested.
                        case 2:
                            
                            command.CommandText = "select * from MainTable where Name = '" + dataString + "';";
                            // Execute the command and cycle through the DataReader object
                            using (MySqlDataReader reader = command.ExecuteReader())
                            {
                                

                                data = @"<div class='bs-example' data-example-id='simple-table'> <table class='table table-striped'> 
			<caption>{0}'s AgCubio Stats! </caption> 
			<thead> 
				<tr> 
					<th>Name</th> 
					<th>Life Time</th>
					<th>Maximum Mass</th>
					<th>Max Rank</th>
					<th>Cubes Eaten</th>
                    <th>Time Of Death</th>
					<th>Player Cubes Eaten</th>
					</tr> </thead> 
					<tbody> 
                        {1}
                        {2}
					</tbody> </table> </div>";
                                while (reader.Read())
                                {
                                    table += string.Format(@"<tr>
                                <td>{0}</td>
                                <td>{1}</td>
                                <td>{2}</td>
                                <td>{3}</td>
                                <td>{4}</td>
                                <td>{5}</td>
                                <td>{6}</td>
                                </tr>", reader["Name"], reader["LifeTime"], reader["MaxMass"], reader["MaxRank"], reader["CubesEaten"], reader["TimeOfDeath"], "<a href=\"http://localhost:11100/eaten?id=" + reader["id"] + "\">" + reader["NumberOfPlayersEaten"] + "</a>");
                                    ReturnLink = "<p> <a href=\"http://localhost:11100/players" + "\"> Return to Player Table </a>";
                                }

                                FormatString = String.Format(data, dataString, ReturnLink, table);
                                reader.Close();
                                break;
                            }
                        // Case where a particular session is requested and eaten players are to be displayed.
                        case 3:


                            command.CommandText = "SELECT * FROM PlayersEaten LEFT JOIN MainTable USING(id) WHERE id = " + dataString + ";";
                            // Execute the command and cycle through the DataReader object
                            using (MySqlDataReader reader = command.ExecuteReader())
                            {


                                data = @"<div class='bs-example' data-example-id='simple-table'> <table class='table table-striped'> 
			<caption>Players eaten by player with id of {0}.</caption> 
			<thead> 
				<tr> 
					<th>Name</th> 
                    <th>Players Eaten</th>
					<th>Life Time</th>
					<th>Maximum Mass</th>
					<th>Max Rank</th>
					<th>Cubes Eaten</th>
                    <th>Time Of Death</th>
					<th>Player Cubes Eaten</th>
					</tr> </thead> 
					<tbody> 
                        {1}
                        {2}
                        {3}
                        
					</tbody> </table> </div>";
                                while (reader.Read())
                                {
                                    table += string.Format(@"<tr>
                                <td>{0}</td>
                                <td>{1}</td>
                                <td>{2}</td>
                                <td>{3}</td>
                                <td>{4}</td>
                                <td>{5}</td>
                                <td>{6}</td>
                                <td>{7}</td>
                                </tr>", reader["Name"], reader["EatenPlayer"], reader["LifeTime"], reader["MaxMass"], reader["MaxRank"], reader["CubesEaten"], reader["TimeOfDeath"], reader["NumberOfPlayersEaten"]);
                                    
                                }
                                ReturnLink = "<p> <a href=\"http://localhost:11100/players" + "\"> Return to Player Table </a>";
                                // If no data is returned by database, PlayerReturnLink
                                try
                                {
                                    PlayerReturnLink = "<p> <a href=\"http://localhost:11100/games?player=" + reader["Name"] + "\"> Return to Player Stats </a> </p>";
                                }
                                catch (MySql.Data.MySqlClient.MySqlException)
                                {
                                    PlayerReturnLink = "<b>No data found for the specified player.</b>";
                                    FormatString = String.Format(data, dataString, ReturnLink, PlayerReturnLink, "");
                                    reader.Close();
                                    break;
                                }

                                FormatString = String.Format(data, dataString, ReturnLink, PlayerReturnLink, table);
                                reader.Close();
                                break;
                            }

                            // Case when an invalid url is sent to server.
                        case 4:
                            FormatString = "<p>ERROR ERROR ERROR EROOR EROOOR ERROOOOOOOOR EROROOOOOOOOOORRRORORORORORRRRRRRRRRRRRRR!!!!!!</p>";
                            


                            break;

                    }
                }
                catch (Exception e)
                {
                    Console.WriteLine(e.Message);
                }
            }


            string finalHTML = String.Format(BeginningHTML, FormatString);
            Console.WriteLine(finalHTML);
            return finalHTML;
        }
    }
}