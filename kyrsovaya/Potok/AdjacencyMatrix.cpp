#include <iostream>
#include "AdjacencyMatrix.h"
#include <fstream>
#include <string>
#include "LinkedList.h"

using namespace std;
AdjacencyMatrix::AdjacencyMatrix(string fileName)
{
	fstream file;
	string str;
	file.open(fileName, ios::in);
	if (file.eof()) throw out_of_range("file is empty");
	getline(file, str); // count Vertices
	sizeMatrix = atoi(str.c_str());
	Matrix = new int* [sizeMatrix];
	MaxFlow = new int* [sizeMatrix];
	Flow = new int* [sizeMatrix];
	for (size_t i = 0; i < sizeMatrix; i++)
	{
		Matrix[i] = new int[sizeMatrix];
		MaxFlow[i] = new int[sizeMatrix];
		Flow[i] = new int[sizeMatrix];
	}
	for (size_t i = 0; i < sizeMatrix; i++)
		for (size_t j = 0; j < sizeMatrix; j++)
		{
			Flow[i][j] = 0;
			MaxFlow[i][j] = 0;
			if (i == j) Matrix[i][j] = 0; // edge Vertex1 -> Vertex1 = 0
			else Matrix[i][j] = INT16_MAX;
		}
	Vertices = new char[sizeMatrix];
	for (unsigned int i = 0; i < sizeMatrix; i++)
		Vertices[i] = ' ';
};
unsigned int AdjacencyMatrix::findCity(char City)
{
	for (unsigned int i = 0; i < sizeMatrix; i++)
	{
		if (Vertices[i] == City) return i;
	}
	return -1;
}
unsigned int AdjacencyMatrix::findNewIndex(char City)
{
	for (unsigned int i = 0; i < sizeMatrix; i++)
	{
		if (Vertices[i] == ' ') return i;
	}
	return -1;
}
void AdjacencyMatrix::printMatrix()
{
	cout << endl << "  ";
	for (size_t i = 0; i < sizeMatrix; i++)
	{
		cout << Vertices[i] << "        ";
	}
	cout << endl;
	for (size_t i = 0; i < sizeMatrix; i++)
	{
		cout << Vertices[i] << " ";
		for (size_t j = 0; j < sizeMatrix; j++)
		{
			if (Matrix[i][j] == INT16_MAX) { cout << "-"; }
			else cout << Matrix[i][j];
			cout << "(" << Flow[i][j] << "/" << MaxFlow[i][j] << ")   ";
		}
		cout << endl;
	}
	cout << endl;
}
void AdjacencyMatrix::createMatrix(string fileName)
{
	fstream file;
	file.open(fileName, ios::in);
	if (file.eof()) throw out_of_range("file is empty");
	string str;
	getline(file, str); // size
	while (!file.eof())
	{
		char Vertex1, Vertex2;
		unsigned int Index1, Index2;
		string dist;
		getline(file, str);
		unsigned int i = 0;
		///////////////////////////////////////////////////////////////// Vertex1
		Vertex1 = str[i];
		i+=2;
		if (findCity(Vertex1) == -1)
		{
			Index1 = findNewIndex(Vertex1);
			Vertices[Index1] = Vertex1;
		}
		else
		{
			Index1 = findCity(Vertex1);
			Vertices[Index1] = Vertex1;
		}
		if (i >= str.length()) throw out_of_range("incorrect input");
		///////////////////////////////////////////////////////////////// Vertex2
		Vertex2 = str[i];
		i+=2;
		if (findCity(Vertex2) == -1)
		{
			Index2 = findNewIndex(Vertex2);
			Vertices[Index2] = Vertex2;
		}
		else
		{
			Index2 = findCity(Vertex2);
			Vertices[Index2] = Vertex2;
		}
		if (i >= str.length()) throw out_of_range("incorrect input");
		///////////////////////////////////////////////////////////////// edge Vertex1 -> Vertex2
		while (i != str.length())
		{
			dist.push_back(str[i]);
			i++;
		}
		Matrix[Index1][Index2] = 1;
		MaxFlow[Index1][Index2] = atoi(dist.c_str());
		if (i > str.length()) throw out_of_range("incorrect input");
	}
	printMatrix();
}
int minimum(int* array, int size)
{
	int min = INT16_MAX;
	for (int i = 0; i < size; i++)
	{
		if (array[i] < min) min = array[i];
	}
	return min;
}
int minimumIndex(int* array, int size)
{
	int min = INT16_MAX;
	int index = 0;
	for (int i = 0; i < size; i++)
	{
		if (array[i] < min) {
			min = array[i]; index = i;
		}
	}
	return index;
}
LinkedList* AdjacencyMatrix::Bellman_Ford()
{
	LinkedList* WayA_B = new LinkedList();
	char Vertex1 = 'S', Vertex2 = 'T';
	int* minWay = new int[sizeMatrix];
	int* labels = new int[sizeMatrix];
	for (unsigned int i = 0; i < sizeMatrix; i++)
	{
		minWay[i] = INT16_MAX;
	}minWay[findCity(Vertex1)] = 0;
	for (unsigned int k = 1; k < sizeMatrix; k++)
	{
		for (unsigned int i = 0; i < sizeMatrix; i++)
		{
			for (unsigned int j = 0; j < sizeMatrix; j++)
			{
				labels[j] = minWay[j] + Matrix[j][i];
				
			}
			if (minWay[i] > labels[minimumIndex(labels, sizeMatrix)])
			{
				WayA_B->push_back(minimumIndex(labels, sizeMatrix), i);
				minWay[i] = labels[minimumIndex(labels, sizeMatrix)];
			}
			for (unsigned int j = 0; j < sizeMatrix; j++)
				labels[j] = INT16_MAX;
		}
	} 
	LinkedList* minWayList = WayA_B->min_way(); // short path indices per sheet
	if (minWay[findCity(Vertex2)] == INT16_MAX) return nullptr;
	else return minWayList;
}
int AdjacencyMatrix::Edmonds_Karp()
{
	if (findCity('S') == -1 || findCity('T') == -1)
		throw out_of_range("incorrect input");
	int max;
	LinkedList* minWay = Bellman_Ford();
	int* arrI = minWay->listInArr();
	int* dist = new int[minWay->get_size() - 1];
	while (minWay != nullptr)
	{
		//printMatrix();
		for (size_t i = 0; i < minWay->get_size() - 1; i++)
			dist[i] = MaxFlow[arrI[i]][arrI[i + 1]];

		max = minimum(dist, minWay->get_size() - 1);
		for (size_t i = 0; i < minWay->get_size() - 1; i++)
		{
			Flow[arrI[i]][arrI[i + 1]] += max;
			Flow[arrI[i + 1]][arrI[i]] -= max;

			MaxFlow[arrI[i]][arrI[i + 1]] -= max;
			if (MaxFlow[arrI[i]][arrI[i + 1]] == 0)
				Matrix[arrI[i]][arrI[i + 1]] = INT16_MAX;

			MaxFlow[arrI[i + 1]][arrI[i]] += max; // back rib
			if (MaxFlow[arrI[i + 1]][arrI[i]] != 0)
				Matrix[arrI[i + 1]][arrI[i]] = 1;
		}
		minWay = Bellman_Ford();
		if (minWay != nullptr)
		{
			//minWay->print_to_console();
			arrI = minWay->listInArr();
			dist = new int[minWay->get_size() - 1];
		}
	}
	int maxFlow = 0, maxFlow2 = 0;
	printMatrix();
	for (size_t i = 0; i < sizeMatrix; i++)
	{
		maxFlow2 += Flow[i][findCity('T')]; // at the drain
		maxFlow += Flow[findCity('S')][i]; // at the source
	}
	cout << endl << "Flow: "<< maxFlow << " = " << maxFlow2;
	return maxFlow;
}