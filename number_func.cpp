#include <iostream>
using namespace std;

struct entry // Declaring the structure of the ordered list
{
	int number;
	entry* next;
};

//Function Prototypes
char displayMenu(); // This function will display the menu
void firstNumber(entry *head, int n); // This function will allow the user to enter the first number
void insertNumber(struct entry** head, int n); // This function will allow the user to add in numbers after the first number
entry* searchNumber(entry* head, int n); // This function will search the number in the list
bool deleteNumber(entry** head, entry* ptrDel); // This function will delete the number in the list
void display(struct entry* head); // This function will display the ordered list
void sortList(struct entry** h_ref); // This function will sort the list
void orderTraverse(struct entry** h_ref, struct entry* n_node); // The function to insert and traverse the ordered list

int main()
{
	// Defining the variables
	int num;
	int i = 0;
	int s;
	int numDel;

	// Defining the structures
	entry* newHead;
	entry* head = new entry;
	entry* ptr = 0;
	entry* ptrDelete;

	char choice = displayMenu();
	while (choice != 'e' && 'E')
	{
		switch (choice)
		{
		case 'A': // Case 'A'and 'a' will ask the user to enter a number
			cout << endl;
			cout << "Enter a number" << endl; // Will ask the user to enter a number
			cin >> num; // Entering the first number
			if (i == 0)
			{
				firstNumber(head, num);  // Inserting other numbers
			}
			else
			{
				if (ptr == NULL) // Checking for duplicated numbers
				{
					insertNumber(&head, num);
				}
				else
				{
					cout << "Duplicate number. Not added to the list" << endl;
					cout << "Enter the number again ";
					cin >> num;
					insertNumber(&head, num);
				}
			}
			sortList(&head);
			i = i + 1;
			break;
		case 'a':
			cout << endl;
			cout << "Enter a number" << endl;
			cin >> num;
			if (i == 0)
			{
				firstNumber(head, num);
			}
			else
			{
				if (ptr == NULL)
				{
					insertNumber(&head, num);
				}
				else
				{
					cout << "Duplicate number. Not added to the list" << endl;
					cout << "Enter the number again ";
					cin >> num;
					insertNumber(&head, num);
				}
			}
			sortList(&head);
			i = i + 1;
			break;
		case 'B': // Case 'B' and 'b' will delete a number within the list
			cout << endl;
			int numDel;
			cout << "Enter a number to be deleted: "; // Asking the user what number should be deleted
			cin >> numDel; // Declaring the number that's going to be deleted

			ptrDelete = searchNumber(head, numDel); //Searching the number within the list
			if (ptrDelete == NULL)
			{
				cout << "Number not found" << endl; // If the number is not found within the list, it will output an error message
			}
			else
			{
				if (deleteNumber(&head, ptrDelete)) // If the number is found it will be deleted
				{
					cout << "Number " << numDel << " has been deleted" << endl;
				}
			}
			break;
		case 'b':
			cout << endl;
			cout << "Enter a number to be deleted: ";
			cin >> numDel;

			ptrDelete = searchNumber(head, numDel);
			if (ptrDelete == NULL)
			{
				cout << "Element not found" << endl;
			}
			else
			{
				if (deleteNumber(&head, ptrDelete))
				{
					cout << "Number " << numDel << " deleted" << endl;
				}
			}
			break;
		case 'C': // Case 'C' and 'c' will ask the user to search for a number
			cout << endl;
			cout << "Enter a number to be searched "; // Asking the user what number he/she would like to search
			cin >> s; // Declaring the number that will be searched
			ptr = searchNumber(head, s); // Searching the number within the list

			if (ptr == NULL)
			{
				cout << "Number not found in the list" << endl; // If the number is not in the list, an error message will be displayed
			}
			else
			{
				cout << "The number is in the list! " << endl; // If the number is in the list, it will display a message stating that the number has been found
			}

			break;
		case 'c':
			cout << endl;
			int s;
			cout << "Enter a number to be searched ";
			cin >> s;
			ptr = searchNumber(head, s);

			if (ptr == NULL)
			{
				cout << "Number not found in the list" << endl;
			}
			else
			{
				cout << "Number " << s << " is found" << endl;
			}
			break;
		case 'D': // Case 'D' and 'd' will display the ordered list
			display(head);
			break;
		case 'd':
			display(head);
			break;
		default: cout << "Wrong choice" << endl;
		}
		cout << endl;
		choice = displayMenu();
	}
	return 0;
}

char displayMenu()// Function definition for displayMenu
{
	char choice;
	string menu;

	menu = "Choose from the following menu: \n";
	menu += "--------------------------------\n";
	menu += "a - Add a number \n";
	menu += "b - Delete a number \n";
	menu += "c - Search for a number \n";
	menu += "d - Display the whole list of numbers \n";
	menu += "e - Exit \n";

	cout << menu << endl;
	cin >> choice;
	choice = tolower(choice);

	return choice; // This function will continue to display until the user has entered 'E' or 'e' to exit the program
}

void firstNumber(entry* head, int n) // Function definition of firstNumber
{
	head->number = n;
	head->next = NULL;
}// This function will enter the first number within the list

void insertNumber(struct entry** head, int n)// Function definition of insertNumber
{
	entry* nNode = new entry;
	nNode->number = n;
	nNode->next = *head;
	*head = nNode;
}// This function will allow the user to append the list, adding numbers to the list.

bool deleteNumber(entry** head, entry* ptrDel) // Function definition of deleteNumber
{
	entry* curr = *head;

	if (ptrDel == *head)
	{
		*head = curr->next;
		delete ptrDel;
		return true;
	}
	while (curr)
	{
		if (curr->next == ptrDel)
		{
			curr->next = ptrDel->next;
			delete ptrDel;
			return true;
		}
		curr = curr->next;
	}
	return false;
} // This function allows the user to delete a number within the list

void display(struct entry* head) // Function definition of display
{
	cout << endl;
	cout << "The ordered list is:" << endl;
	entry* list = head;
	while (list != NULL)
	{
		cout << list->number << " ";
		list = list->next;
	}
	cout << endl;
}// This function will display the ordered list

void sortList(struct entry** h_ref)// Function definition of sortList
{
	struct entry* ordered = NULL;
	struct entry* current = *h_ref;
	while (current != NULL)
	{
		struct entry* next = current->next;
		orderTraverse(&ordered, current);
		current = next;
	}
	*h_ref = ordered;
}// This function will sort the list so that the numbers are in order

void orderTraverse(struct entry** h_ref, struct entry* n_node)// Function definition of orderTraverse
{
	struct entry* current;
	if (*h_ref == NULL || (*h_ref)->number >= n_node->number)
	{
		n_node->next = *h_ref;
		*h_ref = n_node;
	}
	else
	{
		current = *h_ref;
		while (current->next != NULL && current->next->number < n_node->number)
		{
			current = current->next;
		}
		n_node -> next = current->next;
		current->next = n_node;
	}
}// This function will traverse the ordered list

entry* searchNumber(entry* head, int n) // Function definition of searchNumber
{
	entry* curr = head;
	while (curr)
	{
		if (curr->number == n)
		{
			return curr;
		}
		curr = curr->next;
	}
}// This function will search the number in the list