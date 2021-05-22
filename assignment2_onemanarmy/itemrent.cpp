#include "itemrent.h"

//Insert items into current customer's borrow list 
void Item_List::appenTail(string* value)
{
	Item_Rent_Node* tmp = new Item_Rent_Node(*value);
	// If list empty, set node as head
	if (head == NULL)
	{
		head = tmp;
		tail = tmp;
	}
	else
	{
		tail->setNext(tmp);
		tail = tmp;
	}

}
//Dsiplay item
void Item_List::PrintDataInNode(Item_List* list)
{
	cout << list->head->getData() << endl;
}
//Display all items
int Item_List::PrintAllItemNode(Item_List* list)
{
	int result = 0;

	for (Item_Rent_Node* point = list->head; point != NULL; point = point->getNext())
	{
		PrintDataInNode(list);
		result++;
	}
	//Count Lines
	return result;
};
//Get the size of the rented item list
int Item_List::ItemListSize(Item_List* list)
{
	int result = 0;
	if (list != NULL) {
		for (Item_Rent_Node* point = list->head; point != NULL; point = point->getNext())
		{
			result++;
		}
	}
	//Cout Lines
	return result;
};

