using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using OutputPrint = System.Diagnostics.Debug;

namespace Assignment_1
{
    class Program
    {
        static void Main(string[] args)
        {
            
            //Create Queues of both Linked List Queue and Array Queue
            LinkedListQueue myLL = new LinkedListQueue();
            ArrayQueue myAQ = new ArrayQueue();

            OutputPrint.WriteLine("--------ENQUEUE LINKED LIST QUEUE (x3)-----------");

            //Perform at least 3 Enqueue and 2 Dequeue Operations
            myLL.Enqueue("LL Enqueue 1");
            myLL.Enqueue("Hello from Linked List Queue!");
            myLL.Enqueue("Coca Cola");
            myLL.print();

            OutputPrint.WriteLine("-----------ENQUEUE ARRAY QUEUE (x3)---------------");

            myAQ.Enqueue("AQ Enqueue 1");
            myAQ.Enqueue("Hello from Array Queue!");
            myAQ.Enqueue("Boston Red Sox");
            myAQ.print();

            //demonstration of attempting to fill full Array Queue (QueueFullException thrown)
            /*for (int i = 0; i < 100; i++)
            {
                myAQ.Enqueue("Overflow");
            }*/

            OutputPrint.WriteLine("--------DEQUEUE LINKED LIST QUEUE (x2)------------");

            myLL.Dequeue();
            myLL.Dequeue();
            myLL.print();

            OutputPrint.WriteLine("------------DEQUEUE ARRAY QUEUE (x2)-------------");

            myAQ.Dequeue();
            myAQ.Dequeue();
            myAQ.print();

            OutputPrint.WriteLine("-----------ADDFRONT DEQUE QUEUE (x3)---------------");

            //Then declare a deque("DECK") and do a couple of AddFront operations
            Deque myD = new Deque();
            myD.AddFront("D Enqueue 1");
            myD.AddFront("Hello from Deque!");
            myD.AddFront("Pizza");
            myD.print();

            OutputPrint.WriteLine("-----------REMOVEFRONT DEQUE QUEUE---------------");
            //Followed by a RemoveFront operation, then do the same with AddEnd and RemoveEnd
            myD.RemoveFront();
            myD.print();

            OutputPrint.WriteLine("---------------ADDEND DEQUE QUEUE---------------");

            myD.AddEnd("Fusion Dance Co");
            myD.print();

            OutputPrint.WriteLine("------------REMOVEEND DEQUE QUEUE---------------");
            myD.RemoveEnd();
            myD.print();

            OutputPrint.WriteLine("-----------------END PROGRAM------------------");
        }
    }
}
