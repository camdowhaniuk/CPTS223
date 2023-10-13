#ifndef AVLTREE_H
#define AVLTREE_H
#include "AVLNode.h"

template <typename T>
class AVLTree 
{
public:
    AVLNode<T>* root;

    // constructor and destructor 
    AVLTree() : root(nullptr) {}
    ~AVLTree() 
    {
        destroyTree(root); // starts recursive call
    }

    // function that gets height of tree
    int getHeight() 
    {
        return (root == nullptr) ? 0 : root->height;
    }

    // function rotates left child
    void rotateLeftChild(AVLNode<T> *&n2)
    {
        AVLNode<T> *n1 = n2->left;
        n2->left = n1->right;
        n1->right = n2;
        n2->height = max(getHeight(n2->left), getHeight(n2->right)) + 1;
        n1->height = max(getHeight(n1->left), getHeight(n2)) + 1;
        n2 = n1;
    }

    // function rotates right child
    void rotateRightChild(AVLNode<T> *&n1)
    {
        AVLNode<T> *n2 = n1->right;
        n1->right = n2->left;
        n2->left = n1;
        n1->height = max(getHeight(n1->right), getHeight(n1->left)) + 1;
        n2->height = max(getHeight(n2->right), getHeight(n1)) + 1;
        n1 = n2;
    }

    // double rotation for left child
    void doubleLeftChild(AVLNode<T> *&n3)
    {
        rotateRightChild(n3->left);
        rotateLeftChild(n3);
    }

    // double rotation for right child
    void doubleRightChild(AVLNode<T> *&n3)
    {
        rotateLeftChild(n3->right);
        rotateRightChild(n3);
    }

    // function uses previous four functions to insert into AVL tree and balance if needed
    void insert(AVLNode<T> *&node, T data) 
    {
        if(node == nullptr) 
        {
            // create new node
            node = new AVLNode<T>(data);
        }
        else if(data < node->data) 
        {
            // insert into left subtree
            insert(node->left, data);
            // if height isn't balanced
            if(getHeight(node->left) - getHeight(node->right) == 2)
            {
                if(data < node->left->data)
                {
                    rotateLeftChild(node);
                }
                else
                {
                    doubleLeftChild(node);
                }
            }
        }
        else if(data > node->data) 
        {
            insert(node->right, data);
            if(getHeight(node->right) - getHeight(node->left) == 2)
            {
                if(node->right->data < data)
                {
                    rotateRightChild(node);
                }
                else
                {
                    doubleRightChild(node);
                }
            }
        }

        // update height 
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    // functions starts recursive call
    bool contains(T& data) 
    {
        return containsRecursive(root, data);
    }

    bool validate() 
    {
        return validateRecursive(root);
    }
        

private:

    // function destroys tree by deallocating memory recursively 
    void destroyTree(AVLNode<T> *tree)
	{
		if(tree != nullptr)
		{
			destroyTree(tree->left);
			destroyTree(tree->right);
			delete tree;
		}
	}

    // function finds if tree contains given data
    bool containsRecursive(AVLNode<T>* node, T& data) 
    {
        if(node == nullptr) return false;

        if(data == node->data) return true;

        if(data < node->data) return containsRecursive(node->left, data);

        else return containsRecursive(node->right, data);
    }

    // function validates that the tree is balanced
    bool validateRecursive(AVLNode<T>* node) 
    {
       if(node == nullptr) return true;

       int balance = getBalance(node);

       if(balance < - 1 || balance > 1) return false;

       return validateRecursive(node->left) && validateRecursive(node->right);
    }

    // function gets height at given node
    int getHeight(AVLNode<T>* node) 
    {
        return node == nullptr ? -1 : node->height;
    }

    // function gets balance of tree
    int getBalance(AVLNode<T>* node) 
    {
       if(node == nullptr) return 0;
       return (getHeight(node->left) - getHeight(node->right));
    }
};

#endif // AVLTREE_H
