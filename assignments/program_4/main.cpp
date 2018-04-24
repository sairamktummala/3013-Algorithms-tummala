///////////////////////////////////////////////////////////////////////////////
//                   
// Title:            Spanning Trees
// Files:            edge_heap.h, filtered_cities.csv, csv.h, distance.h, graph.h
//                    main.cpp
// Semester:         (3013 Advanced structures and Algorithms)Spring 2018
// Date:              4/24/2018
// Author:           SAI RAMA KRISHNA TUMMALA
// Email:            sairamktummala@gmail.com
// Description:
//     Spanning tree has all the vertices covered with minimum possible
//      number of edges.Fully connecting your cities by adding edges between cities 
//      that are close together. All the vertices have a maximum degree of 3.
/////////////////////////////////////////////////////////////////////////////////
#include "graph.h"
#include <stdio.h>


using namespace std;

graph loadGraphCSV(string filename, int max)
{
	int zip;
	double lat;
	double lon;
	string city;
	string state;
	string county;


	strMapInt cityCheck;

	int i = 0;

	graph G;

	ifstream file;

	file.open("filtered_cities.csv", 0);

	bool asd = file.is_open();



	for (CSVIterator loop(file); loop != CSVIterator(); ++loop)
	{
		zip = stoi((*loop)[0]);
		if ((*loop)[1].length() > 0)
		{
			lat = stod((*loop)[1]);
		}
		else
		{
			lat = 0.0;
		}

		if ((*loop)[2].length() > 0)
		{
			lon = stod((*loop)[2]);
		}
		else
		{
			lon = 0.0;
		}

		city = (*loop)[3];
		state = (*loop)[4];
		county = (*loop)[5];


		if (cityCheck.find(city) == cityCheck.end())
		{
			// Add the city as a key to the map.
			cityCheck[city] = 0;

			//if (state != "PR") {
			G.addVertex(city, state, lat, lon);

			//}
		}


		if (i >= max)
		{
			break;
		}

		i++;
	}

	return G;
}

int main(int argc, char **argv)
{
	srand(984325);
	ofstream output;
	output.open("output.txt", ios::out);
	output << "";
	output.close();
	int maxVertix = -1;
	do
	{
		cout << "Enter Number of Max Vertices : ";
		cin >> maxVertix;
		cout << endl;


	} while (maxVertix<1);

	do
	{

		cin.ignore();
		graph G = loadGraphCSV("filtered_cities.csv", maxVertix);
		string starting, state;
		double lat, lon;
		int index, maxEdges;
		cout << "Enter city: (eg. Adjuntas) ";
		getline(cin, starting);

		cout << "Enter State: (eg. PR) ";

		getline(cin, state);


		index = G.search(starting, state);
		while (index == -1) {
			cout << "Invalid Input, try again.";
			cout << "Enter city: (eg. Adjuntas) ";
			getline(cin, starting);

			cout << "Enter State: (eg. PR) ";
			getline(cin, state);

			index = G.search(starting, state);

		}

		cout << "Max Edges Per vertex: ";
		cin >> maxEdges;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(128, '\n');
			cout << "Try Again.";
		}

		double distance = 0;
		G.buildEdges(index, maxEdges, distance);
		output.open("output.txt", ios::out | ios::app);
		output << "Index OF " << starting << "," << state << " is :  " << index << endl;
		output << "Distance : " << distance << " miles | " << "Edges : " << G.num_edges << endl << endl;
		output.close();

		G.SaveToFileGraph();


		ofstream outputfile;
		outputfile.open("viz - " + starting + "," + state + ".txt");
		//G.createSpanningTree(G.vertexList[index]->city);
		outputfile << G.graphViz(true, "PR");
		outputfile.close();

		char ch;
		cout << "Want to calculate for more cities ? Select Y for YES and any key for NO : ";
		while (true)
		{
			cin >> ch;

			if (!(ch == 'Y' || ch == 'y'))
			{
				return 0;
			}
			else
			{
				cout << endl;
				break;
			}
		}

	} while (true);

	return 0;
}