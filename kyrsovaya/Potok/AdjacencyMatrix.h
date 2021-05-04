#pragma once
#include <string>
#include "LinkedList.h"
using namespace std;
class AdjacencyMatrix
{
private:
	size_t sizeMatrix;
	int** Matrix;
	int** MaxFlow;
	int** Flow;

	char* Vertices;
public:
	AdjacencyMatrix(string);
	~AdjacencyMatrix()
	{
		delete Matrix;
		delete Vertices;
	};
	void createMatrix(string);
	int Edmonds_Karp();
	LinkedList* Bellman_Ford();
	unsigned int findNewIndex(char);
	unsigned int findCity(char);

	void printMatrix();
};