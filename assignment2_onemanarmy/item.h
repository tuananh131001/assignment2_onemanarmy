#pragma once

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Create new class for item
class Item
{
protected:
	string itemId, title, rentType, loan, genre;
	int num_copy = 0;
	double fee = 0;
	bool available = false;
public:
	Item() {} // Item Construction
	Item(string itemId, string title, string rentType, string loan, string num_copy, string fee, string genre)
	{
		this->itemId = itemId;
		this->title = title;
		this->rentType = rentType;
		this->loan = loan;
		this->genre = genre;
		this->num_copy = stoi(num_copy);
		this->available = this->num_copy > 0;
		this->fee = stod(fee);
	}
	~Item() {} // Item Destruction

	// Getter functions used for item 
	string& getItemId() { return this->itemId; } //ID getter
	string& getTitle() { return this->title; } //Title getter
	string& getRentType() { return this->rentType; } //RentType getter
	string& getLoan() { return this->loan; } //Loan getter
	int& getCopy() { return this->num_copy; } //Copy getter
	double& getFee() { return this->fee; } // Fee getter
	string& getGenre() { return this->genre; } // Genre getter for DVD or Record

	// Setter functions used for item
	void setItemId(string itemId) { this->itemId = itemId; } // ID setter
	void setTitle(string title) { this->title = title; } //Title Setter
	void setFee(double fee) { this->fee = fee; } // Fee Setter
	void setCopy(int num_copy) { this->num_copy = num_copy; } // Copy Setter
	void setLoan(string loan) { this->loan = loan; } // Loan setter
	void setRentType(string rentType) { this->rentType = rentType; } // RentType setter
	void setGenre(string genre) { this->genre = genre; } // Genre setter for DVD or Record


	void updateItemMenu(int field, Item& item); // Function to update item menu
	void display(); // Function to display all object in item

	// Return item store in string to input/ouput file
	string getItemString()
	{
		string s = to_string(this->fee);
		size_t found = s.find(".");
		s = s.substr(0, found + 3);

		if (this->rentType != "Game")
		{
			string ret = this->itemId + "," + this->title + "," + this->rentType + "," + this->loan + "," +
				to_string(this->num_copy) + "," + s + "," + this->genre;
			return ret;
		}
		else
		{
			string ret = this->itemId + "," + this->title + "," + this->rentType + "," + this->loan + "," +
				to_string(this->num_copy) + "," + s;
			return ret;
		}
	}

	// Check whether item is available
	bool checkAvailable()
	{
		return this->available;
	}

	// Get rent item and decrease in stock quantity
	void getRented()
	{
		this->num_copy--;
		this->available = num_copy > 0;
	}

	// Get return item and increase in stock quantity
	void getReturned()
	{
		this->num_copy++;
		this->available = num_copy > 0;
	}

	// Check if the item is available in stock
	void setAvailable()
	{
		this->available = true;
	}

};

// Create new class record inheritance from item
class Record : public Item
{
public:
	Record() : Item()
	{
		this->rentType = "Record";
	}

	Record(string itemId, string title, string type, string loan, string num_copy, string fee, string genre) :
		Item(itemId, title, type, loan, num_copy, fee, genre)
	{
		this->rentType = "Record";
		this->genre = genre;
	}

};

// Create new class DVD inheritance from item
class DVD : public Item
{
public:
	DVD() : Item()
	{
		this->rentType = "DVD";
	}

	DVD(string itemId, string title, string type, string loan, string num_copy, string fee, string genre) :
		Item(itemId, title, type, loan, num_copy, fee, genre)
	{
		this->rentType = "DVD";
		this->genre = genre;
	}

};

// Create new class Game inheritance from item
class Game : public Item
{
public:
	Game() : Item()
	{
		this->rentType = "Game";
	}

	Game(string itemId, string title, string type, string loan, string num_copy, string fee, string genre) :
		Item(itemId, title, type, loan, num_copy, fee, genre)
	{
		this->rentType = "Game";
	}
};

// Generate node applied to item
class Node
{
private:
	Item data;
	Node* next;
public:

	Node()
	{
		this->data = data;
		next = nullptr;
	}
	Node(Item newData)
	{
		data = newData;
		next = nullptr;
	}
	Node(Item newData, Node* nextNode)
	{
		data = newData;
		next = nextNode;
	}
	~Node() {}

	Node* getNext() { return next; }
	void setNext(Node* newNext) { next = newNext; }
	Item& getData() { return data; }
	Item setData(Item newData) { data = newData; }
	Node* createNode(Item newData);


};

// Generate Linklist applied to item
class LinkedList
{
private:
	Node* head;
	Node* tail;
public:
	LinkedList() : head(NULL), tail(NULL)
	{}
	~LinkedList() {}


	void createList(LinkedList& list);
	void insertHead(LinkedList& list, Node* temp);
	void appenTail(LinkedList& list, Node* temp);
	void appenTail(Item* value);
	//void printAll(LinkedList list);
	int CountItem(LinkedList* list);

	void printAllItemList(LinkedList* list);

	void add_Game(LinkedList& list);
	void add_DVD_Record(LinkedList& list);
	void deleteItem(LinkedList list);

	void searchById(LinkedList list);
	void searchByTitle(LinkedList list);
	void writeOneLine(ostream& file, Item& item);
	void writeAllLine(LinkedList& list);
	void deleteLinkedList(LinkedList& list);
	void updateItem(LinkedList& itemList);
	void printOutOfStock(LinkedList& list);
	void sortedById(LinkedList& list);
	void sortedByTitle(LinkedList& list);

	Item& get(int index)
	{
		int pos = 0;

		// Begin at list head
		Node* current = head;

		// Running through list until reach the desired index
		while (pos < index && current != NULL)
		{
			current = current->getNext();
			pos++;
		}

		// Check whether object available at the index
		if (pos == index)
		{
			return current->getData();
		}
		else
		{ // if not print out error
			cerr << "Index not found" << endl;
		}
		return current->getData();
	}
};



