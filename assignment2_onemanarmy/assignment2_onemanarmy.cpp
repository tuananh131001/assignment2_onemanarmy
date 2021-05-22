#include <iostream>
#include <fstream>
#include <string>
#include "item.h"
#include "Customer.h"

using namespace std;

const int EXIT = 999;

LinkedList list;
Customer_List cus_list;

Item item;
Node* node;

// Declare Function Here
void rentItem(LinkedList* itemList, Customer_List* customerList);
void returnItem(LinkedList* itemList, Customer_List* customerList);
void printAllCustomerByType(Customer_List cusList);
void checkAllSpaceItem(string id, string loan, string copy, string fee, string genre);
void checkAllSpaceCustomer(string id, string phone_num, string address, string past_borrow);

bool isDuplicateNewCustomer(Customer* t, Customer_List* list);
bool isDuplicateNewItem(Item* t, LinkedList* list);


void menu()
{
	string choice;
	string itemId, title, type, loan, num_copy, fee, genre;
here:
	cout << "Welcome to Genie\'s video store" << endl;
	cout << "Enter an option below" << endl;
	cout << "1. Add a new game item" << endl;
	cout << "2. Add a DVD or Record item" << endl;
	cout << "3. Delete an item" << endl;
	cout << "4. Update an item" << endl;
	cout << "5. Search an item by ID" << endl;
	cout << "6. Search an item by title" << endl;
	cout << "7. Display all item" << endl;
	cout << "8. Display ths list of items sorted by ID" << endl;
	cout << "9. Display ths list of items sorted by Title" << endl;
	cout << "10. Display Item Out Of Stocks" << endl;
	cout << "_____________________________________" << endl;
	cout << endl;
	cout << "11. Add a new Customer" << endl;
	cout << "12. Update a Customer" << endl;
	cout << "13. Display ths list of customers sorted by ID" << endl;
	cout << "14. Display ths list of customers sorted by name" << endl;
	cout << "15. Display the list of customers by Customer Type" << endl;
	cout << "16. Display all Customer" << endl;
	cout << "_____________________________________" << endl;
	cout << "17. Rent an Item" << endl;
	cout << "18. Return an Item" << endl;
	cout << "19. Search an customer by Customer ID" << endl;
	cout << "20. Search an customer by Customer Name" << endl;
	cout << "Exit" << endl;
	cout << "Enter your choice: ";

	cin >> choice;
	if (choice == "1")
	{
		system("cls");
		list.add_Game(list);
		goto here;
	}
	else if (choice == "2")
	{
		system("cls");
		list.add_DVD_Record(list);
		goto here;
	}
	else if (choice == "3") {

		system("cls");
		list.deleteItem(list);
		goto here;
	}
	else if (choice == "4")
	{
		system("cls");
		list.updateItem(list);
		goto here;
	}
	else if (choice == "5")
	{
		system("cls");
		list.searchById(list);
		goto here;
	}
	else if (choice == "6")
	{
		system("cls");
		list.searchByTitle(list);
		goto here;
	}
	else if (choice == "7") {
		system("cls");

		list.printAllItemList(&list);
		goto here;
	}
	else if (choice == "8")
	{
		system("cls");
		list.sortedById(list);
		goto here;
	}
	else if (choice == "9")
	{
		system("cls");
		list.sortedByTitle(list);
		goto here;
	}
	else if (choice == "10")
	{
		system("cls");
		list.printOutOfStock(list);
		goto here;
	}
	else if (choice == "11")
	{
		system("cls");
		cus_list.add_Customer(cus_list);
		goto here;
	}
	else if (choice == "12")
	{
		system("cls");
		cus_list.editCustomer(cus_list);
		goto here;
	}
	else if (choice == "13")
	{
		system("cls");
		cus_list.Customer_ID_Sort(cus_list);
		goto here;
	}
	else if (choice == "14")
	{
		system("cls");
		cus_list.Customer_Name_Sort(cus_list);
		goto here;
	}
	else if (choice == "15")
	{
		system("cls");
		printAllCustomerByType(cus_list);
		cout << endl;
		goto here;
	}
	else if (choice == "16")
	{
		system("cls");
		cout << "Total Customer: " << cus_list.CustomerLine(cus_list) << endl;
		cus_list.print_customer_list(cus_list);
		cout << endl;
		goto here;
	}
	else if (choice == "17")
	{
		system("cls");
		rentItem(&list, &cus_list);
		goto here;
	}
	else if (choice == "18")
	{
		system("cls");
		returnItem(&list, &cus_list);
		cout << endl;
		goto here;
	}
	else if (choice == "19")
	{
		system("cls");
		cus_list.Customer_ID_Search(cus_list);
		goto here;
	}
	else if (choice == "20")
	{
		system("cls");
		cus_list.Customer_Name_Search(cus_list);
		cout << endl;
		goto here;
	}
	else if (choice == "Exit" || choice == "EXIT")
	{
		cout << "Program End. Goodbye." << endl;
	}
	else
	{
		cout << "Invalid choice. please enter again." << endl;
		cout << endl;
		goto here;
	}
}


/*---------------FILE I/O-----------------------------*/
bool loadItemsFromFile(const string& itemFile, LinkedList& itemList)
{
	string word;
	string extraLine;

	ifstream inFile(itemFile, ios::in);
	if (!inFile)
	{
		cout << "Error in opening file." << endl;
		return false;
	}
	// appenTail each line in text file and split it

	while (getline(inFile, word))
	{
		if (word.find('#', 0) != std::string::npos)
		{
			cout << "Ignore Line: " << word << endl;
			continue;
		}
		string delim = ",";

		int i = 0;
		string space[7];

		unsigned int start = 0U;
		unsigned int end = word.find(delim);

		// Split the line around ", "
		while (end != string::npos)
		{
			// Add the token to space array
			space[i++] = word.substr(start, end - start);
			// Set start and end for next token
			start = end + delim.length();
			end = word.find(delim, start);
		}
		// Get last token
		space[i] = word.substr(start, end - start);

		// Check format
		for (int i = 0; i <= 5; i++)
		{
			if (space[i].empty())
				cerr << "[WARNING] There is/are space missing in your Item txt " << endl;
		}

		// Copy data to items and append items
		Item* tmp = nullptr;
		if (space[2] != "Game")
			checkAllSpaceItem(space[0], space[3], space[4], space[5], space[6]);
		else
			checkAllSpaceItem(space[0], space[3], space[4], space[5], "Action");

		//Load in each inheritent
		if (space[2] == "Record")
			tmp = new Record(space[0], space[1], space[2],
				space[3], space[4], space[5], space[6]);
		else if (space[2] == "DVD")
			tmp = new DVD(space[0], space[1], space[2],
				space[3], space[4], space[5], space[6]);
		else
			tmp = new Game(space[0], space[1], space[2],
				space[3], space[4], space[5], "\0");

		if (!isDuplicateNewItem(tmp, &itemList))
			itemList.appenTail(tmp);
		else
			delete tmp;
	}
	inFile.close();
	return true;
}

//Load customers from customers.txt to linked list
bool loadCusFromFile(const string& CustomerFile, Customer_List& CustomerList)
{
	string word;
	string extraLine;

	ifstream inFile(CustomerFile, ios::in);
	if (!inFile)
	{
		cout << "Error in opening file." << endl;
		return false;
	}
	// Store the last customer information
	Customer* lastCustomerGot = nullptr;

	while (getline(inFile, word))
	{
		if (word[0] == 'C') {
			string delim = ",";
			int i = 0;
			string space[7];

			unsigned int start = 0U;
			unsigned int end = word.find(delim);


			// Split the line around ", "
			while (end != string::npos)
			{
				// Add the token to space array
				space[i++] = word.substr(start, end - start);

				// Set start and end for next token
				start = end + delim.length();
				end = word.find(delim, start);
			}
			// Check format
			for (int i = 0; i <= 4; i++)
			{
				if (space[i].empty() && word[0] != 'I')
					cerr << "[WARNING] There is/are space missing in your Customer txt " << endl;
			}

			checkAllSpaceCustomer(space[0], space[3], space[2], space[4]);
			// Copy data to Customers and append Customers if not duplicate
			Customer* tmp = nullptr;

			// Get last token
			space[i] = word.substr(start, end - start);


			if (space[5] == "Guest")
			{
				tmp = new Guest(space[0], space[1], space[2],
					space[3], space[4], "0");
				lastCustomerGot = tmp;
			}

			else if (space[5] == "Regular")
			{
				tmp = new Regular(space[0], space[1], space[2],
					space[3], space[4], "0");
				lastCustomerGot = tmp;
			}
			else {
				tmp = new VIP(space[0], space[1], space[2],
					space[3], space[4], space[5]);
				lastCustomerGot = tmp;
			}


			if (!isDuplicateNewCustomer(tmp, &cus_list)) {
				CustomerList.appenTail(tmp);
			}
			else {
				delete tmp;
				lastCustomerGot = nullptr;
			}
		}
		else if (word[0] == 'I') {
			if (lastCustomerGot)
				lastCustomerGot->getListOfRentals()->appenTail(&word);
		}
		else continue;

	}
	inFile.close();
	return true;
}

// Save customers to customers.txt file from the linked list
void writeCustomersToFile(const string& customerFileName, Customer_List* customerList) {
	ofstream outFile;
	outFile.open(customerFileName);

	int size = customerList->CustomerLine(*customerList);
	if (size <= 0)
		cout << "Customer list is empty" << endl;

	else for (int i = 0; i < size; i++) {
		Customer& tmp = customerList->get(i);
		// Write customer info to customers.txt file
		outFile << tmp.get_all_customer_information() << endl;
		// Write list of rentals to customers.txt file
		for (int j = 0; j < tmp.getListOfRentals()->ItemListSize(tmp.getListOfRentals()); j++) {

			outFile << tmp.getListOfRentals()->get(j) << endl;
		}
	}
	outFile.close();
}

/*---------------END FILE I/O-----------------------------*/

/*---------------CHECKING SYSTEM-----------------------------*/

// Check duplicate customer
bool isDuplicateNewCustomer(Customer* t, Customer_List* list) {
	int listSize = list->CustomerLine(*list);
	if (listSize > 0) {
		for (int i = 0; i < listSize; i++) {
			Customer& tmp = list->get(i);
			// Validate unique xxx
			if (t->get_Customer_id().substr(1, 3) == tmp.get_Customer_id().substr(1, 3)) {
				cout << "[WARNING] Program has removed the duplicate customer : " << endl;
				t->display();

				return true;
			}

		}
		return false;
	}
	return false;
}

// Check duplicate Item
bool isDuplicateNewItem(Item* t, LinkedList* list) {
	int listSize = list->CountItem(list);
	if (listSize > 0) {
		for (int i = 0; i < listSize; i++) {
			Item& tmp = list->get(i);
			// Validate unique xxx
			if (t->getItemId().substr(1, 3) == tmp.getItemId().substr(1, 3)) {
				cout << "[WARNING] Program has removed the duplicate Item : " << endl;
				t->display();

				return true;
			}

		}
		return false;
	}
	return false;
}


//Check whether the inputs in the command line are correct
bool checkArgc(int argc)
{
	if (argc < 3)
	{
		cout << "Please input the items.txt and Customers.txt respectively." << endl;
		cout << "    * NOTE: text file format is as follows:" << endl;
		cout << "      -------------------------------------" << endl;
		cout << "      Item: Ixxx-yyyy, title, rentalType, loanType, numOfCopies, rentalFee + genre (if non-Game)" << endl;
		cout << "      Customer: Cxxx, name, address, phone, numOfPastRentals, level + points (if VIP)" << endl;
		cout << "                (list of rented IDs)" << endl;
		cout << "      Thank You." << endl;
		return false;
	}
	else
	{
		return true;
	}
}
/*---------------CHECKING SYSTEM-----------------------------*/

// Find a specific item
Item* findItem(LinkedList* list)
{
	string itemId;
	cin >> itemId;

	if (itemId.empty())
	{
		cout << "Input is empty" << endl;
		return nullptr;
	}

	int listSize = list->CountItem(list);

	if (listSize > 0)
	{
		for (int i = 0; i < listSize; i++)
		{
			Item& tmp = list->get(i);
			if (itemId == tmp.getItemId().substr(1, 3))
				return &tmp;
		}
	}
	else
	{
		cout << "Targeted list is empty" << endl;
	}

	cout << "ID not found in database" << endl;
	return nullptr;
}

// Find a specific customer
Customer* findCustomer(Customer_List* list)
{
	string cusId;
	cin >> cusId;

	if (cusId.empty())
	{
		cout << "Input is empty" << endl;
		return nullptr;
	}

	int listSize = list->CustomerLine(*list);


	if (listSize > 0)
	{
		for (int i = 0; i < listSize; i++)
		{
			Customer& tmp = list->get(i);
			if (cusId == tmp.get_Customer_id().substr(1, 3))
				return &tmp;
		}
	}
	else
	{
		cout << "Targeted list is empty" << endl;
	}

	cout << "ID not found in database" << endl;
	return nullptr;
}

// Function check all space of item before load in
void checkAllSpaceItem(string id, string loan, string copy, string fee, string genre)
{
	//Check ID space
	bool valid = true;
	for (int i = 0; i < id.length(); i++)
	{
		if (i == 0 || i == 4) continue;
		if (!isdigit(id[i])) {
			valid = false;
			break;
		}
	}
	if (valid && id.length() == 9 && id[0] == 'I' && id[4] == '-')
		cout << "";
	else
		cerr << "ID wrong format " << id << endl;

	//Check loan space
	if (loan == "1-week" || loan == "2-day")
		cout << "";
	else
		cerr << "Loan wrong format " << loan << endl;

	//Check copy space
	if (!copy.empty() && copy.find_first_not_of("0123456789") == string::npos)
	{
		cout << "";
	}
	else cerr << "Number of copy wrong format " << copy << endl;

	//check fee
	size_t foundDot = fee.find('.');
	if (foundDot != string::npos)
	{
		int firstDotPosition = foundDot;    // Dot found, find if there's a second dot
		foundDot = fee.find('.', firstDotPosition + 1);

		if (!fee.empty() && fee.find_first_not_of("0123456789.") == string::npos && foundDot == string::npos) {
			cout << "";
		}
	} // No dot
	else if (!fee.empty() && fee.find_first_not_of("0123456789") == string::npos)
	{
		cout << "";
	}
	else
		cerr << "Wrong fee format " << fee << endl;

	//check genre
	if (genre == "Action" || genre == "Horror" || genre == "Drama" || genre == "Comedy")
	{
		cout << "";
	}
	else cerr << "Wrong genre format " << genre << endl;
}

// Function check all space of item before load in
void checkAllSpaceCustomer(string id, string phone_num, string address, string past_borrow)
{
	//Check ID space
	if (id.length() == 4 && id[0] == 'C' && isdigit(id[1]) && isdigit(id[2]) && isdigit(id[3]))
		cout << "";
	else
		cerr << "Wrong ID format :" << id << endl;

	// Validate number input
	for (int i = 0; phone_num[i] == '\0'; i++)
	{
		if (isdigit(phone_num[i]))
			cout << "";
		else
			cerr << "Wrong phone number format, only number is allowed ! " << phone_num << endl;
	}
	int i = 0;
	// Validate address
	//If the character is true, which is only normal, capital and numbers, then we move to the next string index
	for (int i = 0; address[i] != '\0'; i++) {
		if ((address[i] <= 122 && address[i] >= 97) || (address[i] <= 90 && address[i] >= 65) || (address[i] == ' ' || (address[i] >= 48 && address[i] <= 57)))
			//if all the previous string index is true and the string is at null character, then it's true !, we set the value and then stop the loop
			cout << "";
		//if it has weird value like %$#@#$_+, then we will ask for the owner to type again and check for that value again
		else
			cout << "Abnormal character detected!, only alphabets and numbers are accepted " << address << endl;
	}
	//validate pass borrow
	for (int i = 0; past_borrow[i] != '\0'; i++) {
		if (isdigit(past_borrow[i]))
			cout << "";
		else
			cerr << "Wrong number past borrowed, only number is allowed ! " << phone_num << endl;
	}

}
/*-------------------------------------RENT AND RETURN---------------------------------------*/

void rentItem(LinkedList* itemList, Customer_List* customerList)
{
	cout << "Renting an item..." << endl;
	cout << "Enter an item ID (xxx) to rent: ";

	Item* item = findItem(itemList);

	if (item != nullptr)
		cout << "Item to rent: " << item->getItemString() << endl;
	else return;

	cout << "Enter a customer ID (xxx): ";
	Customer* customer = findCustomer(customerList);

	if (customer != nullptr)
	{
		cout << "Customer: " << customer->get_all_customer_information() << endl;
	}
	else return;

	// Both item and customer found, rent with constraints
	if (!item->checkAvailable())
	{
		cout << "Item is out of stock" << endl;
		return;
	}

	// Check if item is already rented
	//PrintAllItemNode is also cout lines
	int listSize = customer->getListOfRentals()->ItemListSize(customer->getListOfRentals());
	if (listSize > 0)
	{
		for (int i = 0; i < listSize; i++)
		{
			if (item->getItemId() == customer->getListOfRentals()->get(i))
			{
				cout << "Item is already in customer's rental list" << endl;
				return;
			}
		}
	}

	// Check the type of customer meets to the requirement
	if (customer->get_Customer_type() == "Guest")
	{
		if (customer->getListOfRentals()->ItemListSize(customer->getListOfRentals()) >= 2 || item->getLoan() == "2-day")
		{
			cout << "Failed: this Guest is renting a maximum of 2 items, or is trying to rent a 2-day item" << endl;
			return;
		}
	}
	// If the item and customer meets the requirement
	customer->getListOfRentals()->appenTail(&item->getItemId());

	if (customer->get_Customer_type() != "VIP" || customer->getPoints() < 100)
	{
		cout.precision(2);
		cout << "Cost ($): " << item->getFee() << endl;
	}

	customer->rent();
	item->getRented();
	cout << "Item rented successfully" << endl;
}
//Function to return item
void returnItem(LinkedList* itemList, Customer_List* customerList)
{
	cout << "Returning an item..." << endl;
	cout << "Enter an item ID (xxx) to return: ";
	Item* item = findItem(itemList);

	if (item != nullptr)
		cout << "Item to return: " << item->getItemString() << endl;
	else return;

	cout << "Enter a customer ID (xxx): ";
	Customer* customer = findCustomer(customerList);

	if (customer != nullptr)
	{
		cout << "Customer: " << customer->get_all_customer_information() << endl;
	}
	else return;

	// Find item in customer's list of rentals
	bool found = false;

	int listSize = customer->getListOfRentals()->ItemListSize(customer->getListOfRentals());
	if (listSize != 0) {
		for (int i = 0; i < listSize; i++)
		{
			if (item->getItemId() == customer->getListOfRentals()->get(i))
			{
				found = true;
				// Delete item off rental list
				customer->getListOfRentals()->deleteNode(i, listSize);
				// Item logistics
				item->getReturned();
				customer->returnItem();
				cout << "Item returned successfully" << endl;

				// Promote customer is applicable
				if (customer->get_customer_borrow_numb() >= 3)
				{
					customer->customer_promote();
				}
				break;
			}
		}
		if (!found)
			cout << "Item is not in customer's list of rentals" << endl;
	}
	else
	{
		cout << "Customer's list of rentals is empty" << endl;
	}
}
// Print Customers List By Their Customer Type
void printAllCustomerByType(Customer_List cusList)
{
	cout << "Enter an option:" << endl
		<< "1. Print all Guests Customer" << endl
		<< "2. Print all Regulars Customer" << endl
		<< "3. Print all VIPs Customer" << endl;
	int function;
	cin >> function;
	int listSize = cusList.CustomerLine(cusList);
	if (listSize > 0)
	{
		switch (function)
		{
		case 1:
		{
			for (int i = 0; i < listSize; i++)
			{
				Customer& tmp = cusList.get(i);
				if (tmp.get_Customer_type() == "Guest")
					cout << tmp.get_all_customer_information() << endl;
			}
			break;
		}
		case 2:
		{
			for (int i = 0; i < listSize; i++)
			{
				Customer& tmp = cusList.get(i);
				if (tmp.get_Customer_type() == "Regular")
					cout << tmp.get_all_customer_information() << endl;
			}
			break;
		}
		case 3:
		{
			for (int i = 0; i < listSize; i++)
			{
				Customer& tmp = cusList.get(i);
				if (tmp.get_Customer_type() == "VIP")
					cout << tmp.get_all_customer_information() << endl;
			}
			break;
		}
		default:
		{
			cerr << "Input 1 -> 3 only .Thank you " << endl;
		}
		;
		}
	}
	else
	{
		cout << "Customer list is empty" << endl;
	}
}

/*-------------------------------------RENT AND RETURN---------------------------------------*/
//Function to print the members
void member_printout()
{

	string group = { "ASSIGNMENT 2 GROUP 03" };
	string ID_1 = { "s3864077, s3864077@rmit.edu.vn, Tuan Anh , Nguyen" };
	string ID_2 = { "s3772163, s3772163@rmit.edu.vn, Hien Thuan, Ta" };
	string ID_3 = { "s3821186, s3821186@rmit.edu.vn, Dai Duong , Vo " };
	string ID_4 = { "s3847766, s3847766@rmit.edu.vn, Dang Khoa, Tran" };

	cout << group << "\n" << ID_1 << "\n" << ID_2 << "\n" << ID_3 << "\n" << ID_4 << endl;

}

int main(int argc, char* argv[])
{
	string itemFile;
	string CustomerFile;

	if (checkArgc(argc))
	{
		itemFile = argv[1];
		CustomerFile = argv[2];
	}
	else
	{
		return 1;
	}
	loadItemsFromFile(itemFile, list);
	loadCusFromFile(CustomerFile, cus_list);
	menu();
	writeCustomersToFile(CustomerFile, &cus_list);
	list.writeAllLine(list);
	member_printout();
	return 0;
}