using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AgCubio
{
    public class World
    {
        private readonly int WIDTH;
        private readonly int HEIGHT;
        private Dictionary<int, Cube> cubes;

        public World()
        {
            WIDTH = 1000;
            HEIGHT = 1000;
            cubes = new Dictionary<int, Cube>();
        }

        public void addCube(Cube cube)
        {
            cubes[cube.UID] = cube;
        }

        public void removeCube(Cube cube)
        {
            //return cubes.Remove(cube);
        }

        public Dictionary<int, Cube> getCubes()
        {
            return cubes;
        }
    }
}
