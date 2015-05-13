//Assignment 1 for EECS 211
//Out: April 11th, 2014
//Due: April 18th, 2014
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using OutputPrint = System.Diagnostics.Debug;
namespace Assignment_1
{
    //Again, note how the ArrayQueue implements the Abstract class Queue
    //And how the methods/functions defined in the Queue abstract class
    //Are overriden
    /// <summary>
    /// A queue internally implemented as a linked list of objects
    /// </summary>
    public class LinkedListQueue : Queue
    {
        LLCell top;
        int count = 0;

        /// <summary>
        /// Add object to end of queue
        /// </summary>
        /// <param name="o">object to add</param>
        public override void Enqueue(object o)
        {
            if (o == null)
                throw new NullReferenceException();
            else if (count == 0)
                top = new LLCell(o);
            else
            {
                LLCell x = top;
                while (x != null && x.next != null)
                    x = x.next;
                x.next = new LLCell(o);
            }
            count++;
        }

        /// <summary>
        /// Remove object from beginning of queue.
        /// </summary>
        /// <returns>Object at beginning of queue</returns>
        public override object Dequeue()
        {
            if (IsEmpty)
                throw new QueueEmptyException();
            else
            {
                LLCell eject = top;
                top = top.next;
                count--;
                return eject;
            }
        }

        /// <summary>
        /// The number of elements in the queue.
        /// </summary>
        public override int Count
        {
            get
            {
                return count;
            }
        }

        /// <summary>
        /// True if the queue is full and enqueuing of new elements is forbidden.
        /// Note: LinkedListQueues can be grown to arbitrary length, and so can
        /// never fill.
        /// </summary>
        public override bool IsFull
        {
            get
            {
                return false;
            }
        }

        /// <summary>
        /// True if the queue is empty and dequeuing is forbidden.
        /// </summary>
        public override bool IsEmpty
        {
            get
            {
                return (count == 0);
            }
        }
        public void print()
        {
            object[] objs = new object[Count];
            LLCell each = top;
            for (int i = 0; i < Count; i++)
            {
                objs[i] = each.obj;
                each = each.next;
            }
            for (int j = 0; j < Count; j++)
            {
                OutputPrint.WriteLine(objs[j]);
            }
        }
    }

    public class LLCell
    {
        public object obj;
        public LLCell next;

        public LLCell(object v)
        {
            obj = v;
        }
    }

}
