//Assignment 5 for EECS 214
//Out: May 16th, 2014
//Due: May 23rd, 2014

using Assignment_4;
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

using OutputPrint = System.Diagnostics.Debug;
namespace Assignment_5
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    ///Don't worry about this being defined as a partial class, a partial class just allows you to split up code in 
    ///different files while telling the compiler to splice them together during compilation
    public partial class MainWindow : Window
    {
        SkipList mySkip = new SkipList(0);

        public SolidColorBrush regularBrush = new SolidColorBrush(Color.FromRgb(120, 200, 100));
        public SolidColorBrush highlightBrush = new SolidColorBrush(Color.FromRgb(50, 0, 90)); //to hightlight
        public SolidColorBrush rStrBrush = new SolidColorBrush(Color.FromArgb(100, 46, 59, 74));
        public SolidColorBrush lBrush = new SolidColorBrush(Color.FromRgb(255, 255, 255));
        public int top = 150, margin = 10;


        public MainWindow()
        {
            InitializeComponent();
            
            //Registering callbacks for the 3 buttons
            searchBtn.Click += searchBtn_Click;
            insertBtn.Click += insertBtn_Click;
            removeBtn.Click += removeBtn_Click;

            Graph myGraph = new Graph();
            Graph.GraphNode g1 = new Graph.GraphNode(1);
            Graph.GraphNode g2 = new Graph.GraphNode(2);
            Graph.GraphNode g3 = new Graph.GraphNode(3);
            Graph.GraphNode g4 = new Graph.GraphNode(4);
            Graph.GraphNode g5 = new Graph.GraphNode(5);
            myGraph.AddNode(g1);
            myGraph.AddNode(g2);
            myGraph.AddNode(g3);
            myGraph.AddNode(g4);
            myGraph.AddNode(g5);
            myGraph.AddDirectedEdge(g1, g2, 5);
            myGraph.AddDirectedEdge(g1, g5, 1);
            myGraph.AddUndirectedEdge(g1, g3, 4);
            myGraph.AddUndirectedEdge(g2, g3, 1);
            myGraph.AddUndirectedEdge(g3, g4, 3);
            myGraph.AddDirectedEdge(g4, g5, 2);
            OutputPrint.WriteLine("------------Neighbors of g1--------------");
            myGraph.printNeighbors(g1);
            OutputPrint.WriteLine("---------Does myGraph contain 6?---------");
            OutputPrint.WriteLine(myGraph.Contains(6));
            OutputPrint.WriteLine("-------How many nodes in myGraph?------");
            OutputPrint.WriteLine(myGraph.Count);
            myGraph.Remove(3);
            OutputPrint.WriteLine("----Neighbors of g1 (with g3 removed)---");
            myGraph.printNeighbors(g1);
            OutputPrint.WriteLine("-----How many nodes in myGraph now?-----");
            OutputPrint.WriteLine(myGraph.Count);
            OutputPrint.WriteLine("----------------------------------------");
            //takes roughly 1 min 30 sec
            for (int num = 1; num < 100000; num++)
            {
                OutputPrint.WriteLine(num);
                mySkip.Insert(num);
            }

            drawStructure(-1);

            OutputPrint.WriteLine("----------------------------");
            OutputPrint.WriteLine("--------Path to Node--------");
            OutputPrint.WriteLine("----------------------------");
            mySkip.printPath(14);
            OutputPrint.WriteLine("----------------------------");
            OutputPrint.WriteLine("--------Path to Node--------");
            OutputPrint.WriteLine("----------------------------");
            mySkip.printPath(35500);

        }

        void removeBtn_Click(object sender, RoutedEventArgs e)
        {
            MessageBoxResult message;

            if (input.Text != "")
            {
                int remove = Convert.ToInt32(input.Text);
                if (mySkip.Contains(remove))
                {
                    mySkip.Remove(remove);
                    drawStructure(-1);
                }
                else
                    message = MessageBox.Show("Value not found");
                input.Text = "";
            }
            else
                message = MessageBox.Show("Type Value First");
        }

        void insertBtn_Click(object sender, RoutedEventArgs e)
        {
            MessageBoxResult message;

            if (input.Text != "")
            {
                int insert = Convert.ToInt32(input.Text);
                if (mySkip.Contains(insert))
                    message = MessageBox.Show("Duplicate Value");
                else
                {
                    mySkip.Insert(insert);
                    drawStructure(-1);
                }
                input.Text = "";
            }
            else
                message = MessageBox.Show("Type Value First");
        }

        //Search for an element in the RBTree
        void searchBtn_Click(object sender, RoutedEventArgs e)
        {
            MessageBoxResult message;

            if (input.Text != "")
            {
                int search = Convert.ToInt32(input.Text);
                if (mySkip.Contains(search))
                {
                    drawStructure(search);
                    int next_node_value = mySkip.NextNode(search);

                    if (next_node_value == -999)
                        message = MessageBox.Show("Next node is null");
                    else
                        message = MessageBox.Show(next_node_value.ToString());
                }
                else
                    message = MessageBox.Show("Search Value not found");
                input.Text = "";
            }
            else
                message = MessageBox.Show("Type Value First");
        }


        //Draw contents of the Skip List
        private void drawStructure(int val)
        {
            canvas.Children.Clear();
            for (int i = 0; i < mySkip.Nodes.Count; i++)
            {
                Ellipse c = new Ellipse();
                c.Width = 40;
                c.Height = 40;

                if (val != -1)
                {
                    if (mySkip.Nodes[i] == val)
                        c.Fill = highlightBrush;
                    else
                        c.Fill = regularBrush;
                }
                else
                    c.Fill = regularBrush;


                //The brush and it's color is defined earlier (Line 82). This is the color inside the rectangle
                c.StrokeThickness = 2; //This defines the thickness of the outline of each rectangular block
                c.Stroke = rStrBrush; //Defines the color of the block

                Label value = new Label();//It's all about objects! A label is an object that can contain text
                value.Width = c.Width;//We have to define how wide the label can go, otherwise the text can overflow from the rectangle
                value.Height = c.Height;
                value.Content = mySkip.Nodes[i];

                value.FontSize = 12;
                value.Foreground = lBrush; //Again, consider that text is also painted on, the paint color is specified in line 84
                value.HorizontalContentAlignment = HorizontalAlignment.Center; //We are just centering the text horizontally and vertically
                value.VerticalContentAlignment = VerticalAlignment.Center;

                canvas.Children.Add(c); //Add the rectangle 

                Canvas.SetLeft(c, i * c.Height - margin);
                Canvas.SetTop(c, top);

                //Add the text. Note, if you've added the text before the rectangle, the text would have
                //been occluded by the rectangle. 
                //So the order of drawing things matter. The things you draw later, are the ones that are layered on top of the previous ones
                canvas.Children.Add(value);
                Canvas.SetTop(value, Canvas.GetTop(c));
                Canvas.SetLeft(value, Canvas.GetLeft(c));

            }
        }
    }
}
