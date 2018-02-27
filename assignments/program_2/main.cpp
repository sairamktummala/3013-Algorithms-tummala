
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
#include <iostream>
#include <cstdlib>
#include "BSTree.h"

using namespace std;

int main()
{
	srand(2342);

	BSTree B;

	B.insert(38);
	B.insert(10);
	B.insert(29);
	B.insert(27);
	B.insert(5);
	B.insert(43);
	B.insert(36);
	B.insert(3);
	B.printLevelOrder();
	B.GraphVizOut("before.txt");

	// Continously delete root node, until tree is empty
	while (B.top()) {
		cout << "removing: " << B.top() << endl;
		B.deleteNode(B.top());
	}

	B.deleteNode(3);
	B.deleteNode(29);
	B.deleteNode(27);
	B.deleteNode(10);
	B.printLevelOrder();

	B.GraphVizOut("after.txt");
	system("pause");
	return 0;
}
