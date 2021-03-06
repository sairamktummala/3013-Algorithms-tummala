/*
SAI RAMA KRISHNA TUMMALA

Title:Priority Queue

Files: main.cpp

Semester: (3013) Spring 2018

Author: Sai Rama Krishna Tummala

Email: sairamktummala@gmail.com

Description: Adding a method called orderedSert which randomly prints some numbers
             and sorting them in ascending order.
            
*/
#include <iostream>
#include <ctime>

using namespace std;

//Create a container for our list data
struct node {
	int data;
	node* next;
};

/**
* Class: intLinkedList
* Purpose:
*     Implements a singly linked list that holds integers.
* Methods:
*     void  frontSert(int x)
*     node* find(int key)
*     node* remove(int key)
*     void  print()
*     void orderedSert()
*/
class intLinkedList {
private:
	node* Head;
public:
	intLinkedList() {
		Head = NULL;
	}
	void frontSert(int x) {
		//empty list case
		if (!Head) {
			Head = new node;
			Head->data = x;
			Head->next = NULL;
		}
		else {//not empty list
			node* T = new node;
			T->data = x;
			T->next = Head;
			Head = T;
		}
	}
	void orderedSert() {
		node* current = Head;
		int count = 0;
		while (current != NULL)
		{
			count++;
			current = current->next;
		}
		for (int i = count; i > 1; i--)
		{
			node *temp = NULL;
			node *tempHead;
			tempHead = Head;

			for (int j = 0; j < count - 1; j++)
			{
			  //if first number is greater than second one it goes into loop
				if (tempHead->data > tempHead->next->data)
				{
					node *tempNext = tempHead->next;
					tempHead->next = tempNext->next;
					tempNext->next = tempHead;
					//if the first number is smaller then it will go into temporary values
					if (tempHead == Head)
					{
						Head = tempNext;
						tempHead = tempNext;
					}
					//if the first number is not smaller then it will go into the loop
					else
					{
						tempHead = tempNext;
						temp->next = tempNext;
					}
				}
				temp = tempHead;
				tempHead = tempHead->next;
			}
		}
	}

	node* Find(int key) {
		node* temp = Head;
		while (temp) {
			if (temp->data == key) {
				return temp;
			}
			temp = temp->next;
		}
		return NULL;
	}

	void Remove(int key) {
		node* result = Find(key);
		if (result) {
			node* temp = Head;
			while (temp->next != result) {
				temp = temp->next;
			}
			temp->next = result->next;
			delete result;
		}
	}

	void print() {
		node* p = Head;
		while (p) {
			cout << p->data << endl;
			p = p->next;
		}
	}

	
};

int main() {
	// seed random number generator
	srand(8734587);

	// ummmm
	cout << "Hello World!\n";

	// declare instance of intLinkedList turning
	// a class definition into an "object"
	intLinkedList mylist;

	//Load 10 random ints into our list
	for (int i = 0; i<10; i++) {
		mylist.frontSert(rand() % 100);
	}


	//print the list
	mylist.print();

	//find some value
	cout << mylist.Find(99) << endl;

	//remove some value 
	mylist.Remove(58);

	//print the list again
	mylist.print();

	//insert and print in ascending order
	cout << "Inserting number here \n";
	mylist.frontSert(16);
	mylist.frontSert(65);
	cout << endl;

	mylist.orderedSert();
	mylist.print();

	system("pause");
}
