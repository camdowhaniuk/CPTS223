#include <iostream>

using namespace std;

// using template for node struct and List class
template <class C, class D>
struct node
{
    C command;
    D description;
    node<C, D> *next;
};

template <class C, class D>
class List
{
    private:
    node<C, D> *head;
    public:
    List()
    {
        head = nullptr;
    }

    ~List()
    {
        // uses recursion to delete nodes in list from back to front
        destroyList();
    }

    void destroyListHelper(node<C, D> *mem)
    {
        if(mem != nullptr)
        {
            destroyListHelper(mem->next);
            delete mem;
        }
    }

    void destroyList()
    {
        destroyListHelper(head);
    }

    // inserts node at front of list
    void insertFront(C command, D description)
    {
        node<C, D> *temp = new node<C, D>;
        temp->command = command;
        temp->description = description;
        temp->next = head;
        head = temp;
    }

    // deletes node from list given the command from the user
    void deleteNode(C command)
    {
        node<C, D> *prev = nullptr;
        node<C, D> *cur = head;
        if(head != nullptr)
        {
            while (cur != nullptr && cur->command != command) //perform search
            {
                prev = cur;
                cur = cur->next;
            }
            if (cur != nullptr) //if value was found
            {
                if (prev != nullptr) //delete in middle or end
                {
                    //delete
                    prev->next = cur->next;
                    delete cur;
                }
                else //delete front node
                {
                    head = head->next;
                    delete cur;
                }
            }
        }
    }

    // gets size of list
    int getSize()
    {
        node<C, D> *cur = head;
        int size = 0;
        while(cur != nullptr)
        {
            size++;
            cur = cur->next;
        }

        return size;
    }

    // gets head of list
    node<C, D>* getHead()
    {
        return head;
    }
};