using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AgCubio
{
    public class Cube
    {
        
        private double loc_x;
        private double loc_y;
        private double argb_color;
        private int uid;
        private bool food;
        private string Name;
        private double Mass;
        private int team_id;
        int HeightWidth;
        
        public Cube()
        {
            
        }

        public void update(string values)
        {
            Cube rebuilt = JsonConvert.DeserializeObject<Cube>(values);
        }
        [JsonProperty(PropertyName = "loc_x")]
        public double XCoord
        {
            get { return loc_x; }
            set { loc_x = value; }
        }
        [JsonProperty(PropertyName = "loc_y")]
        public double YCoord
        {
            get { return loc_y; }
            set { loc_y = value; }
        }
        [JsonProperty(PropertyName = "argb_color")]
        public double RGBColor
        {
            get { return argb_color; }
            set { argb_color = value; }
        }
        [JsonProperty(PropertyName = "uid")]
        public int UID
        {
            get { return uid; }
            set { uid = value; }
        }
        [JsonProperty(PropertyName = "food")]
        public bool Food
        {
            get { return food; }
            set { food = value; }
        }
        [JsonProperty(PropertyName = "Name")]
        public string CubeName
        {
            get { return Name; }
            set { Name = value; }
        }
        [JsonProperty(PropertyName = "Mass")]
        public double CubeMass
        {
            get { return Mass; }
            set { Mass = value; HeightWidth = (int) Math.Pow(value, .67); }
        }
        [JsonProperty(PropertyName = "team_id")]
        public double TeamID
        {
            get { return Mass; }
            set { Mass = value; }
        }

        public int WidthHeight
        {
            get { return HeightWidth; }
            
        }

    }
}
