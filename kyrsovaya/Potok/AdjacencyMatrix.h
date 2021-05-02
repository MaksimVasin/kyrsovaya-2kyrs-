#pragma once
#include <string>
#include "LinkedList.h"
using namespace std;
class AdjacencyMatrix
{
private:
	size_t sizeMatrix;
	int** Matrix;
	int** MaxPotok;
	int** Potok;

	char* Cities;
public:
	AdjacencyMatrix(string); // creating a list WITHOUT data
	~AdjacencyMatrix()
	{
		delete Matrix;
		delete Cities;
	};
	void createMatrix(string);
	int Edmonds_Karp();
	LinkedList* Bellman_Ford();
	unsigned int findNewIndex(char);
	unsigned int findCity(char);

	void printMatrix();
};