//Assignment 1 for EECS 214
//Out: April 18th, 2014
//Due: April 25th, 2014

using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using OutputPrint = System.Diagnostics.Debug;
namespace Assignment_2
{
    //Again, note how the ArrayQueue implements the Abstract class Queue
    //And how the methods/functions defined in the Queue abstract class
    //Are overriden
    /// <summary>
    /// A queue internally implemented as an array
    /// </summary>
    public class DynArrayQueue : Queue, IEnumerable
    {
        object[] values = new object[0];
        int count = 0;

        IEnumerator IEnumerable.GetEnumerator()
        {
            for (int i = 0; i < values.Length; i++)
                yield return values[i];
        }

        public object this[int index]
        {
            get
            {
                return values[index];
            }
            set
            {
                values[index] = value;
            }
        }
        /// <summary>
        /// Add object to end of queue
        /// </summary>
        /// <param name="o">object to add</param>
        public override void Enqueue(object o)
        {
            if (o == null)
                throw new NullReferenceException();
            else
            {
                object[] newArray = new object[values.Length + 1];
                for (int i = 0; i < values.Length; i++)
                    newArray[i] = values[i];
                newArray[values.Length] = o;
                values = newArray;
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
                object eject = values[0];
                object[] newArray = new object[values.Length - 1];
                for (int i = 1; i < values.Length; i++)
                    newArray[i-1] = values[i];
                values = newArray;
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
        /// </summary>
        public override bool IsFull
        {
            get
            {
                return false;
            }
        }

        public void print()
        {
            for (int i = 0; i < values.Length; i++)
            {
                OutputPrint.WriteLine(values[i]);
            }
        }
        
    }
}
