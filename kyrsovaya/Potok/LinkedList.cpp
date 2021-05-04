#include <iostream>
#include "Linkedlist.h"
#include  <stdexcept>
#include <string>

LinkedList::LinkedList(int Vertex1, int Vertex2) // creating a list WITH data
{
	head = new Node;
	head->Vertex1 = Vertex1;
	head->Vertex2 = Vertex2;
	tail = head;
	sizeList++;
}
LinkedList::LinkedList() // creating a list WITHOUT data
{
	tail = NULL;
	head = NULL;
	sizeList = 0;
}
LinkedList::~LinkedList()
{
	clear();
}
int LinkedList::at(size_t pos)
{
	if (isEmpty()) throw std::out_of_range("The list is empty");
	if (pos + 1 > sizeList) throw std::out_of_range("Index is greater than list size");
	else
	{
		Node* current = head;
		for (size_t position = 0; position < pos; position++) // go to the desired list position
		{
			current = current->next;
		}
		return current->Vertex1;
	}
}
bool LinkedList::find(int data)
{
	Node* current = head;
	while (current != nullptr)
	{
		if (current->Vertex2 == data)
		{
			return true;
		}
		current = current->next;
	}
	return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////// NEW
LinkedList* LinkedList::min_way()
{
	if (!isEmpty())
	{
		LinkedList* way = new LinkedList();
		Node* cur = tail;
		while (find(cur->Vertex1)) // among the Vertex2
		{
			way->push_back(cur->Vertex2, 0);
			cur = findNode(cur->Vertex1); // among the Vertex2
		}
		way->push_back(cur->Vertex2, 0);
		way->push_back(cur->Vertex1, 0);
		return way;
	}
	return nullptr;
}
int* LinkedList::listInArr()
{
	Node* cur = tail;
	int* arr = new int[get_size()];
	for (size_t i = 0; i < get_size(); i++)
	{
		arr[i] = cur->Vertex1;
		cur = cur->prev;
	}
	return arr;
}
LinkedList::Node* LinkedList::findNode(int data)
{
	Node* current = head;
	while (current != nullptr)
	{
		if (current->Vertex2 == data)
		{
			return current;
		}
		current = current->next;
	}
	return nullptr;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LinkedList::clear() // deleting all list items
{
	if (isEmpty());
	else
	{
		while (sizeList != 0)
		{
			pop_back();
		}
	}
}

size_t LinkedList::get_size()
{
	return sizeList;
}

bool LinkedList::isEmpty()
{
	if (sizeList == 0) return true;
	else return false;
}

void LinkedList::pop_back()
{
	if (sizeList == 0) throw std::out_of_range("The list is empty");
	else if (sizeList == 1)
	{
		delete tail;
		sizeList--;
	}
	else // if SizeList != 0,1
	{
		Node* current = tail;
		current->prev->next = NULL;
		tail = current->prev;
		delete current;
		sizeList--;
	}
}

void LinkedList::pop_front()
{
	if (isEmpty()) throw std::out_of_range("The list is empty");
	else if (sizeList == 1)
	{
		delete head;
		sizeList--;
	}
	else // if SizeList != 0,1
	{
		Node* current = head;
		head = current->next;
		current->next->prev = NULL;
		delete current;
		sizeList--;
	}
}

void LinkedList::print_to_console()
{
	if (isEmpty())
	{
		std::cout << "\n\"The list is empty\"\n";
	}
	else
	{
		Node* current = head;
		for (size_t position = 0; position < sizeList; position++)
		{
			std::cout << current->Vertex1 << current->Vertex2 << " ";
			current = current->next;
		}
	}
}

void LinkedList::push_back(int Vertex1, int Vertex2)
{
	if (isEmpty()) // if the list is empty
	{
		head = new Node;
		head->Vertex1 = Vertex1;
		head->Vertex2 = Vertex2;
		tail = head;
	}
	else
	{
		tail->next = new Node;
		tail->next->prev = tail;
		tail = tail->next;
		tail->Vertex1 = Vertex1;
		tail->Vertex2 = Vertex2;
	}
	sizeList++;
}

void LinkedList::remove(size_t pos)
{
	if (sizeList == 0) throw std::out_of_range("The list is empty");
	if (pos + 1 > sizeList) throw std::out_of_range("Index is greater than list size");
	else
	{
		if (pos == 0) // if this is the first element
		{
			pop_front();
		}
		else if (pos == sizeList - 1) // if this is the last element
		{
			pop_back();
		}
		else
		{
			Node* current = head;
			for (size_t position = 0; position < pos; position++) // go to the desired list position
			{
				current = current->next;
			}
			current->prev->next = current->next; // replacement of pointer (next)
			current->next->prev = current->prev; // replacement of pointer (prev)
			delete current;
			sizeList--;
		}
	}
}