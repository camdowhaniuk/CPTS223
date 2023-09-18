#include "testQueue.h"
#include "queue.h"

using namespace std;

void testSize()
{
    queue q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    if(q.size() == 3)
    {
        cout << "Test case for size() function passed!" << endl;
    }
    else
    {
        cout << "Test case for size() function failed!" << endl;
    }
}

void testIsEmpty()
{
    queue q;

    if(q.isEmpty())
    {
        cout << "Test case for isEmpty() function passed!" << endl;
    }
    else
    {
        cout << "Test case for size() function failed!" << endl;
    }
}

void testIsFull()
{
    queue q;

    for(int i = 0; i < 10; i++)
    {
        q.enqueue(1);
    }

    if(q.isFull())
    {
        cout << "Test case for isFull() function passed!" << endl;
    }
    else
    {
        cout << "Test case for isFull() function failed!" << endl;
    }
}

void testDequeue()
{
    queue q;

    q.enqueue(1);
    q.dequeue();

    if(q.isEmpty())
    {
        cout << "Test case for dequeue() function passed!" << endl;
    }
    else
    {
        cout << "Test case for dequeue() function failed!" << endl;
    }
}

void testEnqueue()
{
    queue q;

    q.enqueue(1);
    if(q.peek() == 1)
    {
        cout << "Test case for enqueue() function passed!" << endl;
    }
    else
    {
        cout << "Test case for enqueue() function failed!" << endl;
    }
}

void testPeek()
{
    queue q;

    q.enqueue(1);
    q.enqueue(2);

    if(q.peek() == 1)
    {
        cout << "Test case for peek() function passed!" << endl;
    }
    else
    {
        cout << "Test case for peek() function failed!" << endl;
    }
}   