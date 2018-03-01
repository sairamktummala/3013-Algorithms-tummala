//Name: SAI RAMA KRISHNA TUMMALA
//Date: 1/3/2018
//Assignment: Program 3
//Description: generating the tenthousandwords using adjectives, adverbs, animals, verbs, nouns
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

// Load a word from a specific file name
void loadWords(vector<string> &words, string filename)
{
	ifstream inFile;
	inFile.open(filename.c_str());

	if (!inFile.is_open())
	{
		cout << "Failed to open file " << filename << endl;
		exit(0);
	}

	string word;

	// Load each word found into the list of words
	while (inFile >> word)
		words.push_back(word);

	inFile.close();
}

// Get a random word from the list of words
string getRandomWord(vector<string> &words)
{
	return words[rand() % words.size()];
}

// This program will generate 10,000 unique sentences into a file
int main()
{
	srand((unsigned) time(NULL));

	// Load all the words coming from different categories
	string filenames[] = { 
		"word_files/animals.txt", "word_files/adjectives.txt", 
		"word_files/adverbs.txt", "word_files/nouns.txt", 
		"word_files/verbs.txt" };

	vector< vector<string> > words;
	
	for (int i = 0; i < 5; i++)
	{
		cout << "Loading " << filenames[i] << "..." << endl;
		vector<string> wordsInACategory;
		loadWords(wordsInACategory, filenames[i]);
		words.push_back(wordsInACategory);
	}
	
	// No we generate 10,000 crazy words
	ofstream outFile;
	outFile.open("tenthousandwords.txt");

	map<string, string> crazyWords;

	cout << "Generating 10,000 crazy words..." << endl;

	for (int i = 0; i < 10000; i++)
	{
		// Generate how many word we need to combine, randomize it. It will be 3 to 5 words.
		while (true)
		{
			int numWords = (rand() % 2) + 3;
			string crazyWord = "";

			// Given the num words generate a pattern of category but will be random also
			for (int j = 0; j < numWords; j++)
			{
				int category = rand() % words.size();
				crazyWord += words[category][rand() % words[category].size()];

				if (j + 1 < numWords)
					crazyWord += " ";
			}

			// Okay, make sure that there is no duplicate of crazy word, otherwise repeat again and make another
			if (crazyWords.find(crazyWord) == crazyWords.end())
			{
				outFile << crazyWord << endl;
				break;
			}
		}
	}

	outFile.close();
	cout << "Generated 10,000 crazy words to crazywords.txt file." << endl;

	return 0;
}
