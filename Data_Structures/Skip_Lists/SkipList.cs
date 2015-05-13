//Assignment 4 for EECS 214
//Out: May 7th, 2014
//Due: May 16th, 2014

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using OutputPrint = System.Diagnostics.Debug;
namespace Assignment_5
{
    class SkipList
    {
        //The Node class should have an integer value and a Node[]
        //of size specified as an input (i.e. a constructor that takes a value and a size/number of levels
        //as an input. Call this array of SkipNode(i.e. SkipNode[]) Next. This array would contain the "next" nodes of a particular node
        //Refer to slide number 17 of Skip Lists on Piazza for what we mean by size
        public class SkipNode
        {
            private int value;
            public SkipNode[] Next;

            public SkipNode(int first_value, int size)
            {
                value = first_value;
                Next = new SkipNode[size];
            }
            public int Val
            {
                get { return value; }
            }
        }
        //Fields of the SkipList class. Should have the starting node, since it is a linked list
        //call it head, should have levels and a random number generator (C# has a class called Random!)
        //private Node head = new Node(0, 20); // Set the max. size to 20 and the first value to be 0
        //private int levels = 1;
        //private Random randNum = new Random();

        private SkipNode head;
        private int levels;
        private Random randNum;

        private List<int> nodes = new List<int>();

        private double prob = 0.75;
        private int max = 20;

        private int count;

        public SkipList(int head_val)
        {
            head = new SkipNode(head_val, max);
            levels = 1;
            randNum = new Random();
            count = 1; //head is already inserted
            nodes.Add(head.Val);
        }

        public List<int> Nodes
        {
            get
            {
                nodes.Sort();
                return nodes;
            }
        }

        public SkipNode Start
        {
            get { return head; }
        }
        public SkipNode[] Next_List
        {
            get { return head.Next; }
        }
        public int Levels
        {
            get { return levels; }
        }
        public int Count
        {
            get { return count; }
        }
        /// <summary>
        /// Inserts a value into the skip list.
        /// </summary>
        public void Insert(int value)
        {
            // Determine the level of a new node. Generate a random number R by calling ChooseRandLevel() function
            // Use the setLevel algorithm we discuss in Slide 19 of Skip Lists
            // Insert this node into the skip list(remember skips lists are sorted)
            // And since this is a linked list, remember that you need to start at the head node


            int lev = ChooseRandLevel();
            SkipNode insert = new SkipNode(value, lev + 1);
            
            if (count < max)
                nodes.Add(insert.Val);

            SkipNode current = head;
            for (int i = max - 1; i >= 0; i--)
            {
                while (current.Next[i] != null)
                {
                    if (current.Next[i].Val > value)
                        break;
                    current = current.Next[i];
                }
                if (i <= lev)
                {
                    insert.Next[i] = current.Next[i];
                    current.Next[i] = insert;
                }
            }
            count++;
        }



        /// <summary>
        /// Checks if a value already exists in the  list
        /// </summary>
        public bool Contains(int value)
        {
            if (head.Val == value)
                return true;

            SkipNode current = head;
            for (int i = max - 1; i >= 0; i--)
            {
                while (current.Next[i] != null)
                {
                    if (current.Next[i].Val > value)
                        break;
                    else if (current.Next[i].Val == value)
                        return true;
                    current = current.Next[i];
                }
            }
            return false;
        }

        /// <summary>
        /// Removes a node with an input value from the skip list. 
        /// </summary>
        public void Remove(int value)
        {
            SkipNode current = head;
            for (int i = max - 1; i >= 0; i--)
            {
                while (current.Next[i] != null)
                {
                    if (current.Next[i].Val == value)
                    {
                        current.Next[i] = current.Next[i].Next[i];
                        break;
                    }
                    if (current.Next[i].Val > value)
                        break;
                    current = current.Next[i];
                }
            }
            nodes.Remove(value);
            if (count != 0)
                count--;
            
        }

        /// <summary>
        /// generate a random number using the Random class
        /// </summary>
        public int ChooseRandLevel()
        {
            int level = 0;
            while (randNum.Next(0, 10) < prob*10)
                level++;
            if (level > max)
                return max;
            else
                return level;
        }

        /// <summary>
        /// Enabling an iterator so that we can iterate using a foreach loop
        /// </summary>
        public IEnumerable<int> Enumerate()
        {
            SkipNode current = head.Next[0];
            while (current != null)
            {
                yield return current.Val;
                current = current.Next[0];
            }
        }

        //ALSO WRITE A FUNCTION OR PROPERTY THAT RETURNS THE NEXT NODE OF AN INPUT NODE
        //THAT'S THE VALUE THAT SHOWS UP IN A MESSAGEBOX ON SEARCHING FOR A VALUE
        public int NextNode(int n)
        {
            if (n == head.Val)
            {
                if (head.Next[0] == null)
                    return -999;
                return head.Next[0].Val;
            }
                
            if (Contains(n))
            {
                SkipNode current = head;
                for (int i = 0; i < current.Next.Length; i++)
                {
                    while (current.Next[i] != null)
                    {
                        if (current.Next[i].Val == n)
                        {
                            if (current.Next[i].Next[i] == null)
                                return -999;
                            return current.Next[i].Next[i].Val;
                        }
                        current = current.Next[i];
                    }
                }
            }
            return -999;
        }

        public void printPath(int value)
        {
            SkipNode current = head;
            OutputPrint.WriteLine("Value: " + current.Val + " Level: " + current.Next.Length);
            for (int i = max - 1; i >= 0; i--)
            {
                while (current.Next[i] != null)
                {
                    if (current.Next[i].Val > value)
                        break;
                    if (current.Next[i].Val == value)
                    {
                        OutputPrint.WriteLine("Value Found!: " + current.Next[i].Val + " Level: " + current.Next.Length);
                        return;
                    }
                    current = current.Next[i];
                    OutputPrint.WriteLine("Value: " + current.Val + " Level: " + current.Next.Length);
                }
            }
        }
        
    }
}
