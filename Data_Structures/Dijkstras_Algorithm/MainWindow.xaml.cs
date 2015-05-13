//Assignment 7 for EECS 214
//Out: May 30rd, 2014
//Due: June 6th, 2014
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Assignment_7
{
    /// <summary>
    /// THIS SHOULD REMAIN VERY SIMILAR TO ASSIGNMENT 6, INSTEAD OF CALLING BFS for SHORTEST PATH, CALL DIJKSTRA's 
    /// ALGORITHM 
    /// </summary>
    ///Don't worry about this being defined as a partial class, a partial class just allows you to split up code in 
    ///different files while telling the compiler to splice them together during compilation
    public partial class MainWindow : Window
    {
        List<Graph.GraphNode> nil = new List<Graph.GraphNode>();
        Graph myGraph = new Graph(); //for ShortestPath


        public MainWindow()
        {
            InitializeComponent();

            //Registering callback for the route finding button
            searchRouteBtn.Click += searchRouteBtn_Click;
            drawStructure(nil);
        }

        void searchRouteBtn_Click(object sender, RoutedEventArgs e)
        {
            //Get the to and from airports from the fromInput and toInput textboxes in MainWindow.xaml.cs
            //Find the cheapest flight path and draw it using drawstructure
            
            //CALL DijkstraShortestPath(fromNode, toNode);
            //Follow it up with a call to drawstructure to highlight the paths
            MessageBoxResult message;

            if (fromInput.Text != "" && toInput.Text != "")
            {
                Graph.GraphNode from = new Graph.GraphNode(fromInput.Text);
                Graph.GraphNode to = new Graph.GraphNode(toInput.Text);
                List<Graph.GraphNode> path = myGraph.DijkstraShortestPath(from, to);
                drawStructure(path);
            }
            else
                message = MessageBox.Show("Type Airport names first");
 
        }


        //ALL YOUR OLD DRAWSTRUCTURE CODE
        private void drawStructure(List<Graph.GraphNode> path)
        {
            canvas.Children.Clear();

            SolidColorBrush highlightBrush = new SolidColorBrush(Color.FromRgb(200, 0, 0));
            SolidColorBrush highlightStrokeBrush = new SolidColorBrush(Color.FromRgb(200, 0, 0));

            //Connector from Denver to SanFran
            Line c1 = new Line();
            c1.X1 = myGraph.Nodes[0].Pos.X + 30 / 2; //30 is the width of the circle/node drawn
            c1.Y1 = myGraph.Nodes[0].Pos.Y + 30 / 2; //30 is the height of the circle/node drawn;
            c1.X2 = myGraph.Nodes[1].Pos.X + 30 / 2;
            c1.Y2 = myGraph.Nodes[1].Pos.Y + 30 / 2;
            c1.StrokeThickness = 2;
            if (path.Contains(myGraph.Nodes[0]) && path.Contains(myGraph.Nodes[1]))
                c1.Stroke = highlightStrokeBrush;
            else
                c1.Stroke = new SolidColorBrush(Color.FromRgb(150, 150, 175));
            canvas.Children.Add(c1);

            //Connector from SanFran to Los Angeles
            Line c2 = new Line();
            c2.X1 = myGraph.Nodes[0].Pos.X + 30 / 2; //30 is the width of the circle/node drawn
            c2.Y1 = myGraph.Nodes[0].Pos.Y + 30 / 2; //30 is the height of the circle/node drawn;
            c2.X2 = myGraph.Nodes[5].Pos.X + 30 / 2;
            c2.Y2 = myGraph.Nodes[5].Pos.Y + 30 / 2;
            c2.StrokeThickness = 2;
            if (path.Contains(myGraph.Nodes[0]) && path.Contains(myGraph.Nodes[5]))
                c2.Stroke = highlightStrokeBrush;
            else
                c2.Stroke = new SolidColorBrush(Color.FromRgb(150, 150, 175));
            canvas.Children.Add(c2);

            //Connector from Los Angeles to San Diego
            Line c3 = new Line();
            c3.X1 = myGraph.Nodes[5].Pos.X + 30 / 2; //30 is the width of the circle/node drawn
            c3.Y1 = myGraph.Nodes[5].Pos.Y + 30 / 2; //30 is the height of the circle/node drawn;
            c3.X2 = myGraph.Nodes[6].Pos.X + 30 / 2;
            c3.Y2 = myGraph.Nodes[6].Pos.Y + 30 / 2;
            c3.StrokeThickness = 2;
            if (path.Contains(myGraph.Nodes[5]) && path.Contains(myGraph.Nodes[6]))
                c3.Stroke = highlightStrokeBrush;
            else
                c3.Stroke = new SolidColorBrush(Color.FromRgb(150, 150, 175));
            canvas.Children.Add(c3);

            //Connector from Denver to Los Angeles
            Line c4 = new Line();
            c4.X1 = myGraph.Nodes[1].Pos.X + 30 / 2; //30 is the width of the circle/node drawn
            c4.Y1 = myGraph.Nodes[1].Pos.Y + 30 / 2; //30 is the height of the circle/node drawn;
            c4.X2 = myGraph.Nodes[5].Pos.X + 30 / 2;
            c4.Y2 = myGraph.Nodes[5].Pos.Y + 30 / 2;
            c4.StrokeThickness = 2;
            if (path.Contains(myGraph.Nodes[1]) && path.Contains(myGraph.Nodes[5]))
                c4.Stroke = highlightStrokeBrush;
            else
                c4.Stroke = new SolidColorBrush(Color.FromRgb(150, 150, 175));
            canvas.Children.Add(c4);

            //Connector from Chicago to Denver
            Line c5 = new Line();
            c5.X1 = myGraph.Nodes[3].Pos.X + 30 / 2; //30 is the width of the circle/node drawn
            c5.Y1 = myGraph.Nodes[3].Pos.Y + 30 / 2; //30 is the height of the circle/node drawn;
            c5.X2 = myGraph.Nodes[1].Pos.X + 30 / 2;
            c5.Y2 = myGraph.Nodes[1].Pos.Y + 30 / 2;
            c5.StrokeThickness = 2;
            if (path.Contains(myGraph.Nodes[3]) && path.Contains(myGraph.Nodes[1]))
                c5.Stroke = highlightStrokeBrush;
            else
                c5.Stroke = new SolidColorBrush(Color.FromRgb(150, 150, 175));
            canvas.Children.Add(c5);

            //Connector from New York to Denver
            Line c6 = new Line();
            c6.X1 = myGraph.Nodes[4].Pos.X + 30 / 2; //30 is the width of the circle/node drawn
            c6.Y1 = myGraph.Nodes[4].Pos.Y + 30 / 2; //30 is the height of the circle/node drawn;
            c6.X2 = myGraph.Nodes[1].Pos.X + 30 / 2;
            c6.Y2 = myGraph.Nodes[1].Pos.Y + 30 / 2;
            c6.StrokeThickness = 2;
            if (path.Contains(myGraph.Nodes[4]) && path.Contains(myGraph.Nodes[1]))
                c6.Stroke = highlightStrokeBrush;
            else
                c6.Stroke = new SolidColorBrush(Color.FromRgb(150, 150, 175));
            canvas.Children.Add(c6);

            //Connector from New York to Chicago
            Line c7 = new Line();
            c7.X1 = myGraph.Nodes[4].Pos.X + 30 / 2; //30 is the width of the circle/node drawn
            c7.Y1 = myGraph.Nodes[4].Pos.Y + 30 / 2; //30 is the height of the circle/node drawn;
            c7.X2 = myGraph.Nodes[3].Pos.X + 30 / 2;
            c7.Y2 = myGraph.Nodes[3].Pos.Y + 30 / 2;
            c7.StrokeThickness = 2;
            if (path.Contains(myGraph.Nodes[4]) && path.Contains(myGraph.Nodes[3]))
                c7.Stroke = highlightStrokeBrush;
            else
                c7.Stroke = new SolidColorBrush(Color.FromRgb(150, 150, 175));
            canvas.Children.Add(c7);

            //Connector from New York to Miami
            Line c8 = new Line();
            c8.X1 = myGraph.Nodes[4].Pos.X + 30 / 2; //30 is the width of the circle/node drawn
            c8.Y1 = myGraph.Nodes[4].Pos.Y + 30 / 2; //30 is the height of the circle/node drawn;
            c8.X2 = myGraph.Nodes[7].Pos.X + 30 / 2;
            c8.Y2 = myGraph.Nodes[7].Pos.Y + 30 / 2;
            c8.StrokeThickness = 2;
            if (path.Contains(myGraph.Nodes[4]) && path.Contains(myGraph.Nodes[7]))
                c8.Stroke = highlightStrokeBrush;
            else
                c8.Stroke = new SolidColorBrush(Color.FromRgb(150, 150, 175));
            canvas.Children.Add(c8);

            //Connector from San Diego to Dallas
            Line c9 = new Line();
            c9.X1 = myGraph.Nodes[6].Pos.X + 30 / 2; //30 is the width of the circle/node drawn
            c9.Y1 = myGraph.Nodes[6].Pos.Y + 30 / 2; //30 is the height of the circle/node drawn;
            c9.X2 = myGraph.Nodes[2].Pos.X + 30 / 2;
            c9.Y2 = myGraph.Nodes[2].Pos.Y + 30 / 2;
            c9.StrokeThickness = 2;
            if (path.Contains(myGraph.Nodes[6]) && path.Contains(myGraph.Nodes[2]))
                c9.Stroke = highlightStrokeBrush;
            else
                c9.Stroke = new SolidColorBrush(Color.FromRgb(150, 150, 175));
            canvas.Children.Add(c9);

            //Connector from Dallas to Los Angeles
            Line c10 = new Line();
            c10.X1 = myGraph.Nodes[2].Pos.X + 30 / 2; //30 is the width of the circle/node drawn
            c10.Y1 = myGraph.Nodes[2].Pos.Y + 30 / 2; //30 is the height of the circle/node drawn;
            c10.X2 = myGraph.Nodes[5].Pos.X + 30 / 2;
            c10.Y2 = myGraph.Nodes[5].Pos.Y + 30 / 2;
            c10.StrokeThickness = 2;
            if (path.Contains(myGraph.Nodes[2]) && path.Contains(myGraph.Nodes[5]))
                c10.Stroke = highlightStrokeBrush;
            else
                c10.Stroke = new SolidColorBrush(Color.FromRgb(150, 150, 175));
            canvas.Children.Add(c10);

            //Connector from New York to Dallas
            Line c11 = new Line();
            c11.X1 = myGraph.Nodes[4].Pos.X + 30 / 2; //30 is the width of the circle/node drawn
            c11.Y1 = myGraph.Nodes[4].Pos.Y + 30 / 2; //30 is the height of the circle/node drawn;
            c11.X2 = myGraph.Nodes[2].Pos.X + 30 / 2;
            c11.Y2 = myGraph.Nodes[2].Pos.Y + 30 / 2;
            c11.StrokeThickness = 2;
            if (path.Contains(myGraph.Nodes[4]) && path.Contains(myGraph.Nodes[2]))
                c11.Stroke = highlightStrokeBrush;
            else
                c11.Stroke = new SolidColorBrush(Color.FromRgb(150, 150, 175));
            canvas.Children.Add(c11);

            //Connector from Dallas to Miami
            Line c12 = new Line();
            c12.X1 = myGraph.Nodes[2].Pos.X + 30 / 2; //30 is the width of the circle/node drawn
            c12.Y1 = myGraph.Nodes[2].Pos.Y + 30 / 2; //30 is the height of the circle/node drawn;
            c12.X2 = myGraph.Nodes[7].Pos.X + 30 / 2;
            c12.Y2 = myGraph.Nodes[7].Pos.Y + 30 / 2;
            c12.StrokeThickness = 2;
            if (path.Contains(myGraph.Nodes[2]) && path.Contains(myGraph.Nodes[7]))
                c12.Stroke = highlightStrokeBrush;
            else
                c12.Stroke = new SolidColorBrush(Color.FromRgb(150, 150, 175));
            canvas.Children.Add(c12);

            //Connector from Denver to SanFran
            Line c13 = new Line();
            c13.X1 = myGraph.Nodes[0].Pos.X + 30 / 2; //30 is the width of the circle/node drawn
            c13.Y1 = myGraph.Nodes[0].Pos.Y + 30 / 2; //30 is the height of the circle/node drawn;
            c13.X2 = myGraph.Nodes[3].Pos.X + 30 / 2;
            c13.Y2 = myGraph.Nodes[3].Pos.Y + 30 / 2;
            c13.StrokeThickness = 2;
            if (path.Contains(myGraph.Nodes[0]) && path.Contains(myGraph.Nodes[3]))
                c13.Stroke = highlightStrokeBrush;
            else
                c13.Stroke = new SolidColorBrush(Color.FromRgb(150, 150, 175));
            canvas.Children.Add(c13);

            //Feel free to use whatever colours you want
            //I've iterated through the position and name lists here just to give an example
            //you'll iterate through the graphnodes in your graph
            int counter = 0;


            foreach (Graph.GraphNode g in myGraph.Nodes)
            {
                Ellipse e = new Ellipse();
                e.Height = 30;
                e.Width = 30;
                if (path.Contains(g))
                    e.Fill = highlightBrush;
                else
                    e.Fill = new SolidColorBrush(Color.FromRgb(255, 190, 175));
                e.StrokeThickness = 3;
                e.Stroke = new SolidColorBrush(Color.FromRgb(175, 175, 175));
                Canvas.SetLeft(e, g.Pos.X);
                Canvas.SetTop(e, g.Pos.Y);
                canvas.Children.Add(e);

                Label l = new Label();
                l.Content = myGraph.Nodes[counter].Name;
                Canvas.SetLeft(l, g.Pos.X - 5);
                Canvas.SetTop(l, g.Pos.Y - 20);

                canvas.Children.Add(l);
                counter++;
            }

        }

    }
}
