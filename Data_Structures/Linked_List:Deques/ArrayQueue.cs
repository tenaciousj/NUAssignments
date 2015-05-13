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
    /// A queue internally implemented as an array
    /// </summary>
    public class ArrayQueue : Queue
    {
        object[] values = new object[100];
        int head = 0;
        int tail = 0;
        int count = 0;


        /// <summary>
        /// Add object to end of queue
        /// </summary>
        /// <param name="o">object to add</param>
        public override void Enqueue(object o)
        {
            if (IsFull)
                throw new QueueFullException();
            else if (o == null)
                throw new NullReferenceException();
            else
            {
                values[tail] = o;
                tail = (tail + 1) % values.Length;
                count++;
            }
        }

        /// <summary>
        /// Remove object from beginning of queue.
        /// </summary>
        /// <returns>Object at beginning of queue</returns>
        public override object Dequeue()
        {
            if (Count == 0)
                throw new QueueEmptyException();
            else
            {
                object item = values[head];
                head = (head + 1) % values.Length;
                count--;
                return item;
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
        /// </summary>
        public override bool IsFull
        {
            get
            {
                return (Count >= values.Length);
            }
        }
        public void print()
        {
            int h = Math.Min(head, tail);
            int t = Math.Max(head, tail);
            for(int i = h; i < t; i++)
            {
                OutputPrint.WriteLine(values[i]);
            }
        }
       
    }
}
