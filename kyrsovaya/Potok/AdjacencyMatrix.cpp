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
	getline(file, str); // count cities
	sizeMatrix = atoi(str.c_str());
	Matrix = new int* [sizeMatrix];
	MaxPotok = new int* [sizeMatrix];
	Potok = new int* [sizeMatrix];
	for (size_t i = 0; i < sizeMatrix; i++)
	{
		Matrix[i] = new int[sizeMatrix];
		MaxPotok[i] = new int[sizeMatrix];
		Potok[i] = new int[sizeMatrix];
	}
	for (size_t i = 0; i < sizeMatrix; i++)
		for (size_t j = 0; j < sizeMatrix; j++)
		{
			Potok[i][j] = 0;
			MaxPotok[i][j] = 0;
			if (i == j) Matrix[i][j] = 0; // cityA -> cityA = 0
			else Matrix[i][j] = INT16_MAX;
		}
	Cities = new char[sizeMatrix];
	for (unsigned int i = 0; i < sizeMatrix; i++)
		Cities[i] = ' ';
};
unsigned int AdjacencyMatrix::findCity(char City)
{
	for (unsigned int i = 0; i < sizeMatrix; i++)
	{
		if (Cities[i] == City) return i;
	}
	return -1;
}
unsigned int AdjacencyMatrix::findNewIndex(char City)
{
	for (unsigned int i = 0; i < sizeMatrix; i++)
	{
		if (Cities[i] == ' ') return i;
	}
	return -1;
}
void AdjacencyMatrix::printMatrix()
{
	cout << endl << "  ";
	for (size_t i = 0; i < sizeMatrix; i++)
	{
		cout << Cities[i] << "        ";
	}
	cout << endl;
	for (size_t i = 0; i < sizeMatrix; i++)
	{
		cout << Cities[i] << " ";
		for (size_t j = 0; j < sizeMatrix; j++)
		{
			if (Matrix[i][j] == INT16_MAX) { cout << "-"; }
			else cout << Matrix[i][j];
			cout << "(" << Potok[i][j] << "/" << MaxPotok[i][j] << ")   ";
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
		char CityA, CityB;
		unsigned int IndexA, IndexB;
		string dist;
		getline(file, str);
		unsigned int i = 0;
		///////////////////////////////////////////////////////////////// city A
		CityA = str[i];
		i+=2;
		if (findCity(CityA) == -1)
		{
			IndexA = findNewIndex(CityA);
			Cities[IndexA] = CityA;
		}
		else
		{
			IndexA = findCity(CityA);
			Cities[IndexA] = CityA;
		}
		if (i >= str.length()) throw out_of_range("incorrect input");
		///////////////////////////////////////////////////////////////// city B
		CityB = str[i];
		i+=2;
		if (findCity(CityB) == -1)
		{
			IndexB = findNewIndex(CityB);
			Cities[IndexB] = CityB;
		}
		else
		{
			IndexB = findCity(CityB);
			Cities[IndexB] = CityB;
		}
		if (i >= str.length()) throw out_of_range("incorrect input");
		///////////////////////////////////////////////////////////////// AB
		while (i != str.length())
		{
			dist.push_back(str[i]);
			i++;
		}
		Matrix[IndexA][IndexB] = 1;
		MaxPotok[IndexA][IndexB] = atoi(dist.c_str());
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
	char cityA = 'S', cityB = 'T';
	int* minWay = new int[sizeMatrix];
	int* labels = new int[sizeMatrix];
	for (unsigned int i = 0; i < sizeMatrix; i++)
	{
		minWay[i] = INT16_MAX;
	}minWay[findCity(cityA)] = 0;
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
	/*if (minWay[findCity(cityB)] == INT16_MAX)
	{
		cout << endl << "There is no way from " << Cities[findCity(cityA)] << " to " << Cities[findCity(cityB)];
		return 0;
	}
	else
	{
		cout << endl << "The optimal way from " << Cities[findCity(cityA)] << " to " << Cities[findCity(cityB)] << " is " << minWay[findCity(cityB)];
	}*/
	if (minWay[findCity(cityB)] == INT16_MAX) return nullptr;
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
			dist[i] = MaxPotok[arrI[i]][arrI[i + 1]];

		max = minimum(dist, minWay->get_size() - 1);
		for (size_t i = 0; i < minWay->get_size() - 1; i++)
		{
			Potok[arrI[i]][arrI[i + 1]] += max;
			Potok[arrI[i + 1]][arrI[i]] -= max;

			MaxPotok[arrI[i]][arrI[i + 1]] -= max;
			if (MaxPotok[arrI[i]][arrI[i + 1]] == 0)
				Matrix[arrI[i]][arrI[i + 1]] = INT16_MAX;

			MaxPotok[arrI[i + 1]][arrI[i]] += max; // back rib
			if (MaxPotok[arrI[i + 1]][arrI[i]] != 0)
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
	int maxPotok = 0, maxPotok2 = 0;
	printMatrix();
	for (size_t i = 0; i < sizeMatrix; i++)
	{
		maxPotok2 += Potok[i][findCity('T')]; // at the drain
		maxPotok += Potok[findCity('S')][i]; // at the source
	}
	cout << endl << "Potok: "<< maxPotok << " = " << maxPotok2;
	return maxPotok;
}