//Assignment 4 for EECS 214
//Out: May 7th, 2014
//Due: May 16th, 2014

using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using OutputPrint = System.Diagnostics.Debug;
namespace Assignment_4
{
    public class Graph : IEnumerable<int>
    {
        public class GraphNode
        {
            //This class should have a value, 
            //a list of integer weights
            //and an adjacency list of neighbors (you can use the C# List class)
            //Write the properties that get or set these
            int val;
            List<int> weights = new List<int>();
            List<GraphNode> neighbors = new List<GraphNode>();

            public GraphNode() { }

            public GraphNode(int v)
            {
                val = v;
            }

            public int Val
            {
                get { return val; }
                set { val = value; }
            }
            public List<int> Weights
            {
                get { return weights; }
                set { weights = value; }
            }
            public List<GraphNode> Neighbors
            {
                get { return neighbors; }
                set { neighbors = value; }
            }
        }

        private List<GraphNode> nodes = new List<GraphNode>();

        //the Graph class should have a list of graphnodes  
        //something like private List<GraphNode> nodes;

        /// <summary>
        /// Should add the node to the list of nodes
        /// </summary>
        public void AddNode(GraphNode node)
        {
            nodes.Add(node);
        }

        /// <summary>
        /// Creates a new graphnode from an input value and adds it to the list of graph nodes
        /// </summary>
        public void AddNode(int value)
        {
            GraphNode node = new GraphNode();
            node.Val = value;
            AddNode(node);
        }

        /// <summary>
        /// Adds a directed edge from one GraphNode to another. 
        /// Also insert the corresponding weight 
        /// </summary>
        public void AddDirectedEdge(GraphNode from, GraphNode to, int weight)
        {
            from.Neighbors.Add(to);
            from.Weights.Add(weight);

            to.Neighbors.Add(from);
            to.Weights.Add(weight);
        }

        /// <summary>
        /// Adds an undirected edge from one GraphNode to another. 
        /// Remember this means that both the from and two are neighbors of each other
        /// Also insert the corresponding weight 
        /// </summary>
        public void AddUndirectedEdge(GraphNode from, GraphNode to, int cost)
        {
            from.Neighbors.Add(to);
            from.Weights.Add(cost);
        }

        //Check if a value exists in the graph or not
        public bool Contains(int value)
        {
            for (int i = 0; i < Count; i++)
            {
                if (nodes[i].Val == value)
                    return true;
            }
            return false;
        }

        /// <summary>
        /// Should remove a node and all its edges and return true if successful
        /// </summary>
        public bool Remove(int value)
        {
            GraphNode remove = new GraphNode();
            if (!Contains(value))
                return false;
            for (int i = 0; i < Count; i++)
            {
                if (nodes[i].Val == value)
                {
                    remove = nodes[i];
                    break;
                }
            }
            if (remove == null)
                return false;
            nodes.Remove(remove);
            foreach (GraphNode g in nodes)
            {
                int i = g.Neighbors.IndexOf(remove);
                if (i != -1)
                {
                    g.Neighbors.RemoveAt(i);
                    g.Weights.RemoveAt(i);
                }
            }
            return true;
        }

        /// <summary>
        /// Is a property and returns the list of nodes, should be a one-liner
        /// </summary>
        public List<GraphNode> Nodes
        {
            get { return nodes; }
        }

        /// <summary>
        /// Is a property and returns the number of nodes in the graph, should be one-liner
        /// </summary>
        public int Count
        {
            get { return nodes.Count; }
        }

        IEnumerator<int> IEnumerable<int>.GetEnumerator()
        {
            for (int i = 0; i < Count; i++)
                yield return nodes[i].Val;
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            for (int i = 0; i < Count; i++)
                yield return nodes[i];
        }
        public void printNeighbors(GraphNode g)
        {
            foreach (GraphNode n in g.Neighbors)
                OutputPrint.WriteLine(n.Val);
        }
    }
}
