//Assignment 1 for EECS 214
//Out: April 18th, 2014
//Due: April 25th, 2014
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using OutputPrint = System.Diagnostics.Debug;
namespace Assignment_2
{
    /// <summary>
    /// Write the necessary classes for a tree using arrays
    /// and write a breadth first walk of that tree.
    /// </summary>//Assignment 1 for EECS 214
    //Out: April 18th, 2014
    //Due: April 25th, 2014
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    namespace Assignment_2
    {
        /// <summary>
        /// Write the necessary classes for a tree using arrays
        /// and write a breadth first walk of that tree.
        /// </summary>
        public class Tree
        {
            TreeNode root;

            public Tree(TreeNode r)
            {
                root = r;
            }

            public void BreadthFirst(TreeNode root)
            {
                TreeNode node;
                DynArrayQueue q = new DynArrayQueue();

                q.Enqueue(root);
                OutputPrint.WriteLine(root.Value);
                while (!q.IsEmpty)
                {
                    node = (TreeNode)q.Dequeue();
                    foreach (TreeNode c in node.Children)
                    {
                        if (c == null)
                            break;
                        OutputPrint.WriteLine(c.Value);
                        q.Enqueue(c);
                    }
                }
            }
        }
        public class TreeNode
        {
            TreeNode parent;
            TreeNode[] children = new TreeNode[1];
            object val;

            public TreeNode(object v)
            {
                val = v;
            }
            public TreeNode Parent
            {
                get
                {
                    return parent;
                }
                set
                {
                    parent = value;
                }
            }
            public TreeNode[] Children
            {
                get
                {
                    return children;
                }
                set
                {
                    children = value;
                }
            }
            public object Value
            {
                get
                {
                    return val;
                }
                set
                {
                    val = value;
                }
            }
        }
    }
}
