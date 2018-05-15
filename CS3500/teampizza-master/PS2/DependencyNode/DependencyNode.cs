using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DependencyNodes
{
    /// <summary>
    /// Class used to handle dependent and dependee references for a graph class.
    /// </summary>
    public class DependencyNode
    {
        private string nodeName;
        private List <DependencyNode> dependents;
        private List <DependencyNode> dependees;

        /// <summary>
        /// Creates a new DependencyNode object with the specified name and empty dependent and dependee lists.
        /// </summary>
        /// <param name="s">String used for the "name of the node.</param>
        public DependencyNode (string s)
        {
            nodeName = s;
            dependents = new List<DependencyNode>();
            dependees = new List<DependencyNode>();
        }

        /// <summary>
        /// Returns the name variable of a node.
        /// </summary>
        /// <returns>String representing the node.</returns>
        public string getName()
        {
            return nodeName;
        }

        /// <summary>
        /// Returns the list of dependents for a given node.
        /// </summary>
        /// <returns>List of dependent references.</returns>
        public List<string> getDependentStrings()
        {
            // List to store string "names" of nodes
            List<string> dependentStrings = new List<string>();
            foreach (DependencyNode n in this.dependents)
            {
                // Add each node name to list
                dependentStrings.Add(n.getName());
            }
            // Sorts the strings
            dependentStrings.Sort();
            // And returns the list
            return dependentStrings;

        }

        /// <summary>
        /// Returns the list of dependees for a given node.
        /// </summary>
        /// <returns>List of dependee references.</returns>
        public List<string> getDependeeStrings()
        {
            // List to store string "names" of nodes
            List<string> dependeeStrings = new List<string>();
            foreach (DependencyNode n in this.dependees)
            {
                // Add each node name to list
                dependeeStrings.Add(n.getName());
            }
            // Sorts the strings
            dependeeStrings.Sort();
            // And returns the list
            return dependeeStrings;

        }

        /// <summary>
        /// Adds the specified node to the reference node's dependents.
        /// </summary>
        /// <param name="n">Dependent node to be added</param>
        public void addDependent (DependencyNode n)
        {
            if (!(this.dependents.Contains(n)))
            {
                this.dependents.Add(n);
            }
            
        }

        /// <summary>
        /// Adds the specified node to the reference node's dependees.
        /// </summary>
        /// <param name="n">Dependee node to be added.</param>
        public void addDependee (DependencyNode n)
        {
            if (!(this.dependees.Contains(n)))
            {
                this.dependees.Add(n);
            }
        }

        /// <summary>
        /// Returns bool stating whether or not the given is dependent on the node passed into the method
        /// </summary>
        /// <param name="n">
        /// The node being checked for a dependent reference to the reference node.
        /// </param>
        /// <returns>Returns true if n contains a dependent reference to the reference node, false otherwise.</returns>
        public bool isDependentOn (DependencyNode n)
        {
            if (this.dependents.Contains(n))
            {
                return true;
            }

            return false;
        }

        /// <summary>
        /// Returns the number of dependee references found in the given node.
        /// </summary>
        /// <returns>Number of dependee references.</returns>
        public int getDependeeSize()
        {
            return this.dependees.Count;
        }

        /// <summary>
        /// Returns the number of dependee references found in the given node.
        /// </summary>
        /// <returns>Number of dependee references.</returns>
        public int getDependentSize()
        {
            return this.dependents.Count;
        }

        /// <summary>
        /// Removes the specified dependent from the reference node assuming it exists.
        /// </summary>
        /// <param name="n">Dependent node to be removed.</param>
        /// <returns>Returns true if the dependent node is successfully removed, false otherwise.</returns>
        public bool removeDependent (DependencyNode n)
        {
            return this.dependents.Remove(n);
        }

        /// <summary>
        /// Removes the specified dependee from the reference node assuming it exists.
        /// </summary>
        /// <param name="n">Dependee node to be removed.</param>
        /// <returns>Returns true if the dependee node is successfully removed, false otherwise.</returns>
        public bool removeDependee (DependencyNode n)
        {
            return this.dependees.Remove(n);
        }


        /// <summary>
        /// Returns bool stating whether or not the reference node is a dependee of the given node n.
        /// </summary>
        /// <param name="n">
        /// The node being checked for a dependee reference to the reference node.
        /// </param>
        /// <returns>Returns true if n contains a dependee reference to the reference node, false otherwise</returns>
        public bool isDependeeOf(DependencyNode n)
        {
            if (n.dependees.Contains(this))
            {
                return true;
            }

            return false;
        }

        /// <summary>
        /// Clears all dependent references (and their corresponding dependee references) from the reference node and returns the number of references that were cleared
        /// </summary>
        public int clearDependents()
        {
            // clear dependee references
            foreach (DependencyNode n in this.dependents)
            {
                n.removeDependee(this);
            }
            // store number of references/pairs that were removed
            int count = this.dependents.Count;
            // clear dependents references
            this.dependents.Clear();
            // return removed count for use in size variable
            return count;
        }

        /// <summary>
        /// Clears all dependee references from the reference node and returns the number of references that were cleared
        /// </summary>
        public int clearDependees()
        {
            // clear dependent references
            foreach (DependencyNode n in this.dependees)
            {
                n.removeDependent(this);
            }
            // store number of references/pairs that were removed
            int count = this.dependees.Count;
            // clear dependees references
            this.dependees.Clear();
            // return removed count for use in size variable 
            return count;
        }

    }
}
