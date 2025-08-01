#include <iostream>
#include <string>

using namespace std;

int Id[10];
string Title[10];
string Author[10];
bool Availability[10];
int Totalbooks = 0;

bool IdFound(int id) {
	for (int i = 0; i < Totalbooks; i++) {
		if (Id[i] == id)
			return true;
	}
	return false;
}
bool CheckBackRequest(int id) {
	if (id == 0) {
		cout << "\nBack to the main menu.";
		return true;
	}
	return false;
}

void AddBook() {

	int newId;
	bool repetition = false;

	cout << "Please enter the book id (or 0 to go back ) : ";
	cin >> newId;

	if (CheckBackRequest(newId))
		return;

	if (IdFound(newId)) {
		repetition = true;
	}

	if (repetition) {
		cout << "The book ID has already been added\n";
		return;
	}

	cin.ignore();
	Id[Totalbooks] = newId;



	cout << "Please enter the title of the book : ";
	getline(cin, Title[Totalbooks]);


	cout << "Please enter the book author : ";
	getline(cin, Author[Totalbooks]);


	Availability[Totalbooks] = true;

	Totalbooks++;

	cout << "The book has been successfully added\n";
	cout << "Now Total books : " << Totalbooks << endl;


}
void UpdateBook(int id) {

	if (CheckBackRequest(id))
		return;

	if (!IdFound(id)) {
		cout << "Book with ID " << id << " not found.\n";
		return;
	}

	int y;
	for (int i = 0; i < Totalbooks; i++) {
		if (Id[i] == id) {

			cout << "The title of the book : " << Title[i] << endl;
			cout << "The author's name : " << Author[i] << endl;

			cout << "\nWhat do you want to update ?\n";
			cout << "1. ID\n" << "2. Title\n" << "3. Author\n";
			cout << "Enter the number : ";

			do {
				cin >> y;
				cout << endl;

				if (y == 1) {
					int NewId;
					bool isUsed;
					do {
						isUsed = false;
						cout << "Enter the new ID : ";
						cin >> NewId;

						if (IdFound(NewId)) {
							isUsed = true;
							cout << "This ID is already in use. Please enter a different ID.\n";
						}

					} while (isUsed);

					Id[i] = NewId;
					cout << "The ID has been successfully updated\n ";
					break;
				}
				else if (y == 2) {
					string NewTitle;
					cout << "Enter the title : ";
					cin.ignore();
					getline(cin, NewTitle);
					Title[i] = NewTitle;
					cout << "The Title has been successfully updated\n ";
					break;
				}
				else if (y == 3) {
					string NewAuthor;
					cout << "Enter the author's name : ";
					cin.ignore();
					getline(cin, NewAuthor);
					Author[i] = NewAuthor;
					cout << "The Author has been successfully updated\n ";
					return;
				}
				else {
					cout << "Wrong, please enter the correct number : ";
				}
			} while (!(y == 1 || y == 2 || y == 3));
			break;
		}
	}
}
void RemoveBook() {
	int y;

	cout << "Do you want to remove a book or books ?\n"
		<< "1. A book.\n" << "2. The Books.\n" << ":";
	cin >> y;

	switch (y) {

	case 1: {
		int id;
		cout << "Enter the ID of the book to Remove (or 0 to go back ) : ";
		cin >> id;
		cout << endl;

		if (CheckBackRequest(id))
			return;

		if (!IdFound(id)) {
			cout << "Book with ID " << id << " not found.\n";
			return;
		}

		for (int i = 0; i < Totalbooks; i++) {
			if (id == Id[i]) {
				for (int z = i; z < Totalbooks - 1; z++) {
					Id[z] = Id[z + 1];
					Title[z] = Title[z + 1];
					Author[z] = Author[z + 1];
					Availability[z] = Availability[z + 1];
				}
				Totalbooks--;
				cout << "Successfully Removed\n";
				return;
			}
		}
		break;
	}

	case 2: {
		string confirm;
		cout << "To confirm deletion of ALL books, type 'Delete' (or 'Back' to cancel): ";
		cin >> confirm;

		if (confirm == "Delete" || confirm == "delete") {
			for (int i = 0; i < 10; i++) {
				Id[i] = 0;
				Title[i] = "";
				Author[i] = "";
				Availability[i] = false;
			}
			Totalbooks = 0;
			cout << "All books removed successfully.\n";
			cout << "Now total number of books is zero.\n";
		}
		else if (confirm == "Back" || confirm == "back") {
			cout << "Canceled. Returning to the main menu.\n";
			return;
		}
		else {
			cout << "Invalid input. Returning to the main menu.\n";
		}
		break;
	}

	default:
		cout << "Invalid option.\n";
		break;
	}
}
void BorrowBook(int id) {
	if (CheckBackRequest(id))
		return;

	for (int i = 0; i < Totalbooks; i++) {
		if (id == Id[i]) {
			if (Availability[i]) {
				cout << "The book is available\nOk, it's been borrowed.\n";
				Availability[i] = false;
			}
			else {
				cout << "The book is not available\n";
			}
			return;
		}
	}
	cout << "Book with ID " << id << " not found.\n";
}
void ReturnBook(int id) {

	if (CheckBackRequest(id))
		return;

	for (int i = 0; i < Totalbooks; i++) {
		if (id == Id[i]) {
			if (!Availability[i]) {
				cout << "The book has been returned\nThe book is available now.\n";
				Availability[i] = true;
			}
			else {
				cout << "It's already available.\n";
			}
			return;
		}
	}

	cout << "Book with ID " << id << " not found.\n";
}
void DisplayBook() {

	if (Totalbooks == 0) {
		cout << "No books in the library.\n";
		return;
	}
	cout << "The books :\n " << endl;

	for (int i = 0; i < Totalbooks; i++) {

		cout << "----------------------------\n";
		cout << i + 1 << ". ID : " << Id[i];
		cout << ", Title : " << Title[i];
		cout << ", Author : " << Author[i];
		cout << ", Status: " << (Availability[i] ? "Available " : "Borrowed ") << endl;
		cout << "----------------------------\n";


	}

}
void Statistics() {
	int Availablebooks = 0, Borrowedbooks = 0;

	for (int i = 0; i < Totalbooks; i++) {

		if (Availability[i]) {
			Availablebooks++;
		}
		else {
			Borrowedbooks++;
		}

	}
	cout << "Total number of books : " << Totalbooks << endl;
	cout << "Number of books available : " << Availablebooks << endl;
	cout << "Number of borrowed books : " << Borrowedbooks << endl;



}

int main()
{
	int x;

	int id = 0;
	string title;
	string author;
	bool fl = true;

	cout << "Welcome to the Alex Library\n";
	cout << "\nplease select the service you need :" << endl;

	do {
		cout << "\nPlease select another service :\n"
			<< "1. Add a new book.\n"
			<< "2. Update specific book.\n"
			<< "3. Remove an existing book.\n"
			<< "4. Borrow a book.\n"
			<< "5. Return a book.\n"
			<< "6. Display the books list.\n"
			<< "7. Library statistics.\n"
			<< "8. Exit\n"
			<< "\nEnter the service number : ";
		cin >> x;
		cout << endl;


		switch (x) {

		case 1:

			if (Totalbooks >= 10) {
				cout << "Cannot add more books. Storage is full.\n";
				break;
			}
			AddBook();
			break;

		case 2:
			cout << "Enter the ID of the book to update (or 0 to go back ) : ";
			cin >> id;
			cout << endl;
			UpdateBook(id);
			break;

		case 3:
			RemoveBook();
			break;

		case 4:
			cout << "Enter the ID of the book to borrow (or 0 to go back ) : ";
			cin >> id;
			cout << endl;
			BorrowBook(id);
			break;

		case 5:
			cout << "Enter the ID of the book to Return (or 0 to go back ) : ";
			cin >> id;
			cout << endl;
			ReturnBook(id);
			break;

		case 6:
			DisplayBook();
			break;
			 
		case 7:
			Statistics();
			break;

		case 8:
			fl = false;
			cout << "Exiting the program. Goodbye!\n";
			break;


		default:

			cout << "Invalid option. Please enter a number from 1 to 8.\n";
		}
	} while (fl);
	return 0;
}




