#include "item.h"
#include "Customer.h"

bool isDuplicateNewItem(Item* t, LinkedList* list);

// Create node for item
Node* Node::createNode(Item newData)
{
	Node* temp = new Node;
	if (temp == nullptr)
	{
		cout << "Failed." << endl;
		throw(temp);
	}
	temp->data = newData;
	temp->setNext(nullptr);
	return temp;
}

// Create list for item
void LinkedList::createList(LinkedList& list)
{
	list.head = nullptr;
	list.tail = nullptr;
}

//Inserting head to item list
void LinkedList::insertHead(LinkedList& list, Node* temp)
{
	if (list.head == nullptr)
	{
		list.head = list.tail = temp;
	}
	else
	{
		temp->setNext(head);
		list.head = temp;
	}
}

//Appointing tail for item list
void LinkedList::appenTail(LinkedList& list, Node* temp)
{
	if (list.head == nullptr)
	{
		list.head = temp;
		list.tail = temp;
	}
	else
	{
		list.tail->setNext(temp);
		list.tail = temp;
	}
}
void LinkedList::appenTail(Item* value) {
	Node* tmp = new Node(*value);
	// Check whether head is empty, append tail will be head
	if (head == NULL) {
		head = tmp;
		tail = tmp;
	}
	else {
		tail->setNext(tmp);
		tail = tmp;
	}
}

//Print out item in one line on console screen
void LinkedList::printAllItemList(LinkedList* list)
{
	if (list != NULL) {
		for (Node* point = list->head; point != NULL; point = point->getNext())
		{
			point->getData().display(); //print all item
		}
	}


}

int LinkedList::CountItem(LinkedList* list)
{
	int result = 0;
	if (list != NULL) {
		for (Node* point = list->head; point != NULL; point = point->getNext())
		{
			result++;
		}
	}
	// Print out result to console screen
	return result;
}


//Function to input ID
void InputID(Item& item)
{
	cout << "Enter item's ID: ";
	while (true)
	{
		string newID;
		getline(cin, newID);
		// Check whether input is valid
		bool valid = true;
		for (size_t i = 0; i < newID.length(); i++)
		{
			if (i == 0 || i == 4) continue;
			if (!isdigit(newID[i]))
			{
				valid = false;
				break;
			}
		}
		if (valid && newID.length() == 9 && newID[0] == 'I' && newID[4] == '-')
		{
			item.setItemId(newID);
			break;
		}
		else
		{
			cout << "Error: invalid ID. Please input: Ixxx-yyyy (x: digit, yyyy: published year)" << endl;
			cout << "Enter again: ";
		}
	}
}

// Function to input Title
void InputTitle(Item& item)
{
	cout << "Enter item's title: ";
	while (true)
	{
		string newTitle;
		getline(cin, newTitle);
		if (!newTitle.empty())
		{
			item.setTitle(newTitle);
			break;
		}
		else
			cout << "Error: invalid title. Enter again: ";
	}
}

//Function to set renttype of DVD and Record
void Input_DVD_Record(Item& item)
{
	cout << "Enter item's rent type: ";
	while (true)
	{
		string newRent;
		getline(cin, newRent);
		// Check Loan type for DVD or Record
		if (newRent == "DVD" || newRent == "Record")
		{
			item.setRentType(newRent);
			break;
		}
		else
		{
			cout << "Error: invalid rent type. Please input: DVD or Record" << endl;
			cout << "Enter again: ";
		}
	}
}

//Function to set game renttype
void InputGame(Item& item)
{
	string newRent = "Game";
	item.setRentType(newRent);
}

// Function to input Loan
void InputLoan(Item& item)
{
	cout << "Enter item's loan type: ";
	while (true)
	{
		string newLoan;
		getline(cin, newLoan);
		// Check the loan type input from user
		if (newLoan == "1-week" || newLoan == "2-day")
		{
			item.setLoan(newLoan);
			break;
		}
		else
		{
			cout << "Error: invalid loan type. Please input: 1-week or 2-day" << endl;
			cout << "Enter again: ";
		}
	}
}

// Function to set copies store in stock
void InputCopy(Item& item)
{
	cout << "Enter item's number of copies: ";
	while (true)
	{
		string newCopy;
		getline(cin, newCopy);
		// Check whether int input is valid
		if (!newCopy.empty() && newCopy.find_first_not_of("0123456789") == string::npos)
		{
			item.setCopy(stoi(newCopy));
			break;
		}
		else
			cout << "Error: invalid input. Enter again: ";
	}
}

// Function to set renting fee
void InputFee(Item& item)
{
	cout << "Enter item's rental fee: ";
	while (true)
	{
		string newFee;
		getline(cin, newFee);
		// Check is input is valid
		size_t foundDot = newFee.find('.');
		if (foundDot != string::npos)
		{
			int firstDotPosition = foundDot;    // An Dot is found, check whether second dot exist
			foundDot = newFee.find('.', firstDotPosition + 1);

			if (!newFee.empty() && newFee.find_first_not_of("0123456789.") == string::npos && foundDot == string::npos)
			{
				item.setFee(stod(newFee));
				break;
			}
		} // None of other dot found
		else if (!newFee.empty() && newFee.find_first_not_of("0123456789") == string::npos)
		{
			item.setFee(stod(newFee));
			break;
		}
		else
			cout << "Error: invalid input. Enter again: ";
	}
}

//Function to input genre
void InputGenre(Item& item)
{
	cout << "Enter item's genre: ";
	while (true)
	{
		string newGenre;
		getline(cin, newGenre);
		// Check whether gender is valid
		if (newGenre == "Action" || newGenre == "Horror" || newGenre == "Drama" || newGenre == "Comedy")
		{
			item.setGenre(newGenre);
			break;
		}
		else {
			cout << "Error: invalid genre. Valid genres: Action, Horror, Drama, Comedy" << endl;
			cout << "Enter again: ";
		}
	}
}

// Function to add game to list
void LinkedList::add_Game(LinkedList& list)
{
	Item item;
	Node node;
	Node* temp = new Node;
	cin.ignore();
	InputID(item);
	InputTitle(item);
	InputGame(item);
	InputLoan(item);
	InputCopy(item);
	InputFee(item);
	temp = node.createNode(item); // create node for item
	// if item is new, append it to the list
	if (!isDuplicateNewItem(&item, &list)) {
		list.appenTail(list, temp); //Set node to the end of list
		cout << "Added: ";
		item.display();

		if (item.getCopy() > 0)
			item.setAvailable();
	}
	else {
		// else it is duplicate free memory
		cout << "Duplicate ID, item will not be added" << endl;
		delete temp;
	}
}

//Function to add DVD ot Record to item
void LinkedList::add_DVD_Record(LinkedList& list)
{
	Item item;
	Node node;
	Node* temp = new Node;
	cin.ignore();
	InputID(item);
	InputTitle(item);
	Input_DVD_Record(item);
	InputLoan(item);
	InputCopy(item);
	InputFee(item);
	InputGenre(item);
	temp = node.createNode(item); //Create the node
	// If item is new, append it to the list
	if (!isDuplicateNewItem(&item, &list))
	{
		list.appenTail(list, temp); //Set the node to be at the end of the list
		cout << "Added: ";
		item.display();

		if (item.getCopy() > 0)
			item.setAvailable();
	}
	else
	{
		// It is duplicated, free memory
		cout << "Duplicate ID, item will not be added" << endl;
		delete temp;
	}
}

// Function to delete item from list
void LinkedList::deleteItem(LinkedList list)
{
	string deleteId;
	cout << "Enter the item's Id you want to delete(Ixxx-xxxx): ";
	cin >> deleteId;
	Item item;
	Node* temp = list.head;
	bool found = false;
	if (temp == NULL)
	{
		cerr << "There are no items." << endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		Node* previous = nullptr;
		while (temp != NULL)
		{
			item = temp->getData();
			if (item.getItemId().compare(deleteId) == 0)
			{
				found = true;
				break;
			}
			previous = temp;
			temp = temp->getNext();
		}
		if (found == false)
		{
			cerr << "Item not found." << endl;
			cout << "Re-enter again: ";
			cin >> deleteId;
		}
		else
		{
			if (temp == list.head)
			{
				head = head->getNext();
				temp->setNext(NULL);
				delete temp;
				temp = NULL;
				cout << "Delete success." << endl;
			}
			else if (temp->getNext() == NULL)
			{
				tail = previous;
				previous->setNext(NULL);
				delete temp;
				temp = NULL;
				cout << "Delete success." << endl;
			}
			else
			{
				previous->setNext(temp->getNext());
				temp->setNext(NULL);
				delete temp;
				temp = NULL;
				cout << "Delete success." << endl;
			}
		}
	}
}

//Function to display menu after updated
int getUpdateFieldMenu()
{
	while (true)
	{
		cout << endl;
		cout << "Enter an option below:" << endl
			<< "1. Update ID" << endl
			<< "2. Update title" << endl
			<< "3. Update loan type" << endl
			<< "4. Update number of copies" << endl
			<< "5. Update rental fee" << endl
			<< "6. Quit editing" << endl;

		int field = 0;
		cout << "Enter your choice: ";
		cin >> field;
		return field;
	}
}

//Function to check edit item is duplicated
bool isDuplicateEditedItem(Item* t, LinkedList* list, int index)
{
	int listSize = list->CountItem(list);
	if (listSize > 0) {
		for (int i = 0; i < listSize; i++) {
			if (i != index) {
				Item& tmp = list->get(i);
				//Check if ID is unique
				if (t->getItemId().substr(1, 3) == tmp.getItemId().substr(1, 3))
					return true;
			}
		}
		return false;
	}
	return false;
}

//function Update or delete item
void LinkedList::updateItem(LinkedList& itemList)
{
	string id;
	cout << "Enter the targeted item's ID (xxx): ";
	cin >> id;

	int listSize = CountItem(&itemList);
	bool found = false;

	// If list is not empty, search for item
	if (listSize != 0)
	{
		for (int i = 0; i < listSize; i++)
		{
			Item& tmp = itemList.get(i);
			if (id == tmp.getItemId().substr(1, 3))
			{
				found = true;
				string oldId = tmp.getItemId();
				cout << endl;
				cout << "Selected item: " << endl;
				tmp.display();
				int choice = getUpdateFieldMenu();
				tmp.updateItemMenu(choice, tmp);
				if (isDuplicateEditedItem(&tmp, &itemList, i)) {
					cout << "New ID is duplicate, revert to the old ID" << endl;
					tmp.setItemId(oldId);
					cout << "Edited: ";
					tmp.display();
				}
			}
		}
		if (!found)
			cout << "ID not found" << endl;
	}
}

// Update item by single field
void Item::updateItemMenu(int field, Item& item)
{
	switch (field)
	{
	case 1:
	{
		cin.ignore();
		InputID(item);
		cout << "Edited item: ";
		display();
		cout << endl;
		break;
	}
	case 2:
	{
		cin.ignore();
		InputTitle(item);
		cout << "Edited item: ";
		display();
		cout << endl;
		break;
	}
	case 3:
	{
		cin.ignore();
		InputLoan(item);
		cout << "Edited item: ";
		display();
		cout << endl;
		break;
	}
	case 4:
	{
		cin.ignore();
		InputCopy(item);
		cout << "Updated item: ";
		display();
		cout << endl;
		break;
	}
	case 5:
	{
		cin.ignore();
		InputFee(item);
		cout << "Updated item: ";
		display();
		cout << endl;
		break;
	}
	default:;
	}
}

//Display items which fit the ID
void LinkedList::searchById(LinkedList list)
{
	string searchId;
	cout << "Enter the item's Id you want to find(Ixxx - xxxx): ";
	cin >> searchId;
	Item item;
	Node* temp = list.head;
	bool found = false;
	if (temp == NULL)
	{
		cerr << "There are no items." << endl;
		exit(EXIT_FAILURE);
	}
	while (temp != NULL)
	{
		item = temp->getData();
		if (item.getItemId().compare(searchId) == 0)
		{
			item.display();
			found = true;
		}
		temp = temp->getNext();
	}
	if (!found)
	{
		cerr << "item not found." << endl;
	}
}

//Display items which fit the title
void LinkedList::searchByTitle(LinkedList list)
{
	string searchTitle;
	Item item;
	Node* temp = list.head;
	bool found = false;
	cout << "Enter the item's title you want to find: ";
	cin.ignore();
	getline(cin, searchTitle);
	if (temp == NULL)
	{
		cerr << "There are no items." << endl;
	}
	else
	{
		while (temp != NULL)
		{
			item = temp->getData();
			if (_stricmp(item.getTitle().c_str(), searchTitle.c_str()) == 0)
			{
				found = true;
				item.display();
			}
			temp = temp->getNext();
		}
	}
	if (!found)
	{
		{
			cerr << "Item not found." << endl;
		}
	}
}

//Write one line of a linked dlist
void LinkedList::writeOneLine(ostream& file, Item& item)
{
	if (item.getRentType() == "Game")
	{
		file << item.getItemId() << ',' << item.getTitle() << ',' << item.getRentType() << ',' << item.getLoan() << ',' << item.getCopy() << ',' << item.getFee() << endl;
	}
	else
	{
		file << item.getItemId() << ',' << item.getTitle() << ',' << item.getRentType() << ',' << item.getLoan() << ',' << item.getCopy() << ',' << item.getFee() << ',' << item.getGenre() << endl;
	}
}

//Write linked list to items.txt file
void LinkedList::writeAllLine(LinkedList& list)
{
	ofstream fileOut("items.txt", ios::out | ios::trunc);
	for (Node* temp = head; temp != nullptr; temp = temp->getNext())
	{
		writeOneLine(fileOut, temp->getData());
	}
	fileOut.close();
}
void LinkedList::deleteLinkedList(LinkedList& list)
{
	Node* temp = nullptr;
	while (list.head != nullptr)
	{
		temp = head;
		head = head->getNext();
		delete temp;
	}
}

// Print all item information
void Item::display()
{
	cout.precision(2);
	cout << this->itemId << "," << this->title << "," << this->rentType << ","
		<< this->loan << "," << this->num_copy << ","
		<< fixed << this->fee;
	if (this->rentType != "Game")
		cout << "," << this->genre;

	cout << endl;
}

//Display item that sorted by ID
void LinkedList::sortedById(LinkedList& list)
{
	Node* current = list.head;
	for (Node* current = list.head; current != nullptr; current = current->getNext())
	{
		for (Node* temp = current->getNext(); temp != nullptr; temp = temp->getNext())
		{
			if (current->getData().getItemId() > temp->getData().getItemId())
			{
				swap(current->getData(), temp->getData());

			}
		}
		current->getData().display();
	}

	cout << endl;

}

//Display item that sorted by Title
void LinkedList::sortedByTitle(LinkedList& list)
{
	Node* current = list.head;
	for (Node* current = list.head; current != nullptr; current = current->getNext())
	{
		for (Node* temp = current->getNext(); temp != nullptr; temp = temp->getNext())
		{
			if (_stricmp(current->getData().getTitle().c_str(), temp->getData().getTitle().c_str()) > 0)
			{
				swap(current->getData(), temp->getData());
			}
		}
		current->getData().display();
	}
	cout << endl;
}

//Display item that has no copy available in stocks
void LinkedList::printOutOfStock(LinkedList& list)
{
	Node* temp = list.head;
	bool found = false;
	if (temp == NULL)
	{
		cerr << "There are no items." << endl;
		return;
	}
	while (temp != nullptr)
	{
		Item& item = temp->getData();
		if (item.getCopy() == 0)
		{
			item.display();
			found = true;
		}
		temp = temp->getNext();
	}
	if (!found)
	{
		cout << "Stocks are full." << endl;
	}
	cout << endl;
}