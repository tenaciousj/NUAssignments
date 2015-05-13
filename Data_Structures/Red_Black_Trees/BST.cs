//Assignment 4 for EECS 214
//Out: May 7th, 2014
//Due: May 16th, 2014

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


//Put everything you wrote from assignment 3 here. But most importantly, have InOrder traversal.
//Make sure you also have:
//a. Class called BSTNode, make it public (and put it outside the BST class, so that the RBNode can derive from the BSTNode class) 
//b. Write left-rotate and right-rotate functions
//c. Write a function for inserting a node in the BST

namespace Assignment_4
{
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
        protected BSTNode root;
        protected List<BSTNode> Arr = new List<BSTNode>();


        public BST() { }

        public BSTNode Root
        {
            get
            {
                return root;
            }
            set
            {
                root = value;
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


        //Inorder traversal of the BST
        public void Inorder(BSTNode node)
        {
            if (node.left != null)
                Inorder(node.left);
            Arr.Add(node);
            if (node.right != null)
                Inorder(node.right);
        }

        //rotate right function
        public void RotateRight(RBTree T, BSTNode b)
        {
            BSTNode a = b.left;
            b.left = a.right;
            if (a.right != null)
                a.right.parent = b;
            a.parent = b.parent;
            if (b.parent == null)
                T.Root = a;
            else if (a.parent.right == b)
                a.parent.right = a;
            else
                a.parent.left = a;
            a.right = b;
            b.parent = a;
        }

        //rotate left function
        public void RotateLeft(RBTree T, BSTNode a)
        {
            BSTNode b = a.right;
            a.right = b.left;
            if (b.left != null)
                b.left.parent = a;
            b.parent = a.parent;
            if (a.parent == null)
                T.Root = b;
            else if (a == a.parent.left)
                a.parent.left = b;
            else
                a.parent.right = b;
            b.left = a;
            a.parent = b;
        }


        public BSTNode FindInsertionPoint(BSTNode n, int k)
        {
            BSTNode parent = null;
            while (n != null && n.Key != -999)
            {
                parent = n;
                if (k < n.Key)
                    n = n.left;
                else
                    n = n.right;

            }
            return parent;
        }

        //insert node function
        public BSTNode Insert(BST tree, BSTNode n)
        {
            BSTNode node = n;
            if (tree.Root == null)
                return node;
            BSTNode parent = FindInsertionPoint(tree.Root, node.Key);
            node.parent = parent;
            if (node.Key < parent.Key)
                parent.left = node;
            else
                parent.right = node;
            return node;
        }

        public List<BSTNode> Array
        {
            get
            {
                return Arr;
            }
        }



        //Functions for Minimum and Maximum, and Successor
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
