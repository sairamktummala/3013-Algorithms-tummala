#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "bsTree.h"
#include "avlTree.h"

using namespace std;

// Load the words from file and put it in the binary search tree and avl tree
void loadWords(string filename, BSTree &binarySearchTree, avlTree &balancedBSTree, int &numWords)
{
	ifstream inFile;
	inFile.open(filename.c_str());

	if (!inFile.is_open())
	{
		cout << "Failed to open file " << filename << endl;
		exit(0);
	}

	string word;
	numWords = 0;

	while (inFile >> word)
	{
		binarySearchTree.insert(word);
		balancedBSTree.insert(word);
		numWords++;
	}

	inFile.close();
}

// Entry point of the program
int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cout << "Please add the generated crazy words filename as an argument." << endl;
		return 0;
	}

	string filenames[] = {
		"word_files/adjectives.txt", "word_files/nouns.txt",
		"word_files/verbs.txt", "word_files/adverbs.txt",
		"word_files/animals.txt" };

	int wordsCount[5];

	BSTree binarySearchTree;
	avlTree balancedBSTree;


	// Load both data structures with the same order that the files are listed from the previous program.
	for (int i = 0; i < 5; i++)
	{
		cout << "Loading words from " << filenames[i] << " to both BST and AVL" << endl;
		int count = 0;
		loadWords(filenames[i], binarySearchTree, balancedBSTree, count);
		wordsCount[i] = count;
	}

	// Analyze the ten thousand words
	cout << "Analyzing tenthousandwords.txt..." << endl;

	ifstream inFile;
	inFile.open(argv[1]);

	// Read each word from the ten thousand words and find them in the tree
	string word;

	int bstComparisons = 0;
	int avlComparisons = 0;

	while (inFile >> word)
	{
		binarySearchTree.search(word, bstComparisons);
		balancedBSTree.search(word, avlComparisons);
	}
	
	inFile.close();

	// Output the analysis
	ofstream outFile;
	outFile.open("analysis.out");
	
	outFile << "BST Comparisons = " << bstComparisons << endl;
	outFile << "AVL Comparisons = " << avlComparisons << endl;

	string wordCategories[] = { "Adjectives", "Nouns", "Verbs", "Adverbs", "Animals" };

	for (int i = 0; i < 5; i++)
		outFile << "Number of " << wordCategories[i] << " = " << wordsCount[i] << endl;
	
	outFile << "Analysis written to analysis.out" << endl;

	return 0;
}