#pragma once
#pragma once
#include <string>

class LinkedList
{
private:
	struct Node // Node List
	{
		Node(int A = ' ', int B = ' ', Node* prev = nullptr, Node* next = nullptr)
		{
			this->next = next;
			this->prev = prev;
			this->A = A;
			this->B = B;
		};
		int A;
		int B;
		Node* next; // next element
		Node* prev; // previous element
	};
	size_t sizeList;
	Node* head;
	Node* tail;

	/*int* minWay;
	size_t sizeway;*/
public:
	LinkedList(int A, int B); // creating a list WITH data
	LinkedList(); // creating a list WITHOUT data
	~LinkedList();

	void push_back(int A, int B);			 // 1 // add lust element
	//void push_front(int data);			 // 2 // add front element
	void pop_back();					 // 3 // del lust element
	void pop_front();					 // 4 // del front element
	void insert(int data, size_t pos);   // 5 // add by index 
	int at(size_t pos);					 // 6 // getting by index


	///////////////////////////////////////////////////////////NEW METHODS
	bool find(int); // find B
	Node* findNode(int); // findNode B
	LinkedList* min_way();
	int* listInArr();
	/*size_t size_way() { return sizeway; };
	int* min_way_arr() { return minWay; };*/
	///////////////////////////////////////////////////////////

	void remove(size_t pos);			 // 7 // del by index
	size_t get_size();					 // 8 // getting size List
	void print_to_console();			 // 9 // print to console
	void clear();						 // 10// clear list
	void set(int data, size_t pos);		 // 11// swap data
	bool isEmpty();						 // 12// checking if the list is empty
	void reverse();						 // 13// reverse
};