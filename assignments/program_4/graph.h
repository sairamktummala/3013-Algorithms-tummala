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
#pragma once

#include <algorithm>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include "edge_heap.h"
#include "distance.h"
#include "csv.h"
#include <queue>
#include <stack>


using namespace std;


struct DistancendexPair
{
	int index;
	double distance;

};

bool Comparer(const DistancendexPair &left, const DistancendexPair &right)
{
	return left.distance < right.distance;
}

// Might use as a lookup from city name to ID.
// And to filter duplicate cities.
typedef map<string, int> strMapInt;

typedef map<int, int> intint;

extern struct latlon
{

public: double lat;
		double lon;
		latlon()
		{
			lat = 0.0;
			lon = 0.0;
		}

		latlon(double y, double x)
		{
			lat = y;
			lon = x;
		}

		/**
		* operator= - overload assignment for latlon
		* Params:
		*     const latlon ll     - lat lon to assign
		* Returns
		*     reference to assignment for chaining (e.g. a = b = c )
		*/
		latlon &operator=(const latlon &ll)
		{
			// do the copy
			lat = ll.lat;
			lon = ll.lon;

			// return the existing object so we can chain this operator
			return *this;
		}

		/**
		* operator<< - overload cout for latlon
		* Params:
		*     const latlon ll     - lat lon to print
		* Returns
		*     formatted output for a latlon
		*/
		friend ostream &operator<<(ostream &output, const latlon &ll)
		{
			output << "(" << ll.lat << "," << ll.lon << ")";
			return output;
		}
};



/**
* vertex - represents a vertex in a graph.
*/
struct vertex
{
	int ID;
	string city;
	string state;
	latlon loc;
	vector<edge> E;
	bool visited;
	bool isConnectedTo(int id) {
		for (vector<edge>::iterator it = E.begin(); it != E.end(); it++) if (it->toID == id) return true;
		return false;
	}
	int dropLongestEdge(double & distance) {
		int targetI = -1;
		int i = 0;
		for (unsigned i = 0; i < E.size(); i++)
			if (i == 0 || E[i].weight > E[targetI].weight)
			{
				distance += E[i].weight;
				targetI = i;
			}
		if (targetI >= 0) {
			E.erase(E.begin() + targetI);
			i++;
		};
		return i;
	}
	/**
	* vertex<< - overload cout for vertex
	* Params:
	*     const vertex v     - vertex to print
	* Returns
	*     formatted output for a vertex
	*/
	vertex(int id, string c, string s, latlon ll = latlon())
	{
		ID = id;
		city = c;
		state = s;
		loc = ll;
		visited = false;
	}

	/**
	* operator<< - overload cout for vertex
	* Params:
	*     const vertex v     - vertex to print
	* Returns
	*     formatted output for a vertex
	*/
	friend ostream &operator<<(ostream &output, const vertex &v)
	{
		output << "(ID:" << v.ID << " C: " << v.city << " S: " << v.state << " L: " << v.loc << " Edges:" << v.E.size() << ")";
		return output;
	}
};


class graph
{
	ofstream output;
public:
	int id;                      // id counter for new vertices
	int num_edges;               // edge count
	vector<vertex *> vertexList; // vector to hold vertices
	strMapInt cityLookup;

	vertex *createVertex(string city, string state, latlon ll)
	{
		return new vertex(id++, city, state, ll);
	}

	void createSpanningTree(string cityS, string filter = "")
	{
		//string cityS = "Lebanon";
		vector<vertex *>::iterator vit; // to iterate vertexList
		vector<vertex *> exploredVertices; // to keep track of explored vertices
		vector<vertex *>::iterator evit; // to iterate exploredVertices
		int *degree = new int[vertexList.size()]; // to keep track of degree of each vertex
		int k = 0; // to access degree vector

		int ID1, ID2;
		int startID;
		double minDistance;
		double distance;

		for (vit = vertexList.begin(); vit != vertexList.end(); vit++)
		{
			if ((*vit)->city == cityS)
			{
				exploredVertices.push_back(*vit);
				break;
			}
		}

		vit = vertexList.begin();
		evit = exploredVertices.begin();

		// if the first vertex of vertexList is already explored
		if (find(exploredVertices.begin(), exploredVertices.end(), *vit) != exploredVertices.end())
		{
			vit++;
			minDistance = distanceEarth((*evit)->loc.lat, (*evit)->loc.lon, (*vit)->loc.lat, (*vit)->loc.lon);
		}
		else
		{
			minDistance = distanceEarth((*evit)->loc.lat, (*evit)->loc.lon, (*vit)->loc.lat, (*vit)->loc.lon);
		}

		for (int i = 0; i < vertexList.size() - 1; i++)
		{
			evit = exploredVertices.begin();
			for (int j = 0; evit != exploredVertices.end() && vit != vertexList.end(); evit++, j++)
			{
				if (degree[j] < 3)
				{
					for (vit = vertexList.begin(); vit != vertexList.end(); vit++)
					{
						// skip if vertex is already explored
						if (find(exploredVertices.begin(), exploredVertices.end(), *vit) != exploredVertices.end())
						{
							continue;
						}
						else
						{
							try
							{
								distance = distanceEarth((*evit)->loc.lat, (*evit)->loc.lon, (*vit)->loc.lat, (*vit)->loc.lon);
								if (minDistance > distance)
								{
									minDistance = distance;
									ID1 = (*evit)->ID;
									ID2 = (*vit)->ID;
									k = j;
									exploredVertices.push_back(*vit);
								}
							}
							catch (const std::exception&)
							{

							}
						}
					}
				}
			}

			addEdge(ID1, ID2, minDistance);
			degree[k]++;
			minDistance = 7000;
		}
	}

	void buildEdges(int vertexId, int maxEdges, double &distance) {
		vertex *v = vertexList[vertexId];
		// We start at the given vertex

		stack<vertex *> s; s.push(v);
		while (!s.empty()) { 
			
			// Process the next vertex
			v = s.top(); s.pop();
			
			// Process only vertices if they have less than the maximum out degree
			if (v->E.size() >= (unsigned)maxEdges) continue;
			
			// The current vertex will compute the distance to other vertices 
			for (vector<vertex *>::iterator it = vertexList.begin(); it != vertexList.end(); it++) {
			
				// Ignore the next vertex if its the same current vertex 
				if ((*it) == v) continue;
				
				// Ignore if the vertex is in the edge of the current vertex 
				if (!v->isConnectedTo((*it)->ID)) { // Create an edge to the other vertex 
					double weight = distanceEarth(v->loc.lat, v->loc.lon, (*it)->loc.lat, (*it)->loc.lon);
					distance += weight;
					v->E.push_back(edge((*it)->ID, weight));
					num_edges++;
				
					// Set the vertex for processing next later
					s.push(*it);
					
					// For the current vertex we have to keep only up to "maxEdges" edges 
					if (v->E.size() > (unsigned)maxEdges)
						num_edges -= v->dropLongestEdge(distance);

				}
			}
		}
	}


	/**
	* graph - constructor
	*/
	graph()
	{
		id = 0;
		num_edges = 0;
	}

	graph(const graph &G)
	{
		id = G.id;
		num_edges = G.num_edges;
		vertexList = G.vertexList;
		cityLookup = G.cityLookup;
	}


	int addVertex(string city, string state, double lat = 0.0, double lon = 0.0)
	{
		if (cityLookup.find(city) == cityLookup.end())
		{
			// Add the city as a key to the map.
			cityLookup[city] = 0;
		}
		else
		{
			return -1;
		}

		vertex *temp = createVertex(city, state, latlon(lat, lon));
		vertexList.push_back(temp);

		//update the value that city points to.
		cityLookup[city] = temp->ID;
		return temp->ID;
	}



	void addEdge(int fromID, int toID, double weight = 0, bool directed = false)
	{
		edge e1(toID, weight);
		vertexList[fromID]->E.push_back(e1);
		num_edges++;

		//cout<<"adding "<<fromID<<" to "<<toID<<endl;

		if (!directed)
		{
			edge e2(fromID, weight);
			vertexList[toID]->E.push_back(e2);

			//cout<<"adding "<<toID<<" to "<<fromID<<endl;

			num_edges++;
		}
	}


	void printGraph()
	{

		vector<vertex *>::iterator vit;
		vector<edge>::iterator eit;

		for (vit = vertexList.begin(); vit != vertexList.end(); vit++)
		{
			cout << *(*vit) << endl;

			if ((*vit)->E.size() > 0)
			{
				for (eit = (*vit)->E.begin(); eit != (*vit)->E.end(); eit++)
				{
					cout << "\t" << (*eit) << endl;
				}
			}
		}
	}
	void SaveToFileGraph()
	{
		ofstream out;
		vector<vertex *>::iterator vit;
		vector<edge>::iterator eit;

		for (vit = vertexList.begin(); vit != vertexList.end(); vit++)
		{
			out << *(*vit) << endl;

			if ((*vit)->E.size() > 0)
			{
				for (eit = (*vit)->E.begin(); eit != (*vit)->E.end(); eit++)
				{
					out << "\t" << (*eit) << endl;
				}
			}
		}
		out.close();
	}

	string ToLower(string s) {
		for (int i = 0; i < s.length(); i++) {
			s[i] = tolower(s[i]);
		}
		return s;
	}





	void printVids() {
		vector<vertex *>::iterator vit;
		vector<edge>::iterator eit;

		for (vit = vertexList.begin(); vit != vertexList.end(); vit++)
		{
			cout << (*vit)->ID << endl;
		}
	}

	string graphViz(bool directed = true, string filter = "PR") {
		vector<vertex *>::iterator vit;
		vector<edge>::iterator eit;

		// [label="hi", weight=100];

		string viz = "";
		string labels = "";
		string conns = "";
		int weight = 0;
		string arrow = "";

		if (directed) {
			viz = "digraph G {\n";
			arrow = "->";

		}
		else {
			viz = "graph G {\n";
			arrow = "--";
		}

		for (vit = vertexList.begin(); vit != vertexList.end(); vit++)
		{
			if ((*vit)->E.size() > 0)
			{
				if (!filter.empty() && (*vit)->state != filter)
				{
					continue;

				}
				labels += "\t" + to_string((*vit)->ID) + " [label=\"" + (*vit)->city + ", " + (*vit)->state + "\"]\n";

				for (eit = (*vit)->E.begin(); eit != (*vit)->E.end(); eit++)
				{
					if (!filter.empty() && vertexList[eit->toID]->state != filter)
					{
						continue;

					}

					labels += "\t" + to_string(eit->toID) + " [label=\"" + vertexList[eit->toID]->city + ", " + vertexList[eit->toID]->state + "\"]\n";

					weight = eit->weight;
					conns += "\t" + to_string((*vit)->ID) + arrow
						+ to_string(eit->toID) + " [weight=" + to_string(weight) + ", label=" + to_string(weight) + "]\n";
				}
			}
		}

		viz += labels;
		viz += conns;
		viz += "}\n";

		return viz;
	}

	int maxID()
	{
		return id;
	}


	int* graphSize() {
		int* vals = new int[2];
		vals[0] = vertexList.size();
		vals[1] = num_edges;
		return vals;
	}


	graph &operator=(const graph &g)
	{
		// do the copy
		vertexList = g.vertexList;
		id = g.id;

		// return the existing object so we can chain this operator
		return *this;
	}


	int search(string temp, string state) {
		for (int i = 0; i < vertexList.size(); i++)
		{
			if (ToLower(vertexList[i]->city) == ToLower(temp) && ToLower(vertexList[i]->state) == ToLower(state))
				return i;
		}
		return -1;
	}




};