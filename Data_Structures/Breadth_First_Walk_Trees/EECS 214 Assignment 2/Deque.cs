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
    /// A double-ended queue
    /// Implement this as a doubly-linked list
    /// </summary>
    public class Deque
    {
        DLLCell front;
        DLLCell back;
        int count = 0;

        public void Enqueue(object o)
        {
            AddEnd(o);
        }
        public object Dequeue()
        {
            object o = RemoveFront();
            return o;
        }

        /// <summary>
        /// Add object to end of queue
        /// </summary>
        /// <param name="o">object to add</param>
        public void AddFront(object o)
        {
            if (o == null)
                throw new NullReferenceException();
            else if (count == 0)
            {
                front = new DLLCell(o);
                back = front;
                back.prev = front;
                front.next = back;
            }
            else
            {
                DLLCell newfront = new DLLCell(o);
                newfront.next = front;
                front = newfront;
            }
            count++;
        }

        /// <summary>
        /// Remove object from beginning of queue.
        /// </summary>
        /// <returns>Object at beginning of queue</returns>
        public object RemoveFront()
        {
            if (IsEmpty)
                throw new QueueEmptyException();
            else
            {
                DLLCell eject = front;
                front = front.next;
                count--;
                return eject;
            }
        }

        /// <summary>
        /// Add object to end of queue
        /// </summary>
        /// <param name="o">object to add</param>
        public void AddEnd(object o)
        {
            if (o == null)
                throw new NullReferenceException();
            else if (count == 0)
            {
                front = new DLLCell(o);
                back = front;
                back.prev = front;
                front.next = back;
                count++;
            }
            else
            {
                DLLCell newback = new DLLCell(o);
                back.next = newback;
                back = newback;
                count++;
            }
        }

        /// <summary>
        /// Remove object from beginning of queue.
        /// </summary>
        /// <returns>Object at beginning of queue</returns>
        public object RemoveEnd()
        {
            if (IsEmpty)
                throw new QueueEmptyException();
            else
            {
                DLLCell eject = back;
                back = back.prev;
                count--;
                return eject;
            }
        }

        /// <summary>
        /// The number of elements in the queue.
        /// </summary>
        public int Count
        {
            get
            {
                return count;
            }
        }

        /// <summary>
        /// True if the queue is empty and dequeuing is forbidden.
        /// </summary>
        public bool IsEmpty
        {
            get
            {
                return (count == 0);
            }
        }

        public object Read(int i)
        {
            DLLCell current = front;
            int j = 0;
            while (current != null && current.next != null)
            {
                if (j == i)
                    return current.obj;
                else
                {
                    current = current.next;
                    j++;
                }
            }
            return current.obj;
        }

        public void print()
        {
            object[] objs = new object[Count];
            DLLCell each = front;
            int i = 0;
            while (each != null && i < Count)
            {
                objs[i] = each.obj;
                each = each.next;
                i++;
            }
            for (int j = 0; j < Count; j++)
            {
                OutputPrint.WriteLine(objs[j]);
            }
        }

        public class DLLCell
        {
            public object obj;
            public DLLCell next;
            public DLLCell prev;

            public DLLCell(object v)
            {
                this.obj = v;
            }
        }

    }
}
