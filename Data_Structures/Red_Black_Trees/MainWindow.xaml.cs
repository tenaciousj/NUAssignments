//Assignment 4 for EECS 214
//Out: May 7th, 2014
//Due: May 16th, 2014

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

namespace Assignment_4
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    ///Don't worry about this being defined as a partial class, a partial class just allows you to split up code in 
    ///different files while telling the compiler to splice them together during compilation
    public partial class MainWindow : Window
    {
        int top = 150, margin = 10;
        public Color black = Color.FromArgb(90, 11, 32, 56);
        public Color red = Color.FromArgb(90, 201, 56, 76);
        public SolidColorBrush lBrush = new SolidColorBrush(Color.FromRgb(255, 255, 255));

        //RBTree myRBTree = new RBTree();
        RBTree myRBTree = new RBTree("test tree");
        

        public MainWindow()
        {
            
            InitializeComponent();
            
            //Registering callbacks for the 3 buttons
            searchBtn.Click += searchBtn_Click;
            insertBtn.Click += insertBtn_Click;
            bhBtn.Click +=bhBtn_Click;



            drawStructure(null);
            //Insert your code here, read the comments in BST.cs for implementation details
            //Things that should work
            //a. When the program runs, draw the tree as an inorder traversal (i.e. sorted list) of boxes horizontally. 
            //   Same as assignment 3
            //b. If I search for a node that doesn't exist in the tree, a Message Box should pop-up saying
            //   that the node was not found
            //c. If I search for a node that DOES exist in the tree, change its stroke color to highlight where it is
            //   in the sorted list (i.e. horizontal visualization of the inorder traversal of the RBT).
            //   N.B. don't change the colour of the fill(should be red or black), only change the outlines to highlight
            //d. Clicking on the insert button should insert the value/key in the input box. Do proper validation (numbers only, empty box etc.)
            //e. RECOMMENDATION: Use the red and black colors defined in the drawstructure function for the red and black nodes,
            //   While we encourage creative freedom, grading this assignment would kill me and Aleck if we
            //   see different shades of red and black from all of you :).

        }

        void bhBtn_Click(object sender, RoutedEventArgs e)
        {
            RBNode black_height = (RBNode)myRBTree.Search(myRBTree.Root, Convert.ToInt16(input.Text));
            myRBTree.BlackHeight(myRBTree, black_height);
        }

        void insertBtn_Click(object sender, RoutedEventArgs e)
        {
            MessageBoxResult message;
            if (input.Text != "")
            {
                RBNode insert = new RBNode(Convert.ToInt16(input.Text), red);
                myRBTree.Insert(myRBTree, insert);
                drawStructure(null);
                input.Text = "";
            }
            else
            {
                message = MessageBox.Show("Type Value First");
            }
        }

        //Search for an element in the RBTree
        void searchBtn_Click(object sender, RoutedEventArgs e)
        {
            MessageBoxResult message;
            if (input.Text != "")
            {
                RBNode search = (RBNode)myRBTree.Search(myRBTree.Root, Convert.ToInt16(input.Text));
                if (search == null)
                    message = MessageBox.Show("Search key not found");
                else
                    drawStructure(search);
                input.Text = "";
            }
            else
            {
                message = MessageBox.Show("Type Value First");
            }
        }


        //Draw the inorder traversal (i.e. sorted list) of BST you've defined
        //Parameterize it if necessary
        private void drawStructure(RBNode node)
        {
            canvas.Children.Clear();

            //Brush for Red nodes
            SolidColorBrush redBrush = new SolidColorBrush(red);
            //Brush for Black nodes
            SolidColorBrush blackBrush = new SolidColorBrush(black);


            SolidColorBrush highlightBrush = new SolidColorBrush(Color.FromRgb(50, 200, 90)); //to hightlight
            SolidColorBrush rStrBrush = new SolidColorBrush(Color.FromArgb(100, 46, 59, 74));

            for (int i = 0; i < myRBTree.RBArr.Count; i++)
            {

                SolidColorBrush node_color_brush = new SolidColorBrush(myRBTree.RBArr[i].Color);

                //Think about this drawing exercise as your having brushes dipped in different types of paint
                //And you use those brushes to paint a rectangle
                Ellipse c = new Ellipse();
                c.Width = 40;
                c.Height = 40;

                if (node != null)
                {
                    if (myRBTree.RBArr[i].Key == node.Key) //highlights the correct node
                        c.Fill = highlightBrush;
                    else
                        c.Fill = node_color_brush;
                }
                else
                    c.Fill = node_color_brush;


                //The brush and it's color is defined earlier (Line 82). This is the color inside the rectangle
                c.StrokeThickness = 2; //This defines the thickness of the outline of each rectangular block
                c.Stroke = rStrBrush; //Defines the color of the block

                Label value = new Label();//It's all about objects! A label is an object that can contain text
                value.Width = c.Width;//We have to define how wide the label can go, otherwise the text can overflow from the rectangle
                value.Height = c.Height;
                value.Content = myRBTree.RBArr[i].Key;
                value.FontSize = 12;
                value.Foreground = lBrush; //Again, consider that text is also painted on, the paint color is specified in line 84
                value.HorizontalContentAlignment = HorizontalAlignment.Center; //We are just centering the text horizontally and vertically
                value.VerticalContentAlignment = VerticalAlignment.Center;

                canvas.Children.Add(c); //Add the rectangle 

                Canvas.SetLeft(c, i * c.Height + margin);
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
