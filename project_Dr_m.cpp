#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ===============================
// Base Class
// ===============================
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

    bool isAvailable() {
        return available;
    }

    void borrowItem() {
        if (available) {
            available = false;
            cout << "Item borrowed successfully!" << endl;
        }
        else {
            cout << "Item is not available!" << endl;
        }
    }

    void returnItem() {
        if (!available) {
            available = true;
            cout << "Item returned successfully!" << endl;
        }
        else {
            cout << "Item was not borrowed!" << endl;
        }
    }

    virtual ~LibraryItem() {
    }
};

// ===============================
// Derived Class: Book
// ===============================
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

// ===============================
// Derived Class: Magazine
// ===============================
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

// ===============================
// Student Class
// ===============================
class Student {
private:
    int studentID;
    string name;
    vector<int> borrowedItems;

public:
    Student(int id, string n) {
        studentID = id;
        name = n;
    }

    int getID() {
        return studentID;
    }

    bool hasBorrowed(int itemID) {
        for (int i = 0; i < borrowedItems.size(); i++) {
            if (borrowedItems[i] == itemID) {
                return true;
            }
        }
        return false;
    }

    void addBorrowedItem(int itemID) {
        borrowedItems.push_back(itemID);
    }

    void removeBorrowedItem(int itemID) {
        for (int i = 0; i < borrowedItems.size(); i++) {
            if (borrowedItems[i] == itemID) {
                borrowedItems.erase(borrowedItems.begin() + i);
                return;
            }
        }
    }

    void display() {
        cout << "\nStudent ID: " << studentID << endl;
        cout << "Student Name: " << name << endl;

        cout << "Borrowed Items: ";
        if (borrowedItems.empty()) {
            cout << "None";
        }
        else {
            for (int i = 0; i < borrowedItems.size(); i++) {
                cout << borrowedItems[i] << " ";
            }
        }

        cout << endl;
    }

    ~Student() {
    }
};

// ===============================
// Library Class
// ===============================
class Library {
private:
    vector<LibraryItem*> items;
    vector<Student*> students;
    int count;

public:
    Library() {
        count = 0;
    }

    // Function Overloading: Find Item
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
            if (items[i]->getID() == -1) {
                return items[i];
            }
        }
        return nullptr;
    }

    // Find Student
    Student* findStudent(int id) {
        for (int i = 0; i < students.size(); i++) {
            if (students[i]->getID() == id) {
                return students[i];
            }
        }
        return nullptr;
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

    // Register Student
    void addStudent(int id, string name) {
        if (findStudent(id) != nullptr) {
            cout << "Student ID already exists!" << endl;
            return;
        }

        students.push_back(new Student(id, name));
        cout << "Student registered successfully!" << endl;
    }

    // Display Students
    void displayStudents() {
        if (students.empty()) {
            cout << "\nNo students registered." << endl;
            return;
        }

        cout << "\n===== Student Records =====" << endl;

        for (int i = 0; i < students.size(); i++) {
            students[i]->display();
        }
    }

    // Borrow Item
    void borrowBook(int studentID, int itemID) {
        Student* student = findStudent(studentID);
        LibraryItem* item = findItem(itemID);

        if (student == nullptr) {
            cout << "Student not found!" << endl;
            return;
        }

        if (item == nullptr) {
            cout << "Item not found!" << endl;
            return;
        }

        if (!item->isAvailable()) {
            cout << "Item is not available!" << endl;
            return;
        }

        item->borrowItem();
        student->addBorrowedItem(itemID);
    }

    // Return Item
    void returnBook(int studentID, int itemID) {
        Student* student = findStudent(studentID);
        LibraryItem* item = findItem(itemID);

        if (student == nullptr) {
            cout << "Student not found!" << endl;
            return;
        }

        if (item == nullptr) {
            cout << "Item not found!" << endl;
            return;
        }

        if (!student->hasBorrowed(itemID)) {
            cout << "This student did not borrow this item!" << endl;
            return;
        }

        item->returnItem();
        student->removeBorrowedItem(itemID);
    }

    // Destructor
    ~Library() {
        for (int i = 0; i < items.size(); i++) {
            delete items[i];
        }

        for (int i = 0; i < students.size(); i++) {
            delete students[i];
        }
    }
};

// ===============================
// Main Function
// ===============================
int main() {
    Library library;
    int choice;

    do {
        cout << "\n===================================" << endl;
        cout << " University Library Management System" << endl;
        cout << "===================================" << endl;

        cout << "1. Manage Books" << endl;
        cout << "2. Manage Students" << endl;
        cout << "3. Exit" << endl;

        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input! Enter a number." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {

        // Manage Books
        case 1: {
            int option;

            cout << "\n===== Manage Books =====" << endl;
            cout << "1. Add Book" << endl;
            cout << "2. Add Magazine" << endl;
            cout << "3. Display Items" << endl;
            cout << "4. Borrow Book" << endl;
            cout << "5. Return Book" << endl;
            cout << "Enter option: ";

            cin >> option;

            if (option == 1) {
                int id;
                string title, author;

                cout << "Enter Book ID: ";
                cin >> id;

                cin.ignore(10000, '\n');

                cout << "Enter Book Title: ";
                getline(cin, title);

                cout << "Enter Author: ";
                getline(cin, author);

                library.addBook(id, title, author);
            }
            else if (option == 2) {
                int id, issue;
                string title;

                cout << "Enter Magazine ID: ";
                cin >> id;

                cin.ignore(10000, '\n');

                cout << "Enter Magazine Title: ";
                getline(cin, title);

                cout << "Enter Issue Number: ";
                cin >> issue;

                library.addMagazine(id, title, issue);
            }
            else if (option == 3) {
                library.displayItems();
            }
            else if (option == 4) {
                int studentID, itemID;

                cout << "Enter Student ID: ";
                cin >> studentID;

                cout << "Enter Book ID: ";
                cin >> itemID;

                library.borrowBook(studentID, itemID);
            }
            else if (option == 5) {
                int studentID, itemID;

                cout << "Enter Student ID: ";
                cin >> studentID;

                cout << "Enter Book ID: ";
                cin >> itemID;

                library.returnBook(studentID, itemID);
            }
            else {
                cout << "Invalid option!" << endl;
            }

            break;
        }

        // Manage Students
        case 2: {
            int option;

            cout << "\n===== Manage Students =====" << endl;
            cout << "1. Register Student" << endl;
            cout << "2. Display Students" << endl;
            cout << "Enter option: ";

            cin >> option;

            if (option == 1) {
                int id;
                string name;

                cout << "Enter Student ID: ";
                cin >> id;

                cin.ignore(10000, '\n');

                cout << "Enter Student Name: ";
                getline(cin, name);

                library.addStudent(id, name);
            }
            else if (option == 2) {
                library.displayStudents();
            }
            else {
                cout << "Invalid option!" << endl;
            }

            break;
        }

        case 3:
            cout << "\nThank you for using the Library System!" << endl;
            break;

        default:
            cout << "Invalid choice! Try again." << endl;
        }

    } while (choice != 3);

    return 0;
}
