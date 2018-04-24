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
#include <math.h>
#include <cmath> 
#include "graph.h"
#define earthRadiusKm 6371.0

#define M_PI 3.14

// This function converts decimal degrees to radians
double deg2rad(double deg) {
	return (deg * M_PI / 180);
}

//  This function converts radians to decimal degrees
double rad2deg(double rad) {
	return (rad * 180 / M_PI);
}

/**
* Returns the distance between two points on the Earth.
* Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
* @param lat1d Latitude of the first point in degrees
* @param lon1d Longitude of the first point in degrees
* @param lat2d Latitude of the second point in degrees
* @param lon2d Longitude of the second point in degrees
* @return The distance between the two points in kilometers


*/



double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
	double lat1r, lon1r, lat2r, lon2r, u, v;
	lat1r = deg2rad(lat1d);
	lon1r = deg2rad(lon1d);
	lat2r = deg2rad(lat2d);
	lon2r = deg2rad(lon2d);
	u = sin((lat2r - lat1r) / 2);
	v = sin((lon2r - lon1r) / 2);

	double re = (asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v)));

	return 2.0 * earthRadiusKm * re;
}