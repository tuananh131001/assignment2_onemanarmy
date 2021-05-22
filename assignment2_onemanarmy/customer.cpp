#include "Customer.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
//Declare function to check for the duplicated customer
bool isDuplicateNewCustomer(Customer* t, Customer_List* list);

//Create the node for the list
Customer_node* Customer_node::createNode(Customer newData)
{
	Customer_node* temp = new Customer_node;
	if (temp == nullptr) {
		cout << "Failed." << endl;
		throw(temp);
	}
	temp->data = newData;
	temp->setnext(nullptr);
	return temp;
}
//Creating the list
void Customer_List::createList(Customer_List& list)
{
	list.head = nullptr;
	list.tail = nullptr;
}
//Function to insert the node at the begining of the list
void Customer_List::insertHead(Customer_List& list, Customer_node* temp)
{   //If list is empty then head is equal to tail
	if (list.head == nullptr)
	{
		list.head = list.tail = temp;
	}
	else
	{
		temp->setnext(head);
		list.head = temp;
	}
}
//Function to add the customer at the end of the list
void Customer_List::appenTail(Customer_List& list, Customer_node* temp)
{
	if (list.head == nullptr)
	{
		list.head = temp;
		list.tail = temp;
	}
	else
	{
		list.tail->setnext(temp);
		list.tail = temp;
	}
}
//Another overloaded functions that take in the value of the customer only
void Customer_List::appenTail(Customer* value)
{
	Customer_node* tmp = new Customer_node(*value);
	// If list empty, appended node is head
	if (head == NULL) {
		head = tmp;
		tail = tmp;
	}
	else {
		tail->setnext(tmp);
		tail = tmp;
	}

}
//Print customers
void Customer_List::print_customer_list(Customer_List list)
{
	if (list.CustomerLine(list) > 0) {
		for (int i = 0; i < list.CustomerLine(list); i++)
		{
			list.get(i).display();
		}
	}
	else
		cout << "List is empty" << endl;
}

//Function to count for the number of customer in the Customer_List linked list
int Customer_List::CustomerLine(Customer_List list)
{
	int line = 0;
	for (Customer_node* point = list.head; point != NULL; point = point->getNext())
	{
		line++;

	}
	// return the line in the list
	return line;

}
//Function to get the input from the shop owner whether he wants to add new customer, edit customer or search of the desired customer
//The following functions will have the same functionality
//The ID can only contain 4 character, with the C and the 3 unique digit numbers
void input_ID(Customer& object)
{
	string ID;
	cout << "Enter Customer ID: ";
	cin >> ID;
	int i = 0;
	//The loop to check whether the owner's input is correct or not, if it is correct, then the loop will break and we will choose that value for the customer
	while (1)
	{
		if (strlen(ID.c_str()) > 4) {
			cout << "wrong format, the id format is Cxxx and xxx is the 3 digits !" << endl;
			cout << "Enter again: ";
			cin >> ID;
		}
		if (ID.at(0) == 'C' && isdigit(ID.at(1)) && isdigit(ID.at(2)) && isdigit(ID.at(3)))
		{
			object.set_Customer_ID(ID);
			break;
		}

		else
		{
			cout << "Wrong ID format, only Cxxx is allowed ! " << endl;
			cout << "Enter again: ";
			cin >> ID;
		}

	}
}
//Functions to receive the name input from the user, the name is only invalid when it is left blank
void input_name(Customer& object)
{
	cin.ignore();
	cout << "Enter Customer name: ";
	while (true)
	{
		string newName;
		getline(cin, newName);
		if (!newName.empty())
		{
			object.set_Customer_name(newName);
			break;
		}
		else
			cout << "Error: invalid name. Enter again: ";
	}
}
//User will input the address for the customer through this functions, it accepts normal words, capital words and numbers only
void inputAddress(Customer& object)
{
	string Customer_address;
	int i = 0;
	cout << "Enter the address: ";
	getline(cin, Customer_address);
	//Here we will do the same thing, we have a loop to continuously checking for the value, if it's correct, then we set the value for the customer and stop the loop
	while (1) {
		//If the character is true, which is only normal, capital and numbers, then we move to the next string index
		if ((Customer_address[i] <= 122 && Customer_address[i] >= 97) || (Customer_address[i] <= 90 && Customer_address[i] >= 65) || (Customer_address[i] == ' ' || (Customer_address[i] >= 48 && Customer_address[i] <= 57))) {
			i++;
			//if all the previous string index is true and the string is at null character, then it's true !, we set the value and then stop the loop
			if (Customer_address[i] == '\0') {
				object.set_Customer_address(Customer_address);
				break;
			}
		}
		//if it has weird value like %$#@#$_+, then we will ask for the owner to type again and check for that value again
		else {
			cout << "Abnormal character detected!, only alphabets and numbers are accepted " << endl;
			cout << "Enter the address again: ";
			getline(cin, Customer_address);
		}
	}
}

//Now is the phone information input
void input_phone(Customer& object)
{
	string phone_number;
	cout << "Enter phone number: ";
	cin >> phone_number;
	int i = 0;
	//Likewise, we will loop from the beginning till the end, check if it is a digit, then we move on, if it's not then we ask the owner to type again
	while (1) {
		if (isdigit(phone_number[i])) {
			i++;
			if (phone_number[i] == '\0') {
				object.set_Customer_phone(phone_number);
				break;
			}
		}
		else {
			cout << "Wrong phone number format, only number is allowed ! " << endl;
			cout << "Enter again: ";
			cin >> phone_number;
		}

	}

}
//Input for the customer level is simple, if the owner do not type in correctly, which is "VIP", "Regular" and "Guest, then it shows error
//And ask the owner to type in again.
void input_Customer_type(Customer& object)
{
	string Customer_type = "Guest";
	object.set_Customer_type(Customer_type);
}

//This is the function to add the customer at the end of the list
void Customer_List::add_Customer(Customer_List& list)
{
	//First we create a new customer to load in the data
	Customer cus;
	Customer_node node;
	//Then we do malloc for another new customer to be sent in the list later
	Customer_node* temp = new Customer_node();
	//Ask for ID
	input_ID(cus);
	//Ask for name
	input_name(cus);
	//Ask for address
	inputAddress(cus);
	//Ask for phone number
	input_phone(cus);
	//Ask for the level of the customer
	input_Customer_type(cus);
	////Ask for the number of item that the customer wants to borrow
	//input_borrowing_number(cus);
	//Then we create the node inside the list of customer that has the value from the variable "cus" previously and load the value
	temp = node.createNode(cus);
	//Finally, we concatenate the customer at the end of the list of customer and check duplicate.
	if (!isDuplicateNewCustomer(&cus, &list))
	{
		cout << "Added: ";
		list.appenTail(list, temp);
		cus.display();
	}
	else
	{
		// Else, free memory
		cout << "Duplicate ID, customer will not be added" << endl;
		delete temp;
	}
}

//Function to get all the related information of that customer, this will be useful when display out on the console
string Customer::get_all_customer_information()
{
	string ret = CustomerID + "," + CustomerName + "," + Address + "," + Phone_numb + ","
		+ to_string(borrow_numb) + "," + Customer_type;

	if (this->Customer_type == "VIP")
		ret = ret + "," + to_string(this->points);

	return ret;
};

//Functions for renting the item, it is only for the VIP customer since they have stacked points
int Customer::getPoints()
{
	return this->points;
}

//Renting function for the customer class, overloading for the VIP class since they have points
void Customer::rent() {
	if (this->Customer_type == "VIP") {
		canRentFree = this->points >= 100;

		if (canRentFree) {
			// Reset points after rent
			cout << "This VIP just rent this item for free!" << endl;
			this->canRentFree = false;
			this->points -= 100;
		}
		else {
			this->points += 10;
		}
	}
}

//Functions to promote the customer, we will change the customer_type string in the data of that customer
void Customer::customer_promote() {

	//Since we only care if they are a Guest or a Regular
	//If they are a Guest, then their customer_type string will be change to Regular
	if (this->Customer_type == "Guest") {
		this->Customer_type = "Regular";
		cout << "Customer is now a Regular type" << endl;
	}

	else if (this->Customer_type == "Regular") {
		this->Customer_type = "VIP";
		cout << "Congratulations, you are a VIP customer :) " << endl;
	}
	//And if they dont, meaning that they already a VIP customer, then we do nothing
	else {
		return;
	}

	this->borrow_numb = 0;
}


int getCusEditGuide() {

	cout << "Edit this Customer" << endl;

	int function = 1;
	return function;
}
// Helper to print edit menu
int getCustomerEditFieldMenu()
{
	while (true)
	{
		cout << "Enter an option:" << endl
			<< "1. Edit ID" << endl
			<< "2. Edit name" << endl
			<< "3. Edit address" << endl
			<< "4. Edit phone" << endl
			<< "5. Quit editing" << endl;

		int field = 0;
		cout << endl;
		cout << "Enter your choice: ";
		cin >> field;
		return field;
	}
}
//This function is to allows onwer to edit the customer information
void Customer::customer_edit_options(int type, Customer& cus)
{
	switch (type)
	{
	case 1:
	{
		input_ID(cus);//Change the customer ID
		break;
	}
	case 2:
	{
		input_name(cus);//Change the customer name
		break;
	}
	case 3:
	{
		inputAddress(cus);//Change customer's address
		break;
	}
	case 4:
	{
		input_phone(cus);//Change customer's phone number
		break;
	}
	default:;
	}//Then show out what informations have been editted
	cout << "Edited customer: " << cus.get_all_customer_information() << endl;
}
//Check Edited Customer
bool isDuplicateEditedObject(Customer* t, Customer_List* list, int index) {
	int listSize = list->CustomerLine(*list);
	if (listSize > 0) {
		for (int i = 0; i < listSize; i++) {
			if (i != index) {
				Customer& tmp = list->get(i);
				// Validate unique xxx
				if (t->get_Customer_id().substr(1, 3) == tmp.get_Customer_id().substr(1, 3))
					return true;
			}
		}
		return false;
	}
	return false;
}
//Function to edit the information of the customer
void Customer_List::editCustomer(Customer_List& list) {
	string id;
	int listSize = list.CustomerLine(list);
	bool indicator = false;

	//Ask for the id input of desired customer
	cout << "Enter the targeted Customer's ID (xxx): ";
	cin >> id;



	// If list is not empty, then we loop until we found desired value
	if (listSize != 0) {
		//Now start with the first customer till the last customer
		for (int i = 0; i < listSize; i++) {
			Customer& tmp = list.get(i);
			//if the id match the customer in the list, we ask them
			//which aspect that they want to edit
			//this will use the customer_edit_options function
			if (id == tmp.get_Customer_id().substr(1, 3)) {
				indicator = true;
				string oldId = tmp.get_Customer_id();

				cout << "Selected item: ";
				//According to the options of the customer after they have looked in the edit options, we will perform that actions
				int function = getCusEditGuide();
				int choice = getCustomerEditFieldMenu();
				//Call out the function edit customer to edit their information
				tmp.customer_edit_options(choice, tmp);
				//If there is a duplicated customer inside the list
				//no information will be editted
				if (isDuplicateEditedObject(&tmp, &list, i)) {
					cout << "New ID is duplicate, revert to the old ID" << endl;
					tmp.set_Customer_ID(oldId);
					cout << "Edited: ";
					tmp.display();
				}
			}
		}//If the owner type in the wrong ID, error is shown
		if (!indicator)
			cout << "ID not found" << endl;
	}
}
//Display list of customers that sorted by ID
void Customer_List::Customer_ID_Sort(Customer_List& cus_list)
{
	//Create a customer node then we traverse through the list
	Customer_node* current = cus_list.head;
	//2 Loop to swap the id of the customer when we display
	//This is similar to the swap functions, if the next id is smaller than the previous one, we put it on the top when display
	for (Customer_node* current = cus_list.head; current != nullptr; current = current->getNext())
	{
		for (Customer_node* temp = current->getNext(); temp != nullptr; temp = temp->getNext())
		{
			if (current->getData().get_Customer_id() > temp->getData().get_Customer_id())
			{
				//Perform the swap
				swap(current->getData(), temp->getData());
			}
		}
	}
	//After that, we print out the customer list
	print_customer_list(cus_list);
	cout << endl;
}
//Display list of customers that sorted by name
void Customer_List::Customer_Name_Sort(Customer_List& cus_list)
{
	//Similar to the id sort, we also utilize 2 loops and swap the data of the customer when display
	Customer_node* current = cus_list.head;
	for (Customer_node* current = cus_list.head; current != nullptr; current = current->getNext())
	{
		for (Customer_node* temp = current->getNext(); temp != nullptr; temp = temp->getNext())
		{//Compare the string using stricmp functions,
		//allows to compare without cases sensitive, if the name is longer than the previous name, we place them on the top
			if (_stricmp(current->getData().get_Customer_name().c_str(), temp->getData().get_Customer_name().c_str()) > 0)
			{
				swap(current->getData(), temp->getData());
			}
		}
	}
	//Then we print out the list of customer
	print_customer_list(cus_list);
	cout << endl;
}
//Display the customer according to the search of the ID number
void Customer_List::Customer_ID_Search(Customer_List& cus_list)
{
	string searchId;//variable to hold the id of the customer
	//that we want to find
	cout << "Enter the Customer's ID you want to find(Cxxx): ";
	cin >> searchId;
	Customer customer;
	Customer_node* temp = cus_list.head;
	bool found = false;
	if (temp == NULL)
	{
		cerr << "Customer's ID is not existed ." << endl;
		exit(EXIT_FAILURE);
	}
	//loop through the list of customer
	while (temp != NULL)
	{
		customer = temp->getData();
		//if the right customer id is found, then we show them the information of that customer
		if (customer.get_Customer_id().compare(searchId) == 0)
		{
			customer.display();
			found = true;
		}
		temp = temp->getNext();
	}//if there is no customemr, then we show an error
	if (!found)
	{
		cerr << "Customer's ID not found." << endl;
	}
}
//Display list of customers which fit the title
void Customer_List::Customer_Name_Search(Customer_List& cus_list)
{
	//Similar to the ID search, we have a string variable to hold the name
	string searchTitle;
	Customer customer;
	Customer_node* temp = cus_list.head;
	bool found = false;
	cout << "Enter the customer's full name you want to find: ";
	cin.ignore();
	getline(cin, searchTitle);//Get the user input
	if (temp == NULL)
	{
		cerr << "Customer name is not existed." << endl;
		exit(EXIT_FAILURE);
	}
	else
	{   //Now we loop through the customer list and find the name
		while (temp != NULL)
		{
			customer = temp->getData();
			//If right name is found, we display the information of that customer
			if (_stricmp(customer.get_Customer_name().c_str(), searchTitle.c_str()) == 0)
			{
				found = true;
				customer.display();//Show the name
			}
			temp = temp->getNext();//Move to next customer
		}
	}//And if we cant find the name of that customer, we show an error
	if (!found)
	{
		{
			cerr << "Customer is not found." << endl;
		}
	}
}