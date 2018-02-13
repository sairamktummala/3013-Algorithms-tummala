
/*
SAI RAMA KRISHNA TUMMALA
Title:Fix Delete method
Files: main.cpp, BSTree.cpp, BSTree.h
Semester: (3013) Spring 2018
Author: Sai Rama Krishna Tummala
Email: sairamktummala@gmail.com
Description: fixed the delete method and it can handle deleting the 
             root node when it doesn't have left or right child
*/

#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct node
{
	int data;
	node *left;
	node *right;

	node();
	node(int x);
};

class BSTree
{
private:
	node *root;

	int count(node *root);

	void insert(node *&root, node *&temp);

	void print_node(node *n, string label = "");

	/**
	* type = ['predecessor','successor']
	*/
	node *minValueNode(node *root);

	node *deleteNode(node *&root, int key);

	int height(node *root);

	/* Print nodes at a given level */
	void printGivenLevel(node *root, int level);

	//************************************************************************
	// Method to help create GraphViz code so the expression tree can
	// be visualized. This method prints out all the unique node id's
	// by traversing the tree.
	// Recivies a node pointer to root and performs a simple recursive
	// tree traversal.
	//************************************************************************
	void GraphVizGetIds(node *nodePtr, ofstream &VizOut);

	//************************************************************************
	// This method is partnered with the above method, but on this pass it
	// writes out the actual data from each node.
	// Don't worry about what this method and the above method do, just
	// use the output as your told:)
	//************************************************************************
	void GraphVizMakeConnections(node *nodePtr, ofstream &VizOut);

public:
	BSTree();

	~BSTree();

	int count();

	void insert(int x);

	void deleteNode(int key);

	void minValue();

	int height(int key = -1);

	int top();

	/* Function to line by line print level order traversal a tree*/
	void printLevelOrder();

	//************************************************************************
	// Recieves a filename to place the GraphViz data into.
	// It then calls the above two graphviz methods to create a data file
	// that can be used to visualize your expression tree.
	//************************************************************************
	void GraphVizOut(string filename);
};

#endif
