#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

//This struct will be used to store all of the points in a vertex
struct Vertex {
	int xComp;
	int yComp;
	bool isChecked;
};

void MST(vector<Vertex>& allPoints, int& weight, int verticies, int& startPoint);

int nearestInt(int x1, int y1, int x2, int y2);

bool allVertexCheck(vector<Vertex> allPoints, int verticies);


// This function calculates the shortest distance from a starting point to another point that has not already been visited.
// It uses a reference to a vector of verticies, the total weight, the number of verticies, and a reference to the starting point.
void MST(vector<Vertex>& allPoints, int& weight, int verticies, int& startPoint) {

	//I set this value high so that when the algorithm finds a shorter distance, it will be updated. If I 
	// initialized this value to 0, then the algorithm would never find a smaller distance then that.
	int shortest = (unsigned int)~0 >> 1; 
	
	int closestVertex = 0;
	int theCurrentVertex = 0;

	for (int i = 0; i < verticies; i++) {
		// If the distance between two vertecies is 0, then we must be comparing the starting vertex to itself, so we skip it entirely.
		if (nearestInt(allPoints[startPoint].xComp, allPoints[startPoint].yComp, allPoints[i].xComp, allPoints[i].yComp) == 0) {
			theCurrentVertex = i;
		}
		//If the distance != 0, then we are looking at another vertex besides the starting vertex.
		//If the distance between the starting vertex and the current vertex is less than the current smallest distance
		else if (!allPoints[i].isChecked && nearestInt(allPoints[startPoint].xComp, allPoints[startPoint].yComp, allPoints[i].xComp, allPoints[i].yComp) < shortest) {
			//We update the new smallest distance
			shortest = nearestInt(allPoints[startPoint].xComp, allPoints[startPoint].yComp, allPoints[i].xComp, allPoints[i].yComp);
			//And say that the new closest vertex is at this index.
			closestVertex = i;
		}

	}

	//Check both of the vertecies as visited
	allPoints.at(closestVertex).isChecked = true;
	allPoints.at(theCurrentVertex).isChecked = true;
	//Update the weight
	weight = weight + shortest;
	//Set the next starting point as the closest vertex
	startPoint = closestVertex;

}

//This function takes in two points and returns the distance between them (rounded).
int nearestInt(int x1, int y1, int x2, int y2) {
	int rtn = 0;
	int xDiff = x1 - x2;
	int yDiff = y1 - y2;
	rtn = round(sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2)));

	return rtn;
}

//This function checks if all of the vertecies have been visited.
bool allVertexCheck(vector<Vertex> allPoints, int verticies) {
	bool rtn = false;
	for (int i = 0; i < verticies; i++) {
		if (allPoints[i].isChecked) {
			rtn = true;
		}
		else {
			return false;
		}
	}
	return rtn;

}

int main() {

	int cases = 0;
	int verticies = 0;
	int totalWeight = 0;
	int start = 0;
	Vertex tempVertex;
	vector<Vertex> allVertex;
	
	//Open the file, get the data parsed, and put the data into the vector as Vertex variables.
	ifstream file;
	file.open("graph.txt");
		file >> cases;
		for (int i = 0; i < cases; i++) {
			file >> verticies;
			for (int i = 0; i < verticies; i++) {
				file >> tempVertex.xComp;
				file >> tempVertex.yComp;
				tempVertex.isChecked = false;
				allVertex.push_back(tempVertex);
			}
			//For all verticies,
			for (int i = 0; i < verticies; i++) {
				//While not all of the vertecies have been visited,
				while (!allVertexCheck(allVertex, verticies)) {
					//Find the smallest distance away from the starting vertex.
					MST(allVertex, totalWeight, verticies, start);
				}
				
			}
			cout << "Test Case: " << i + 1 << endl;
			cout << "MST Weight: " << totalWeight << endl << endl;
			//Reset all variables and the vector to be used for the next case. 
			allVertex.clear();
			totalWeight = 0;
			start = 0;
			verticies = 0;
		}

	return 0;
}