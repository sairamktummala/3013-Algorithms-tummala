//Name: SAI RAMA KRISHNA TUMMALA
//Date: 1/3/2018
//Assignment: Program 3
#ifndef AVLTREE_H
#define AVL_TREE_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct node {
	string value;
	node *left;
	node *right;
	node *parent;
	int avlValue;

	node(string word){
		value = word;
		left = right = parent = NULL;
		avlValue = 0;
	}
};

class avlTree{

private:
	node *root;
	bool rightHeavy(node *);
	bool leftHeavy(node *);
	void insert(node *&, node *&);
	void inorder(node *);
	void preorder(node *);
	void postorder(node *);
	node* remove(node*&, string);
	node* predSuccessor(node*);
	void printNode(node *, string);
	int  height(node *);
	void computeAvlValues(node *&);
	void rotateLeft(node *&);
	void rotateRight(node *&);
	int  avlValue(node *);

public:
	avlTree();
	~avlTree();
	void doDumpTree(node *);
	void dumpTree(){
		cout << "---------------------------------" << endl;
		cout << "Root:   " << root << "\n";
		doDumpTree(root);
	};
	void insert(string);
	void showInorder(){ inorder(root); };
	void showPreorder(){ preorder(root); };
	void showPostorder(){ postorder(root); };
	bool search(string, int &);
	void remove(string word){ root = remove(root, word); };
	int  treeHeight();
	void graphVizGetIds(node *, ofstream &);
	void graphVizMakeConnections(node *, ofstream &);
	void graphVizOut(string);
};

#endif
