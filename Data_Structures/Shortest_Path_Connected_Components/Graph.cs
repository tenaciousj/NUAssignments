//Assignment 6 for EECS 214
//Out: May 23rd, 2014
//Due: May 30th, 2014

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;

namespace Assignment_6
{
    //public class Graph : IEnumerable<int>
    public class Graph
    {
        public class GraphNode
        {
            //Other than the fields you included in the earlier asignment
            //Add these two fields (basically to use them in the visualizer)
            //Point position and String name
            //Consider writing properties or constructors to get/set these
            Point position;
            String name;
            int val;
            List<int> weights = new List<int>();
            List<GraphNode> neighbors = new List<GraphNode>();

            //for finding shorted path
            public GraphNode predecessor;
            public int distance;

            //for connected components
            int component;
            bool visited = false;

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
            public int Component
            {
                get { return component; }
                set { component = value; }
            }
            public bool Visited
            {
                get { return visited; }
                set { visited = value; }
            }
        }


        //the Graph class should have a list of graphnodes  
        //something like private List<GraphNode> nodes;

        private List<GraphNode> nodes = new List<GraphNode>();

        public Graph()
        {
            GraphNode sanfran = new GraphNode("San Francisco", new Point(25, 40));
            GraphNode denver = new GraphNode("Denver", new Point(200, 100));
            GraphNode dallas = new GraphNode("Dallas", new Point(250, 250));
            GraphNode chicago = new GraphNode("Chicago", new Point(300, 60));
            GraphNode newyork = new GraphNode("New York", new Point(450, 100));
            GraphNode losangeles = new GraphNode("Los Angeles", new Point(35, 200));
            GraphNode sandiego = new GraphNode("San Diego", new Point(55, 275));
            GraphNode miami = new GraphNode("Miami", new Point(400, 325));

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

        public List<GraphNode> ShortestPath(GraphNode from, GraphNode to)
        {
            if (Contains(from.Name) && Contains(to.Name))
            {
                foreach (GraphNode g in nodes)
                {
                    if (g.Name == from.Name)
                        from = g;
                    if (g.Name == to.Name)
                        to = g;
                    g.Visited = false;
                }
            }
            else
                return null;

            Queue<GraphNode> q = new Queue<GraphNode>();
            q.Enqueue(from);
            from.distance = 0;
            from.predecessor = null;
            from.Visited = true;
            while (q.Count != 0)
            {
                GraphNode node = q.Dequeue();
                foreach (GraphNode c in node.Neighbors)
                {
                    int i = node.Neighbors.IndexOf(c);
                    if (c.Visited == false)
                    {
                        q.Enqueue(c);
                        c.distance = node.distance + node.Weights[i];
                        c.predecessor = node;
                        c.Visited = true;
                    }
                }
            }
            List<GraphNode> path = new List<GraphNode>();
            GraphNode trace = to;
            while (trace != null && trace.predecessor != null)
            {
                path.Add(trace);
                trace = trace.predecessor;
            }
            path.Add(from);
            path.Reverse();
            return path;
            

        }
        public List<GraphNode> ConnectedComponentsMaker()
        {
            nodes = new List<GraphNode>();

            GraphNode g1 = new GraphNode(1);
            GraphNode g2 = new GraphNode(2);
            GraphNode g3 = new GraphNode(3);
            GraphNode g4 = new GraphNode(4);
            GraphNode g5 = new GraphNode(5);
            GraphNode g6 = new GraphNode(6);
            GraphNode g7 = new GraphNode(7);
            GraphNode g8 = new GraphNode(8);
            GraphNode g9 = new GraphNode(9);
            GraphNode g10 = new GraphNode(10);
            GraphNode g11 = new GraphNode(11);
            GraphNode g12 = new GraphNode(12);
            GraphNode g13 = new GraphNode(13);

            AddNode(g1);
            AddNode(g2);
            AddNode(g3);
            AddNode(g4);
            AddNode(g5);
            AddNode(g6);
            AddNode(g7);
            AddNode(g8);
            AddNode(g9);
            AddNode(g10);
            AddNode(g11);
            AddNode(g12);
            AddNode(g13);


            AddUndirectedEdge(g1, g2, 1);
            AddUndirectedEdge(g2, g1, 1);

            AddUndirectedEdge(g1, g4, 1);
            AddUndirectedEdge(g4, g1, 1);

            AddUndirectedEdge(g2, g4, 1);
            AddUndirectedEdge(g4, g2, 1);

            AddUndirectedEdge(g2, g3, 1);
            AddUndirectedEdge(g3, g2, 1);

            AddUndirectedEdge(g2, g8, 1);
            AddUndirectedEdge(g8, g2, 1);

            AddUndirectedEdge(g3, g9, 1);
            AddUndirectedEdge(g9, g3, 1);

            AddUndirectedEdge(g8, g9, 1);
            AddUndirectedEdge(g9, g8, 1);

            //////

            AddUndirectedEdge(g5, g11, 1);
            AddUndirectedEdge(g11, g5, 1);

            AddUndirectedEdge(g5, g6, 1);
            AddUndirectedEdge(g6, g5, 1);

            AddUndirectedEdge(g6, g11, 1);
            AddUndirectedEdge(g11, g6, 1);

            AddUndirectedEdge(g5, g7, 1);
            AddUndirectedEdge(g7, g5, 1);

            return nodes;
        }

        public void LabelConnectedComponents()
        {
            int comp = 0;
            foreach (GraphNode g in nodes)
            {
                if (g.Visited == false)
                {
                    LCCVisit(g, comp);
                    comp++;
                }
            }
        }
        private void LCCVisit(GraphNode n, int c)
        {
            n.Visited = true;
            n.Component = c;
            foreach (GraphNode neighbor in n.Neighbors)
            {
                if (neighbor.Visited == false)
                    LCCVisit(neighbor, c);
            }
        }
    }
}
