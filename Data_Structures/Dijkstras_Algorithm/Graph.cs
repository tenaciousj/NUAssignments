//Assignment 7 for EECS 214
//Out: May 30rd, 2014
//Due: June 6th, 2014

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;

namespace Assignment_7
{
    //public class Graph : IEnumerable<int>
    public class Graph
    {
        //ENSURE THAT YOU HAVE THE ":IComparable<GraphNode>" below
        public class GraphNode : IComparable<GraphNode>
        {
            //ALL THE STUFF FROM ASSIGNMENT 6 and ONE ADDITIONAL FIELD, cost 
            //Of course, if you need other variables, feel free to add them
            private int cost;
            Point position;
            String name;
            int val;
            List<int> weights = new List<int>();
            List<GraphNode> neighbors = new List<GraphNode>();
            public GraphNode predecessor;

            public GraphNode() { }

            public GraphNode(int v)
            {
                val = v;
            }
            public GraphNode(String n)
            {
                name = n;
            }
            public GraphNode(String n, Point pos)
            {
                name = n;
                position = pos;
            }
            public Point Pos
            {
                get { return position; }
                set { position = value; }
            }
            public String Name
            {
                get { return name; }
                set { name = value; }
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
            //Property to get and set cost
            public int Cost
            {
                get { return cost; }
                set { cost = value; }
            }

            //YOU AVE TO INCLUDE THIS COMPARETO FUNCTION BECAUSE 
            //THE GRAPHNODE IMPLEMENTS THE ICOMPARABLE INTERFACE
            //DONT WORRY ABOUT IT, ITS A C# WAY OF COMPARING OBJECTS
            //TO RETURN IF AN OBJECT IS GREATER THAN OR LESS THAN ANOTHER OBJECT
            public int CompareTo(GraphNode other)
            {
                if (this.cost < other.cost) return -1;
                else if (this.cost > other.cost) return 1;
                else return 0;
            }
        }

        private List<GraphNode> nodes = new List<GraphNode>();

        public Graph()
        {
            GraphNode sanfran = new GraphNode("San Francisco", new Point(25, 40)); //0
            GraphNode denver = new GraphNode("Denver", new Point(200, 100));//1
            GraphNode dallas = new GraphNode("Dallas", new Point(250, 250));//2
            GraphNode chicago = new GraphNode("Chicago", new Point(300, 60));//3
            GraphNode newyork = new GraphNode("New York", new Point(450, 100));//4
            GraphNode losangeles = new GraphNode("Los Angeles", new Point(35, 200));//5
            GraphNode sandiego = new GraphNode("San Diego", new Point(55, 275));//6
            GraphNode miami = new GraphNode("Miami", new Point(400, 325));//7

            AddNode(sanfran);
            AddNode(denver);
            AddNode(dallas);
            AddNode(chicago);
            AddNode(newyork);
            AddNode(losangeles);
            AddNode(sandiego);
            AddNode(miami);

            //all flights to San Francisco
            AddDirectedEdge(denver, sanfran, 90);
            AddDirectedEdge(chicago, sanfran, 60);

            //all flights to Los Angeles
            AddDirectedEdge(sanfran, losangeles, 45);
            AddDirectedEdge(denver, losangeles, 100);
            AddDirectedEdge(dallas, losangeles, 80);
            AddDirectedEdge(sandiego, losangeles, 50);

            //all flights to San Diego
            AddDirectedEdge(dallas, sandiego, 80);

            //all flights to Denver
            AddDirectedEdge(chicago, denver, 25);
            AddDirectedEdge(newyork, denver, 100);

            //all flights to Dallas
            AddDirectedEdge(newyork, dallas, 125);
            AddDirectedEdge(miami, dallas, 50);

            //all flights to Chicago
            AddDirectedEdge(newyork, chicago, 80);

            //all flights to Miami
            AddDirectedEdge(newyork, miami, 90);

        }

        /// <summary>
        /// Should add the node to the list of nodes
        /// </summary>
        public void AddNode(GraphNode node)
        {
            // adds a node to the graph
            nodes.Add(node);
        }

        /// <summary>
        /// Creates a new graphnode from an input value and adds it to the list of graph nodes
        /// </summary>
        public void AddNode(int value)
        {
            GraphNode node = new GraphNode(value);
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

        //Check if a name exists in the graph or not
        public bool Contains(String name)
        {
            for (int i = 0; i < Count; i++)
            {
                if (nodes[i].Name == name)
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
            //fill this up, otherwise it'll generate a property/indexer error
            get { return nodes; }
        }


        /// <summary>
        /// Is a property and returns the number of nodes in the graph, should be one-liner
        /// </summary>
        public int Count
        {
            //fill this up, otherwise it'll generate a property/indexer error 
            get { return nodes.Count; }
        }

        //YOU SHOULD HAVE ALL THE STUFF FROM ASSIGNMENT 6 and ADD DIJKSTRA'S ALGORITHM to the GRAPH CLASS
        /// Implementation of Djikstra's Algorithm. 

        public List<GraphNode> DijkstraShortestPath(GraphNode start, GraphNode finish)
        {
            List<GraphNode> returnList = new List<GraphNode>(); //constains the list of nodes to go from start to finish
            PriorityQueue<GraphNode> PQ = new PriorityQueue<GraphNode>();

            //NOTICE HOW YOU HAVE ACCESS TO ALL THE FUNCTIONS YOU NEED, i.e.
            //PQ.Insert(GraphNode insertNode)
            //PQ.ExtractMin()
            //PQ.DecreaseKey(GraphNode item, newCost)

            foreach (GraphNode g in Nodes)
            {
                if (g.Name == start.Name)
                    g.Cost = 0;
                else
                    g.Cost = Int32.MaxValue;
                g.predecessor = null;
                PQ.Insert(g);
            }
            while (PQ.Count() != 0)
            {
                GraphNode u = PQ.ExtractMin();
                if (u.Name == finish.Name)
                {
                    GraphNode trace = u;
                    while (trace != null)
                    {
                        returnList.Add(trace);
                        trace = trace.predecessor;
                    }
                    break;
                }
                foreach (GraphNode v in u.Neighbors)
                {
                    int w = u.Weights[u.Neighbors.IndexOf(v)];
                    int newCost = u.Cost + w;
                    if (newCost < v.Cost)
                    {
                        v.Cost = newCost;
                        PQ.DecreaseKey(PQ.Data.IndexOf(v));
                        v.predecessor = u;
                    }
                }
            }

            return returnList;
        }
    }
}
