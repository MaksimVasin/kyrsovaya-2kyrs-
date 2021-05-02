#include <iostream>
#include <fstream>
#include "AdjacencyMatrix.h"
#include "LinkedList.h"

int main()
{
	string fileName = "in.txt";
	AdjacencyMatrix* Matrix = new AdjacencyMatrix(fileName);
	Matrix->createMatrix(fileName);
	//Matrix->Bellman_Ford();
	Matrix->Edmonds_Karp();
}
