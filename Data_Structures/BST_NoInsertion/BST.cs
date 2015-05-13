//Assignment 1 for EECS 214
//Out: April 18th, 2014
//Due: April 25th, 2014

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using OutputPrint = System.Diagnostics.Debug;
namespace Assignment_3
{
    //a. Class called BSTNode 
    public class BSTNode
    {
        private int key;
        public BSTNode parent;
        public BSTNode left;
        public BSTNode right;

        public BSTNode(int k)
        {
            key = k;
        }

        public int Key
        {
            get { return key; }
            set { key = value; }
        }
    }

    public class BST 
    {
        int count = 0; //for inorder traversal to initialize BSTArr
        BSTNode root;
        BSTNode[] BSTArr = new BSTNode[9];
        

        //b. A function that builds out the tree given in the instructions PDF file. You can
        //also wrap it in a constructor.

        public BST()
        {
            BSTNode n8 = new BSTNode(8);

            BSTNode n2 = new BSTNode(2);
            BSTNode n9 = new BSTNode(9);

            BSTNode n1 = new BSTNode(1);
            BSTNode n6 = new BSTNode(6);

            BSTNode n4 = new BSTNode(4);
            BSTNode n7 = new BSTNode(7);

            BSTNode n3 = new BSTNode(3);
            BSTNode n5 = new BSTNode(5);

            n8.left = n2;
            n8.right = n9;

            n2.parent = n8;
            n2.left = n1;
            n2.right = n6;

            n9.parent = n8;

            n1.parent = n2;

            n6.parent = n2;
            n6.left = n4;
            n6.right = n7;

            n4.parent = n6;
            n4.left = n3;
            n4.right = n5;

            n7.parent = n6;

            n3.parent = n4;
            n5.parent = n4;

            root = n8;

            Inorder(root);
        }

        public BSTNode Root
        {
            get
            {
                return root;
            }
        }

        //c. A Search function
        public BSTNode Search(BSTNode node, int k)
        {
            while (node != null && node.Key != k)
            {
                if (k < node.Key)
                    node = node.left;
                else
                    node = node.right;
            }
            return node;
        }


        public BSTNode[] Array
        {
            get
            {
                return BSTArr;
            }
        }

        //d. Inorder traversal of the BST
        public void Inorder(BSTNode node)
        {
            
            //while (BSTArr[count] != null)
              //  count++;
            if(node.left != null)
                Inorder(node.left);
            BSTArr[count++] = node;
            if(node.right != null)
                Inorder(node.right);
        }

        //e. Functions for Minimum and Maximum, and Successor
        public BSTNode Minimum(BSTNode n)
        {
            while (n.left != null)
                n = n.left;
            return n;
        }

        public BSTNode Maximum(BSTNode n)
        {
            while (n.right != null)
                n = n.right;
            return n;
        }

        public BSTNode Successor(BSTNode n)
        {
            if (n.right != null)
                return Minimum(n.right);
            BSTNode p = n.parent;
            while (p != null && n == p.right)
            {
                n = p;
                p = n.parent;
            }
            return p;
        }
    }
}
