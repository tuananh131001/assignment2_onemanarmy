#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "item.h"

//Create the node for the rented items
class Item_Rent_Node
{
private:
	string data;
	Item_Rent_Node* next;
public:
	Item_Rent_Node() // Constructor implementation
		: next(NULL)
	{}
	Item_Rent_Node(string newData)
	{
		data = newData;
		next = nullptr;
	}
	Item_Rent_Node(string newData, Item_Rent_Node* nextNode)
	{
		data = newData;
		next = nextNode;
	}
	~Item_Rent_Node() {} // Destructor implementation
	string& getData() { return this->data; } //Getters for the class
	Item_Rent_Node* getNext() { return next; } //Get the next node
	void setNext(Item_Rent_Node* newNext) { next = newNext; } //Set the value for the next node
};

//Create the rented item linked list
class Item_List
{
private:
	Item_Rent_Node* head;
	Item_Rent_Node* tail;
public:

	Item_List() : head(NULL), tail(NULL)
	{}
	~Item_List() {}

	void appenTail(string* value);
	void PrintDataInNode(Item_List* list);
	int PrintAllItemNode(Item_List* list);
	int ItemListSize(Item_List* list);

	string get(int index)
	{
		int pos = 0;

		// Set current node as the head of the list

		Item_Rent_Node* current = head;

		// Find the position of the desirable node
		while (pos < index && current != NULL)
		{
			current = current->getNext();
			pos++;
		}

		// Check if there's an item at desirable position
		if (pos == index)
		{
			return (current ? current->getData() : "Error");
		}
		else
		{
			cerr << "Index not found" << endl;
			return "error";
		}
	}
	// Delete first node in list
	void deleteHead()
	{
		Item_Rent_Node* tmp;
		tmp = head;
		head = head->getNext();
		delete tmp;
	}

	// Delete last node in list
	void deleteTail()
	{
		Item_Rent_Node* current = head;
		Item_Rent_Node* previous = new Item_Rent_Node();

		while (current->getNext() != NULL) {
			previous = current;
			current = current->getNext();
		}
		tail = previous;
		previous->setNext(NULL);
		delete current;
	}

	// Delete a node in a given position
	void deleteNode(int pos, int sizelist)
	{
		if (pos == 0) return deleteHead(); //delete node at the beginning
		if (pos == sizelist - 1) return deleteTail(); //delete node at the end
		if (pos >= sizelist) return;    // Out of the list

		auto* current = head;

		//Go to the previous of the desirable node
		for (int i = 0; current != NULL && i < pos - 1; i++)
		{
			current = current->getNext();
		}
		if (current == NULL || current->getNext() == NULL) return;

		// Delete node at desired position (next of current)
		Item_Rent_Node* tmp = current->getNext()->getNext(); // Store the next node after the deleted node
		free(current->getNext());   // Free memory at targeted node
		current->setNext(tmp);   // Connect preivous node and next one of the deleted node
	}

};