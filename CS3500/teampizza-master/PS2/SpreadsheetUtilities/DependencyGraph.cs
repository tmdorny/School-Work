// Skeleton implementation written by Joe Zachary for CS 3500, September 2013.
// Version 1.1 (Fixed error in comment for RemoveDependency.)

using System.Collections.Generic;


namespace SpreadsheetUtilities //PS2 Tim Dorny u0829896
{

    /// <summary>
    /// (s1,t1) is an ordered pair of strings
    /// s1 depends on t1 --> t1 must be evaluated before s1
    /// 
    /// A DependencyGraph can be modeled as a set of ordered pairs of strings.  Two ordered pairs
    /// (s1,t1) and (s2,t2) are considered equal if and only if s1 equals s2 and t1 equals t2.
    /// (Recall that sets never contain duplicates.  If an attempt is made to add an element to a 
    /// set, and the element is already in the set, the set remains unchanged.)
    /// 
    /// Given a DependencyGraph DG:
    /// 
    ///    (1) If s is a string, the set of all strings t such that (s,t) is in DG is called dependents(s).
    ///        
    ///    (2) If s is a string, the set of all strings t such that (t,s) is in DG is called dependees(s).
    /// /// </summary>
    //
    // For example, suppose DG = {("a", "b"), ("a", "c"), ("b", "d"), ("d", "d")}
    //     dependents("a") = {"b", "c"}
    //     dependents("b") = {"d"}
    //     dependents("c") = {}
    //     dependents("d") = {"d"}
    //     dependees("a") = {}
    //     dependees("b") = {"a"}
    //     dependees("c") = {"a"}
    //     dependees("d") = {"b", "d"}
    public class DependencyGraph
    {
        // The data structure used for this graph is a dictionary containing a string key and DependencyNode value.
        private Dictionary<string, DependencyNode> graph;

        // private int used to record the number of ordered pairs in our graph
        private int size;

        /// <summary>
        /// Creates an empty DependencyGraph.
        /// </summary>
        public DependencyGraph()
        {
            graph = new Dictionary<string, DependencyNode>();
            size = 0;
        }


        /// <summary>
        /// The number of ordered pairs in the DependencyGraph.
        /// </summary>
        public int Size
        {
            get { return size; }
        }
        

        /// <summary>
        /// The size of dependees(s).
        /// This property is an example of an indexer.  If dg is a DependencyGraph, you would
        /// invoke it like this:
        /// dg["a"]
        /// It should return the size of dependees("a")
        /// </summary>
        public int this[string s]
        {
            get
            {
                // If there is no such key s, return 0.
                if (!(graph.ContainsKey(s)))
                {
                    return 0;
                }
                else
                {
                    return graph[s].getDependeeSize();
                }
            }
        }


        /// <summary>
        /// Reports whether dependents(s) is non-empty.
        /// </summary>
        public bool HasDependents(string s)
        {
            if (graph.ContainsKey(s) && graph[s].getDependentSize() > 0)
            {
                return true;
            }

            return false;
        }


        /// <summary>
        /// Reports whether dependees(s) is non-empty.
        /// </summary>
        public bool HasDependees(string s)
        {
            if(graph.ContainsKey(s) && graph[s].getDependeeSize() > 0)
            {
                return true;
            }

            return false;
        }


        /// <summary>
        /// Enumerates dependents(s).
        /// </summary>
        public IEnumerable<string> GetDependents(string s)
        {
            // If graph doesn't contain a key s, return empty hashset.
            if (!(graph.ContainsKey(s)))
            {
                return new HashSet<string>();
            }
            // Otherwise, return a list of its dependents in sorted order.
            return graph[s].getDependentStrings();
        }

        /// <summary>
        /// Enumerates dependees(s).
        /// </summary>
        public IEnumerable<string> GetDependees(string s)
        {
            // If graph doesn't contain a key s, return empty hashset.
            if (!(graph.ContainsKey(s)))
            {
                return new HashSet<string>();
            }
            // Otherwise, return a list of its dependees in sorted order.
            return graph[s].getDependeeStrings();
        }


        /// <summary>
        /// <para>Adds the ordered pair (s,t), if it doesn't exist</para>
        /// 
        /// <para>This should be thought of as:</para>   
        /// 
        ///   s depends on t
        ///
        /// </summary>
        /// <param name="s"> s cannot be evaluated until t is</param>
        /// <param name="t"> t must be evaluated first.  S depends on T</param>
        public void AddDependency(string s, string t)
        {
            // Variables to store newly constructed nodes.
            DependencyNode dependeeNode;
            DependencyNode dependentNode;

            // if both pairs are already-existing nodes
            if (graph.ContainsKey(s) && graph.ContainsKey(t))
            {
                // Simply update the references and return. (As long as that ordered pair has not yet been added.)
                if (graph[s].isDependentOn(graph[t]) && graph[s].isDependeeOf(graph[t]))
                {
                    // If the pair already exists within the graph, return.
                    return;
                }
                graph[s].addDependent(graph[t]);
                graph[t].addDependee(graph[s]);
                // Increment size
                size++;
                return;
            }
            // if just s has already has a node associated with it.
            else if (graph.ContainsKey(s))
            {
                // Initiallize node for t and update references
                dependentNode = new DependencyNode(t);
                graph[s].addDependent(dependentNode);
                dependentNode.addDependee(graph[s]);
                // Add new node to dependency graph
                graph.Add(t, dependentNode);
                // Increment size and return.
                size++;
                return;
            }
            // if just t already has a node associated with it.
            else if (graph.ContainsKey(t))
            {
                // Initiallize node for s and update references
                dependeeNode = new DependencyNode(s);
                dependeeNode.addDependent(graph[t]);
                graph[t].addDependee(dependeeNode);
                // Add new node to dependency graph
                graph.Add(s, dependeeNode);
                // Increment size and return.
                size++;
                return;
            }
            // Otherwise, if neither string have nodes associated to them...
            // initiallize nodes and set dependent/dependee references
            dependeeNode = new DependencyNode(s);
            dependentNode = new DependencyNode(t);
            dependeeNode.addDependent(dependentNode);
            dependentNode.addDependee(dependeeNode);

            // add nodes to graph
            graph.Add(s, dependeeNode);
            graph.Add(t, dependentNode);

            // increment size
            size++;
        }

        /// <summary>
        /// Removes the ordered pair (s,t), if it exists
        /// </summary>
        /// <param name="s"></param>
        /// <param name="t"></param>
        public void RemoveDependency(string s, string t)
        {
            // ensure that the ordered pair exists within our graph
            if (graph.ContainsKey(t) && graph.ContainsKey(s))
            {
                // ensure that the pair are dependent/dependees of each other
                if(graph[s].isDependentOn(graph[t]) && graph[s].isDependeeOf(graph[t]))
                {
                    // remove dependee/dependent references from each node
                    graph[s].removeDependent(graph[t]);
                    graph[t].removeDependee(graph[s]);

                    // decrement size
                    size--;
                }
               
            }
            
        }


        /// <summary>
        /// Removes all existing ordered pairs of the form (s,r).  Then, for each
        /// t in newDependents, adds the ordered pair (s,t).
        /// </summary>
        public void ReplaceDependents(string s, IEnumerable<string> newDependents)
        {
            // if there is no existing dependents under string s, create node for s and add dependents.
            if (!(graph.ContainsKey(s)))
            {
                DependencyNode newNode = new DependencyNode(s);
                graph.Add(s, newNode);

            }
            // clear dependents from node under string s and store number that were removed
            int removedPairs = graph[s].clearDependents();
            // int to store how many reference pairs are added
            int addedPairs = 0;

            // add newDependents and update references
            foreach (string newString in newDependents)
            {
                // If there is no key newString, create the node and add it to graph
                if (!(graph.ContainsKey(newString)))
                {
                    DependencyNode newNode = new DependencyNode(newString);
                    graph.Add(newString, newNode);
                }
                // add dependee reference
                graph[newString].addDependee(graph[s]);
                // finally, add the newNode to the existing node's dependent reference
                graph[s].addDependent(graph[newString]);
                // Increment addedPairs
                addedPairs++;
            }
            // Update size variable
            int sizeChange = addedPairs - removedPairs;
            size = size + sizeChange;
        }


        /// <summary>
        /// Removes all existing ordered pairs of the form (r,s).  Then, for each 
        /// t in newDependees, adds the ordered pair (t,s).
        /// </summary>
        public void ReplaceDependees(string s, IEnumerable<string> newDependees)
        {
            // if there is no existing dependees under string s, add node to graph.
            if (!(graph.ContainsKey(s)))
            {
                DependencyNode newNode = new DependencyNode(s);
                graph.Add(s, newNode);
            }
            // clear dependees from node under string s and store number that were removed
            int removedPairs = graph[s].clearDependees();
            // int to store how many reference pairs are added
            int addedPairs = 0;

            // add newDependees and update references
            foreach (string newString in newDependees)
            {
                // If there is no key newString, create the node and add it to graph
                if (!(graph.ContainsKey(newString)))
                {
                    DependencyNode newNode = new DependencyNode(newString);
                    graph.Add(newString, newNode);
                }
                // add dependent reference
                graph[newString].addDependent(graph[s]);
                // finally, add the newNode to the existing node's dependent reference
                graph[s].addDependee(graph[newString]);
                // Increment addedPairs
                addedPairs++;
            }
            // Update size variable
            int sizeChange = addedPairs - removedPairs;
            size = size + sizeChange;
        }

    }




}


