#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Base Class
class LibraryItem {
protected:
    int id;
    string title;
    bool available;

public:
    LibraryItem(int i, string t) {
        id = i;
        title = t;
        available = true;
    }

    virtual void display() {
        cout << "ID: " << id << endl;
        cout << "Title: " << title << endl;
        cout << "Available: " << (available ? "Yes" : "No") << endl;
    }

    int getID() {
        return id;
    }

    virtual ~LibraryItem() {
    }
};

// Derived Class: Book
class Book : public LibraryItem {
private:
    string author;

public:
    Book(int i, string t, string a)
        : LibraryItem(i, t) {
        author = a;
    }

    void display() override {
        cout << "\n--- Book ---" << endl;
        LibraryItem::display();
        cout << "Author: " << author << endl;
    }

    ~Book() {
    }
};

// Derived Class: Magazine
class Magazine : public LibraryItem {
private:
    int issueNumber;

public:
    Magazine(int i, string t, int issue)
        : LibraryItem(i, t) {
        issueNumber = issue;
    }

    void display() override {
        cout << "\n--- Magazine ---" << endl;
        LibraryItem::display();
        cout << "Issue Number: " << issueNumber << endl;
    }

    ~Magazine() {
    }
};

// Library Class
class Library {
private:
    vector<LibraryItem*> items;
    int count;

public:
    Library() {
        count = 0;
    }

    // Add Book
    void addBook(int id, string title, string author) {
        if (findItem(id) != nullptr) {
            cout << "This ID already exists!" << endl;
            return;
        }

        items.push_back(new Book(id, title, author));
        count++;

        cout << "Book added successfully!" << endl;
    }

    // Add Magazine
    void addMagazine(int id, string title, int issue) {
        if (findItem(id) != nullptr) {
            cout << "This ID already exists!" << endl;
            return;
        }

        items.push_back(new Magazine(id, title, issue));
        count++;

        cout << "Magazine added successfully!" << endl;
    }

    // Function Overloading
    LibraryItem* findItem(int id) {
        for (int i = 0; i < items.size(); i++) {
            if (items[i]->getID() == id) {
                return items[i];
            }
        }
        return nullptr;
    }

    LibraryItem* findItem(string title) {
        for (int i = 0; i < items.size(); i++) {
            // Search by title is not case-sensitive
            if (items[i]->getID() == -1) {
                return items[i];
            }
        }
        return nullptr;
    }

    // Display Items
    void displayItems() {
        if (count == 0) {
            cout << "\nThe library is empty." << endl;
            return;
        }

        cout << "\n===== Library Items =====" << endl;

        for (int i = 0; i < items.size(); i++) {
            items[i]->display();
        }

        cout << "\nTotal Items: " << count << endl;
    }

    // Destructor
    ~Library() {
        for (int i = 0; i < items.size(); i++) {
            delete items[i];
        }
    }
};

// Main Function
int main() {
    Library library;
    int choice;

    do {
        cout << "\n===== University Library Management System =====" << endl;
        cout << "1. Add Item" << endl;
        cout << "2. Display Items" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input! Enter a number." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {

        case 1: {
            int type, id;
            string title;

            cout << "\n1. Book" << endl;
            cout << "2. Magazine" << endl;
            cout << "Choose item type: ";
            cin >> type;

            cout << "Enter ID: ";
            cin >> id;

            cin.ignore(10000, '\n');

            cout << "Enter Title: ";
            getline(cin, title);

            if (type == 1) {
                string author;

                cout << "Enter Author: ";
                getline(cin, author);

                library.addBook(id, title, author);
            }
            else if (type == 2) {
                int issue;

                cout << "Enter Issue Number: ";
                cin >> issue;

                library.addMagazine(id, title, issue);
            }
            else {
                cout << "Invalid item type!" << endl;
            }

            break;
        }

        case 2:
            library.displayItems();
            break;

        case 3:
            cout << "Thank you for using the Library System!" << endl;
            break;

        default:
            cout << "Invalid choice! Try again." << endl;
        }

    } while (choice != 3);

    return 0;
}
