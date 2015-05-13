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
namespace Assignment_3
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    ///Don't worry about this being defined as a partial class, a partial class just allows you to split up code in 
    ///different files while telling the compiler to splice them together during compilation
    public partial class MainWindow : Window
    {
        int top = 150, margin = 10;

        BST b = new BST();

        public MainWindow()
        {
            InitializeComponent();

            //Registering callbacks for the 3 buttons
            searchBtn.Click += searchBtn_Click;
            maxBtn.Click += maxBtn_Click;
            minBtn.Click += minBtn_Click;
            drawStructure(null);
            //Insert your code here, read the comments in BST.cs for implementation details
            //Things that should work
            //a. When the program runs, draw the tree as an inorder traversal (i.e. sorted list) of boxes horizontally.
            //   That is, exactly similar to the queue visualization you made last time around.
            //b. If I search for a node that doesn't exist in the tree, a Message Box should pop-up saying
            //   that the node was not found
            //c. If I search for a node that does exist in the tree, change its color to highlight where it is
            //   in the sorted list (i.e. horizontal visualization of the inorder traversal of BST)
            //d. If I click the Minimum button, it should hightlight the minimum value and if I click the max.... you get the drift 


        }

        //Search for an element in the BST
        void searchBtn_Click(object sender, RoutedEventArgs e)
        {
            MessageBoxResult message;
            if (input.Text != "")
            {
                BSTNode search = b.Search(b.Root, Convert.ToInt16(input.Text));
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

        //Finds minimum value in BST
        void minBtn_Click(object sender, RoutedEventArgs e)
        {
            BSTNode min = b.Minimum(b.Root);
            drawStructure(min);
        }
        
        //Finds max. value in BST
        void maxBtn_Click(object sender, RoutedEventArgs e)
        {
            BSTNode max = b.Maximum(b.Root);
            drawStructure(max);
        }

        //Draw the inorder traversal (i.e. sorted list) of BST you've defined
        private void drawStructure(BSTNode node)
        {
            canvas.Children.Clear(); //You need to call this function to redraw the canvas after each click

            
            SolidColorBrush rBrush = new SolidColorBrush(Color.FromRgb(10, 150, 230));
            SolidColorBrush rStrBrush = new SolidColorBrush(Color.FromArgb(100, 46, 59, 74));
            SolidColorBrush lBrush = new SolidColorBrush(Color.FromRgb(255, 255, 255));

            SolidColorBrush highlightBrush = new SolidColorBrush(Color.FromRgb(100, 10, 70)); //to hightlight

            for (int i = 0; i < b.Array.Length; i++)
            {
                    
                //Think about this drawing exercise as your having brushes dipped in different types of paint
                //And you use those brushes to paint a rectangle
                Ellipse c = new Ellipse();
                c.Width = 40;
                c.Height = 40;

                if (node != null)
                {
                    if (b.Array[i].Key == node.Key) //highlights the correct node
                        c.Fill = highlightBrush;
                    else
                        c.Fill = rBrush;
                }
                else
                    c.Fill = rBrush;
                 //The brush and it's color is defined earlier (Line 82). This is the color inside the rectangle
                c.StrokeThickness = 2; //This defines the thickness of the outline of each rectangular block
                c.Stroke = rStrBrush; //Defines the color of the block

                Label value = new Label();//It's all about objects! A label is an object that can contain text
                value.Width = c.Width;//We have to define how wide the label can go, otherwise the text can overflow from the rectangle
                value.Height = c.Height;
                value.Content = b.Array[i].Key;
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
