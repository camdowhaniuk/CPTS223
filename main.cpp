#include "AVLTree.h"

// function shuffles an array of size 50
void shuffle(int array[])
{
    int temp = 0;
    int random = 0;

    for(int i = 0; i < 50; i++)
    {
        random = rand() % 50;
        temp = array[i];
        array[i] = array[random];
        array[random] = temp;
    }
}

int main() 
{
    srand(time(0));
    // 3 arrays declared for different data sequences
    int ascOrder[100], decOrder[100], randOrder[100], x = 0;
 
    for(int i = 1; i < 101; i++)
    {
        if(i % 2 != 0) 
        {
            // populate arrays with odd numbers in ascending order
            ascOrder[x] = i;
            randOrder[x] = i; 
            x++;
        }
    }

    // shuffle array
    shuffle(randOrder);
    
    x = 0;

    for(int i = 100; i > 0; i--)
    {
        if(i % 2 != 0) 
        {
            // populate arrays with odd numbers in descending order
            decOrder[x] = i; 
            x++;
        }
    }

    // three AVL trees initialized 
    AVLTree<int> tree1, tree2, tree3;

    for(int i = 0; i < 50; i++)
    {
        // 1. insert different sequences into three trees
        tree1.insert(tree1.root, ascOrder[i]);

        tree2.insert(tree2.root, decOrder[i]);

        tree3.insert(tree3.root, randOrder[i]);
    }

    // 2. print the height of each AVL tree 
    cout << "Height of tree1: " << tree1.getHeight() << endl << "Height of tree2: " << tree2.getHeight() << endl << "Height of tree3: " << tree3.getHeight() << endl;

    // 3. print result of validate of each tree
    cout << "Validate of tree1: " << tree1.validate() << endl << "Validate of tree2: " << tree2.validate() << endl << "Validate of tree3: " << tree3.validate() << endl;

    // loop through and call contains to check if any even numbers are in the trees
    for(int i = 1; i < 101; i++)
    {
        if(i % 2 == 0)
        {
            if(tree1.contains(i) || tree2.contains(i) || tree3.contains(i))
            {
                // if they are print tree implementation is wrong
                cout << "My AVL tree implementation is wrong." << endl;
            }
        }
    }

    


    return 0;
}
