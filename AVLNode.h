#ifndef AVLNODE_H
#define AVLNODE_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename T>
class AVLNode 
{
public:
// constructor and destructor
    AVLNode(T &value) : data(value), left(nullptr), right(nullptr), height(0) {}
    ~AVLNode() {}

    // public data members declared
    T data;
    AVLNode<T>* left;
    AVLNode<T>* right;
    int height;
};

#endif // AVLNODE_H
