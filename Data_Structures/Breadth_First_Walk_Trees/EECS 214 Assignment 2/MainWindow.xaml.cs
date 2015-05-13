//Assignment 1 for EECS 214
//Out: April 18th, 2014
//Due: April 25th, 2014

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
using Assignment_2.Assignment_2;
using EECS_214_Assignment_2;

namespace Assignment_2
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    ///Don't worry about this being defined as a partial class, a partial class just allows you to split up code in 
    ///different files while telling the compiler to splice them together during compilation
    public partial class MainWindow : Window
    {
        //The top, left and margin variables are used in the
        //drawStructure function. Their only purpose is to specify where to draw
        //the shapes
        int top = 150, left = 160, margin = 10;

        Deque d = new Deque();

        public MainWindow()
        {
            //************************************CODE RELATED TO VISUALIZATION************************************//
          
            //add values to deque object d
            d.Enqueue("Start");
            d.Enqueue(1492);
            d.Enqueue("hello");
            InitializeComponent();

            //This is where we register a "callback". Callbacks are basically functions that take executable
            //code as input. Well, if that sounds like hocus pocus, don't worry about it.
            //there are these things called eventHandlers i.e. functions
            //that are called when an event happens. Such as when you click your mouse, when you drag your mouse etc.
            //Here we are referring to the "click" event on the enqueue and dequeue buttons

            dequeueBtn.Click += dequeueBtn_Click;
            enqueueBtn.Click += enqueueBtn_Click;
            drawStructure();

            //************************************CODE RELATED TO Dynamic Array Based Queue************************************//
            //Declare a dynamic array based queue and do a few Enqueue and Dequeue operations 
            OutputPrint.WriteLine("-------------START DYNAMIC ARRAY------------");

            DynArrayQueue myDynArray = new DynArrayQueue();
            myDynArray.Enqueue("My Dynamic Array");
            myDynArray.print();
            
            OutputPrint.WriteLine("-----------");

            myDynArray.Enqueue(1999);
            myDynArray.print();
            OutputPrint.WriteLine("-----------");

            myDynArray.Enqueue("Hi");
            myDynArray.print();
            OutputPrint.WriteLine("-----------");

            myDynArray.Enqueue("Candy");
            myDynArray.print();
            OutputPrint.WriteLine("-----------");

            myDynArray.Enqueue("Testing for dynamic ability");
            myDynArray.print();
            OutputPrint.WriteLine("-----------");
            
            myDynArray.Dequeue();
            myDynArray.Dequeue();
            myDynArray.print();
            OutputPrint.WriteLine("-----------");

            myDynArray.Enqueue("Recursion");
            myDynArray.print();
            OutputPrint.WriteLine("--------------END DYNAMIC ARRAY--------------\n");
            

            //************************************CODE RELATED TO TREE************************************//
            //Create a tree with at least 5 nodes. Ensure that the tree has at least 3 levels (say 0 1 and 2)
            //Print out a breadth first traversal of the tree
            //If you can hook into the visualizer, that'd be awesome and worth 2% extra credit

            OutputPrint.WriteLine("-------------START TREE--------------");

            //visualization of tree provided below

            TreeNode my_root = new TreeNode("root");

            TreeNode child1 = new TreeNode(1); //will be the children of my_root
            TreeNode child2 = new TreeNode(2);
            ///////////////////////////////
            TreeNode child3 = new TreeNode(3); //will be the children of child1
            TreeNode child4 = new TreeNode(4);
            ///////////////////////////////
            TreeNode child5 = new TreeNode(5); //will be the children of child2
            TreeNode child6 = new TreeNode(6);
            TreeNode child7 = new TreeNode(7);

            TreeNode[] my_root_children = { child1, child2 };
            TreeNode[] child1_children = { child3, child4 };
            TreeNode[] child2_children = { child5, child6, child7 };

            my_root.Children = my_root_children;
            child1.Children = child1_children;
            child1.Parent = my_root;
            child2.Children = child2_children;
            child2.Parent = my_root;

            //This tree will visually look like this
            /*
                              root
                          /         \
                     child1           child2
                    /     \        /     |     \
                child3   child4  child5 child6 child7
            */


            Tree my_tree = new Tree(my_root);
            
            my_tree.BreadthFirst(my_root); //traverse the tree starting from the root
            OutputPrint.WriteLine("--------");
            my_tree.BreadthFirst(child1); //traverse the tree starting from child1
            OutputPrint.WriteLine("--------");
            my_tree.BreadthFirst(child2); //traverse the tree starting from child2

            OutputPrint.WriteLine("------------END TREE-----------\n");

        }

        //Notice when we defined the callback, in lines 53 and 54, we didn't pass any parameters?
        //The system does it for you. It sends a couple of object when you click. An object called sender and event details in 
        //in an object called e

        void enqueueBtn_Click(object sender, RoutedEventArgs e)
        {
            if (input.Text != "")
            {
                d.Enqueue(input.Text);
                drawStructure();
                input.Text = "";
            }
            else
            {
                MessageBoxResult message = MessageBox.Show("Type Value First");
            }
        }

        void dequeueBtn_Click(object sender, RoutedEventArgs e)
        {
            if (!d.IsEmpty)
            {
                d.Dequeue();
                drawStructure();
            }
            else
            {
                MessageBoxResult message = MessageBox.Show("Empty Queue");
            }
        }

        private void drawStructure()
        {
            canvas.Children.Clear(); //You need to call this function to redraw the canvas after each click

            SolidColorBrush rBrush = new SolidColorBrush(Color.FromArgb(90, 101, 135, 178));
            SolidColorBrush rStrBrush = new SolidColorBrush(Color.FromArgb(100, 46, 59, 74));
            SolidColorBrush lBrush = new SolidColorBrush(Color.FromRgb(255, 255, 255));

            //We are drawing a square block for each element in our Stack
            for (int i = 0; i < d.Count; i++)
            {
                //Think about this drawing exercise as your having brushes dipped in different types of paint
                //And you use those brushes to paint a rectangle
                Rectangle r = new Rectangle();
                r.Width = 40;
                r.Height = 40;

                r.Fill = rBrush; //The brush and it's color is defined earlier (Line 82). This is the color inside the rectangle
                r.StrokeThickness = 2; //This defines the thickness of the outline of each rectangular block
                r.Stroke = rStrBrush; //Defines the color of the block

                Label value = new Label();//It's all about objects! A label is an object that can contain text
                value.Width = r.Width;//We have to define how wide the label can go, otherwise the text can overflow from the rectangle
                value.Height = r.Height;
                value.Content = d.Read(i);//Read the i-th element in the stack
                value.FontSize = 12;
                value.Foreground = lBrush; //Again, consider that text is also painted on, the paint color is specified in line 84
                value.HorizontalContentAlignment = HorizontalAlignment.Center; //We are just centering the text horizontally and vertically
                value.VerticalContentAlignment = VerticalAlignment.Center;

                canvas.Children.Add(r); //Add the rectangle 

                Canvas.SetLeft(r, left - i * r.Height + margin);
                Canvas.SetTop(r, top);

                //Add the text. Note, if you've added the text before the rectangle, the text would have
                //been occluded by the rectangle. 
                //So the order of drawing things matter. The things you draw later, are the ones that are layered on top of the previous ones
                canvas.Children.Add(value);
                Canvas.SetTop(value, Canvas.GetTop(r));
                Canvas.SetLeft(value, Canvas.GetLeft(r));
            }

        }

    }
}