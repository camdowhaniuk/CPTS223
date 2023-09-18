/*
ADVANTAGES/DISADVANTAGES LINKED LIST:
Advantage: Linked lists have dynamic size which makes it efficient for insertion and deletion
Disadvantage: Linked lists store a lot of extra memory for pointers, which could add up if the commands.csv was larger


ADVANTAGES/DISADVANTAGES ARRAY:
Advantage: Arrays are static size therefore there's no need for dynamic memory allocation or deallocation
Disadvantage: Inserting elements to the front of an array is far less effecient than inserting at the front of a linked list because you need to move all of the elements in the array over one index. 
*/

#include "PA1.h"

int main()
{
    srand((unsigned) time(NULL));
    List<string, string> list;
    profile profiles[100];
    // initialize profile array to initial values
    for(int i = 0; i < 100; i ++)
    {
        profiles[i].name = "";
        profiles[i].points = 0;
    }
    // load list from commands.csv file
    loadList(list);
    // load profiles array from profiles.csv
    loadArray(profiles);
    // display menu
    displayMenu(list, profiles);

    return 0;
}