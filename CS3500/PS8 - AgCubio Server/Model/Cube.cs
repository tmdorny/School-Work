using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Server
{
    [JsonObject(MemberSerialization.OptIn)]
    public class Cube
    {
        [JsonProperty(PropertyName = "loc_x")]
        public double X { get; set; }

        [JsonProperty(PropertyName = "loc_y")]
        public double Y { get; set; }

        [JsonProperty(PropertyName = "uid")]
        public int Uid { get; set; }

        [JsonProperty(PropertyName = "team_id")]
        public int Team { get; set; }

        //[JsonProperty]
        //public double Mass { get; set; }

        [JsonProperty]
        public string Name { get; private set; }

        [JsonProperty(PropertyName = "argb_color")]
        public int IntColor { get; private set; }

        [JsonProperty(PropertyName = "food")]
        public Boolean Food { get; private set; }

        private int Speed { get; set; }

        private double CubeMass;

        //public int Width;

        public Dictionary<int, Cube> teamSet { get; set; }

        private Random rand = new Random();
        public bool Virus;

        public double XVelocity { get; set; }
        public double YVelocity { get; set; }

        public double XMomentum { get; set; }
        public double YMomentum { get; set; }
        public int NumberOfSplits { get; set;}

        public int Width;

        public Stopwatch Stopwatch;

        public double MaxMass;

        public int HighestRank;
        public HashSet<string> PlayersEaten;
        public int CubesEaten;
        /// <summary>
        /// Represents the original "main" cube of teamset (has same uid and teamid). Null if not a split cube.
        /// </summary>
        public Cube Parent;

        /// <summary>
        /// Player creation constructor
        /// </summary>
        /// <param name="name"></param>
        /// <param name="uid"></param>
        public Cube(string name, int uid)
        {
            X = rand.Next(World.Width);
            Y = rand.Next(World.Height);
            Uid = uid;
            Team = uid;
            CubeMass = World.PlayerStartMass;
            Name = name;
            IntColor = rand.Next(Int32.MaxValue) *-1;
            Food = false;
            Width = (int)Math.Sqrt(CubeMass);
            teamSet = new Dictionary<int, Cube>();

            Stopwatch = new Stopwatch();
            Stopwatch.Start();
            MaxMass = CubeMass;
            PlayersEaten = new HashSet<string>();
            CubesEaten = 0;


        }
        /// <summary>
        /// Creates food cube object.
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <param name="uid"></param>
        public Cube(int x, int y, int uid)
        {
            X = x;
            Y = y;
            Uid = uid;
            Team = 0;
            CubeMass = World.FoodValue;
            Name = "";
            IntColor = rand.Next(Int32.MaxValue) *-1;
            Food = true;
            Width = (int)Math.Sqrt(CubeMass);
        }

        public Cube(int x, int y)
        {
            X = x;
            Y = y;
            
            Uid = rand.Next(10001, 20000);
            Team = 0;
            CubeMass = 400;
            Name = "";
            IntColor = IntColor - 116603087;
            Food = false;
            Virus = true;
            Width = (int)Math.Sqrt(CubeMass);

        }
        /// <summary>
        /// Creation of a split cube. Takes in parent cube as member variable
        /// </summary>
        /// <param name="_X"></param>
        /// <param name="_Y"></param>
        /// <param name="_Uid"></param>
        /// <param name="_Team"></param>
        /// <param name="_Mass"></param>
        /// <param name="_Name"></param>
        /// <param name="_Color"></param>
        /// <param name="_Food"></param>
        public Cube(double _X, double _Y, int _Uid, int _Team, double _Mass, string _Name, int _Color, bool _Food, Cube parent)
        {
            X = _X;
            Y = _Y;
            Uid = _Uid;
            Team = _Team;
            CubeMass = _Mass;
            Name = _Name;
            IntColor = _Color;
            Food = _Food;
            Width = (int) Math.Sqrt(_Mass);
            Parent = parent;
        }
        /// <summary>
        /// Mass of cube, when updated, also updates width.
        /// </summary>
        [JsonProperty]
        public double Mass
        {
            get
            {
                return CubeMass;
            }
            set
            {
                CubeMass = value;
                Width = (int) Math.Sqrt(CubeMass);
                if (MaxMass < CubeMass)
                    MaxMass = CubeMass;
            }
        }



    }

}

/* Notes
    Maybe have another constructor if we are making a cube as food?
*/

