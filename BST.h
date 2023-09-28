#ifndef __BST_H
#define __BST_H

#include <iostream>
#include <limits>
using namespace std;


/*
 *  Data structure for a single tree node
 */
template <typename T>
struct Node {
public:
	T value;
	Node* left;
	Node* right;

	Node(T val) {
		this->value = val;
		this->left = nullptr;
		this->right = nullptr;
	}

	~Node()
	{
		this->value = 0;
		this->left = nullptr;
		this->right = nullptr;
	}
};

/*
 * Binary Search Tree (BST) class implementation
 */
template <typename T>
class BST {

protected:
	Node<T>* _root;         // Root of the tree nodes

	/* Add new T val to the tree */
	void addHelper(Node<T>* root, T val) {
		if (root->value > val) {
			if (!root->left) {
				root->left = new Node<T>(val);
			}
			else {
				addHelper(root->left, val);
			}
		}
		else {
			if (!root->right) {
				root->right = new Node<T>(val);
			}
			else {
				addHelper(root->right, val);
			}
		}
	}

	/* Print tree out in inorder (A + B) */
	void printInOrderHelper(Node<T>* root) {
		if (!root) return;
		printInOrderHelper(root->left);
		cout << root->value << ' ';
		printInOrderHelper(root->right);
	}

	/* Return number of nodes in tree */
	int nodesCountHelper(Node<T>* root) {
		if (!root) {
			return 0;
		}
		else {
			return 1 + nodesCountHelper(root->left) + nodesCountHelper(root->right);
		}
	}

	/* Return height of tree (root == nullptr -> 0) */
	int heightHelper(Node<T>* root) {
		if (!root) {
			return -1;
		}
		else {
			return 1 + max(heightHelper(root->left), heightHelper(root->right));
		}
	}

	/* Delete a given <T> value from tree */
	bool deleteValueHelper(Node<T>* parent, Node<T>* current, T value) {
		if (!current) return false;
		if (current->value == value) {
			if (current->left == nullptr || current->right == nullptr) {
				Node<T>* temp = current->left;
				if (current->right) temp = current->right;
				if (parent) {
					if (parent->left == current) {
						parent->left = temp;
					}
					else {
						parent->right = temp;
					}
				}
				else {
					this->_root = temp;
				}
			}
			else {
				Node<T>* validSubs = current->right;
				while (validSubs->left) {
					validSubs = validSubs->left;
				}
				T temp = current->value;
				current->value = validSubs->value;
				validSubs->value = temp;
				return deleteValueHelper(current, current->right, temp);
			}
			delete current;
			return true;
		}
		return deleteValueHelper(current, current->left, value) ||
			deleteValueHelper(current, current->right, value);
	}

	void destroyTree(Node<T> *tree)
	{
		if(tree != nullptr)
		{
			destroyTree(tree->left);
			destroyTree(tree->right);
			delete tree;
		}
	}

	/********************************* PUBLIC API *****************************/
public:

	BST() : _root(nullptr) { }               // Basic initialization constructor

	/**
	 * Destructor - Needs to free *all* nodes in the tree
	 * TODO: Implement Destructor
	 */
	~BST() {
	    // cout << "TODO: Implement Destructor" << endl;
		destroyTree(_root); // starts recursive call
	}

	/* Public API */
	void add(T val) {
		if (this->_root) {
			this->addHelper(this->_root, val);
		}
		else {
			this->_root = new Node<T>(val);
		}
	}

	void print() {
		printInOrderHelper(this->_root);
	}

	/**
	 * Print the nodes level by level, starting from the root
	 * TODO: Implement printLevelOrder
	 */
	void printLevelOrder() {
		// cout << "TODO: Implement printLevelOrder" << endl;
		
		// vector for current level of BST
		vector<Node<T>*> currentLevel;
		currentLevel.push_back(_root);

		// loops through and prints each level of BST
		while (!currentLevel.empty()) 
		{
			vector<Node<T>*> nextLevel;

			for (Node<T> *node : currentLevel) 
			{
				cout << node->value << " ";

				if (node->left)
					nextLevel.push_back(node->left);
				if (node->right)
					nextLevel.push_back(node->right);
			}

			cout << endl;

        	currentLevel = nextLevel;
    	}
	}

	int nodesCount() {
		return nodesCountHelper(this->_root);
	}

	int height() {
		return heightHelper(this->_root);
	}

	vector<int> findMaxPath(Node<T> *root)
	{
		if(!root) return vector<int>();

		// vector for left path and right path
		std::vector<int> leftPath = findMaxPath(root->left);
		std::vector<int> rightPath = findMaxPath(root->right);

		// Choose the longer path between left and right subtrees
		if (leftPath.size() > rightPath.size()) 
		{
			leftPath.push_back(root->value);
			return leftPath;
		} 
		else 
		{
			rightPath.push_back(root->value);
			return rightPath;
    	}
	}

	/**
	 * Print the maximum path in this tree
	 * TODO: Implement printMaxPath
	 */
	void printMaxPath() {
		// cout << "TODO: Implement printMaxPath" << endl;
		
		// calls findMaxPath and stores into maxPath vector
		vector<int> maxPath = findMaxPath(_root);

		if(_root == nullptr)
		{
			// tree is empty
			cout << "Tree is empty." << endl;
			return;
		}

		for (int i = maxPath.size() - 1; i >= 0; i--) 
		{
			// prints max path
            cout << maxPath[i] << " ";
		}
		cout << endl;
	}

	bool deleteValue(T value) {
		return this->deleteValueHelper(nullptr, this->_root, value);
	}

	/**
	 * Find if the BST contains the value
	 * TODO: Implement contains
	 */
	bool contains(T value) {
	    // cout << "TODO: Implement contains" << endl;
		// return numeric_limits<T>::min();+

		bool contains = false;
		vector<Node<T>*> currentLevel;
		currentLevel.push_back(_root);

		while (!currentLevel.empty()) 
		{
			vector<Node<T>*> nextLevel;

			for (Node<T> *node : currentLevel) 
			{
				if(node->value == value)
					// found value set contains variable to true
					contains = true;

				if (node->left)
					nextLevel.push_back(node->left);
				if (node->right)
					nextLevel.push_back(node->right);
			}

        	currentLevel = nextLevel;
    	}

		return contains;
	}
};

#endif

