#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "item.h"
#include "itemrent.h"
using namespace std;

//Class defiinition for the base class
class Customer
{
protected:
	string CustomerID;
	string CustomerName;
	string Address;
	string Phone_numb;
	string Customer_type;
	int borrow_numb;
	int points;
	Item_List* listOfRentals; // List of currently rented IDs
	bool canRentFree = false;
public:
	//Default constructor when initialize the object
	Customer() {
		borrow_numb = 0;
		listOfRentals = new Item_List();
		points = 0;
	}
	//Parameterized constructors
	Customer(string Customer_id, string Customer_name, string address, string phone, const string& borrow_numb, string Customer_type) {
		this->CustomerID = Customer_id;
		this->CustomerName = Customer_name;
		this->Address = address;
		this->Phone_numb = phone;
		this->borrow_numb = stoi(borrow_numb);
		this->Customer_type = Customer_type;
		this->listOfRentals = new Item_List();

	}
	~Customer() {}//Deconstructors and Getter function to return the value of that object
	string& get_Customer_id() { return this->CustomerID; }
	string& get_Customer_name() { return this->CustomerName; }
	string& get_Customer_address() { return this->Address; }
	string& get_Customer_phone() { return this->Phone_numb; }
	int& get_Customer_borrow() { return this->borrow_numb; }
	string& get_Customer_type() { return this->Customer_type; }
	Item_List* getListOfRentals() {
		return this->listOfRentals;
	}
	//Setter Functions
	void set_Customer_ID(string Customer_id) { this->CustomerID = Customer_id; }
	void set_Customer_name(string Customer_name) { this->CustomerName = Customer_name; }
	void set_Customer_address(string address) { this->Address = address; }
	void set_Customer_phone(string phone) { this->Phone_numb = phone; }
	void set_Customer_borrow(int borrow_quantities) { this->borrow_numb = borrow_quantities; }
	void set_Customer_type(string Customer_type) { this->Customer_type = Customer_type; }
	void appenTail(Item* value);
	//Another getter functions to get all the information of that customer
	string get_all_customer_information();


	// Print out all the information regarding that customer
	void display() {
		cout << get_all_customer_information() << endl;

		//Print all item which customer borrows
		int itemline = this->getListOfRentals()->ItemListSize(this->getListOfRentals());
		if (itemline != 0) {
			for (int i = 0; i < itemline; i++) {
				cout << this->getListOfRentals()->get(i) << endl;
			}
		}
	};

	//This function is to get the number of item that the customer has borrowed
	int get_customer_borrow_numb() {
		return this->borrow_numb;
	}
	void customer_promote();

	void customer_edit_options(int field, Customer& cus);
	int getPoints();
	//Renting function for the customer
	void rent();
	//The return for the customer
	void returnItem() {
		this->borrow_numb++;
	}

};
extern Customer CustomerNull;
//These are the 3 sub classes of the superclass "Customer" namely, "Regular", "Guest" and "VIP".

class Guest : public Customer {
public:
	//They only have 2 constructors to set the value, other setters and setters are already inheritted from the base class Customer
	Guest() : Customer() {
		this->Customer_type = "Guest";
	}

	Guest(string Customer_id, string Customer_name, string Customer_address, string Customer_phone, const string& number_of_item, string Customer_type)
		: Customer(Customer_id, Customer_name, Customer_address, Customer_phone, number_of_item, Customer_type) {
		this->Customer_type = "Guest";
	}
};

class Regular : public Customer {
public:
	//They only have 2 constructors to set the value, other setters and setters are already inheritted from the base class Customer
	Regular() : Customer() {
		this->Customer_type = "Regular";
	}

	Regular(string Customer_id, string Customer_name, string Customer_address, string Customer_phone, const string& number_of_item, string Customer_type)
		: Customer(Customer_id, Customer_name, Customer_address, Customer_phone, number_of_item, Customer_type) {
		this->Customer_type = "Regular";
	}
};

class VIP : public Customer {
public:
	//They only have 2 constructors to set the value, other setters and setters are already inheritted from the base class Customer
	VIP() : Customer() {
		this->Customer_type = "VIP";
	}

	VIP(string Customer_id, string Customer_name, string Customer_address, string Customer_phone, const string& number_of_item, string Customer_type)
		: Customer(Customer_id, Customer_name, Customer_address, Customer_phone, number_of_item, Customer_type) {
		this->Customer_type = "VIP";
	}
};
//This Customer_node is to wrap up all the data for the customer into one node, this will be useful when operate in a list.
class Customer_node
{
public:
	Customer data;
	Customer_node* next;
	// Default Constructors
	Customer_node() {
		next = nullptr;
	}
	//Constructors when the node is initialized
	Customer_node(Customer newData)
	{
		data = newData;
		next = nullptr;
	}
	Customer_node(Customer newData, Customer_node* nextNode)
	{
		data = newData;
		next = nextNode;
	}
	~Customer_node() {}//Deconstructor
	//Functions to get the node to the next node and also set the value of the pointer point to the next node
	Customer_node* getNext() { return next; }
	void setnext(Customer_node* newNext) { next = newNext; }
	Customer& getData() { return data; }
	Customer setData(Customer newData) { data = newData; }
	Customer_node* createNode(Customer newData);

};
//This is the class definition for the list of customer, however, it is different from the list of item.
class Customer_List
{

private: //Each list has 2 pointer to specify the head and the tail of the list
	Customer_node* head;
	Customer_node* tail;

public:

	//Deconstructor for the list of customer
	Customer_List() : head(NULL), tail(NULL)
	{}
	~Customer_List() {}

	//The following functions are the functionality of the list
	void createList(Customer_List& list);
	void insertHead(Customer_List& list, Customer_node* temp);
	void appenTail(Customer_List& list, Customer_node* temp);
	void appenTail(Customer* value);
	int CustomerLine(Customer_List list);
	Customer& get(int index_of_list)
	{
		int position = 0;
		// Begin from the list's head
		Customer_node* current = head;


		// Perfrom list traversal until the condition is met
		while (position < index_of_list && current != NULL)
		{
			current = current->next;
			position++;
		}

		// Check if there's an object at desirable index
		if (position == index_of_list)
		{
			return current->data;
		}//If we do not found the correct information, cout error

	}

	//Functions for the functionality of the menu
	void editOrDeleteItem(Customer_List& list);
	void add_Customer(Customer_List& list);
	void editCustomer(Customer_List& list);
	void Customer_ID_Sort(Customer_List& cus_list);
	void Customer_Name_Sort(Customer_List& cus_list);
	void Customer_ID_Search(Customer_List& cus_list);
	void Customer_Name_Search(Customer_List& cus_list);
	void print_customer_list(Customer_List list);
};