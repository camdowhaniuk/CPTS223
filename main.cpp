// This code was taken from https://www.techiedelight.com/queue-implementation-cpp/
// The code has been modified from the original to provide opportunities to learn

/*  5.
    (1) One problem I found with the destructor was that it uses 'delete' instead of 'delete[]'. You would need to use delete[] because the array for queue was dynamicaaally allocated using 'new[]'.
    (2) Another issue would be inadequate error handling. It would be more efficent to use exceptions.
    (3) There could also be more comments explaing the logic of each function.
    (4) There was also no constructor for a queue initalizing the other elements of a queue. This could lead to issues.
    (5) Finally, the dequeue function is inefficient because it shifts the front pointer, but doesn't free the memory. 
*/

#include "testQueue.h"

// main function
int main()
{
    // call your test functions here!

    testSize();

    testIsEmpty();

    testIsFull();

    testDequeue();

    testEnqueue();

    testPeek();
    return 0;
}

