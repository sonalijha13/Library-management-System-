
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool isIssued;

    Book() {}
    Book(int i, string t, string a) {
        id = i;
        title = t;
        author = a;
        isIssued = false;
    }

    void display() {
        cout << "ID: " << id << " | Title: " << title << " | Author: " << author
             << " | Status: " << (isIssued ? "Issued" : "Available") << endl;
    }
};

vector<Book> library;

void saveToFile() {
    ofstream file("library.txt");
    for (auto &book : library) {
        file << book.id << "\n"
             << book.title << "\n"
             << book.author << "\n"
             << book.isIssued << "\n";
    }
    file.close();
}

void loadFromFile() {
    ifstream file("library.txt");
    library.clear();
    int id;
    string title, author;
    bool isIssued;
    while (file >> id) {
        file.ignore();
        getline(file, title);
        getline(file, author);
        file >> isIssued;
        Book b(id, title, author);
        b.isIssued = isIssued;
        library.push_back(b);
    }
    file.close();
}

void addBook() {
    int id;
    string title, author;
    cout << "Enter Book ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Book Title: ";
    getline(cin, title);
    cout << "Enter Author Name: ";
    getline(cin, author);
    library.push_back(Book(id, title, author));
    cout << "Book added successfully.\n";
    saveToFile();
}

void displayBooks() {
    if (library.empty()) {
        cout << "No books available.\n";
        return;
    }
    for (auto &book : library) {
        book.display();
    }
}

void searchBook() {
    string keyword;
    cout << "Enter title or author to search: ";
    cin.ignore();
    getline(cin, keyword);
    bool found = false;
    for (auto &book : library) {
        if (book.title.find(keyword) != string::npos ||
            book.author.find(keyword) != string::npos) {
            book.display();
            found = true;
        }
    }
    if (!found) {
        cout << "No matching book found.\n";
    }
}

void issueBook() {
    int id;
    cout << "Enter Book ID to issue: ";
    cin >> id;
    for (auto &book : library) {
        if (book.id == id) {
            if (!book.isIssued) {
                book.isIssued = true;
                cout << "Book issued successfully.\n";
                saveToFile();
            } else {
                cout << "Book already issued.\n";
            }
            return;
        }
    }
    cout << "Book not found.\n";
}

void returnBook() {
    int id;
    cout << "Enter Book ID to return: ";
    cin >> id;
    for (auto &book : library) {
        if (book.id == id) {
            if (book.isIssued) {
                book.isIssued = false;
                cout << "Book returned successfully.\n";
                saveToFile();
            } else {
                cout << "This book was not issued.\n";
            }
            return;
        }
    }
    cout << "Book not found.\n";
}

int main() {
    loadFromFile();
    int choice;

    do {
        cout << "\n=== Library Management System ===\n";
        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Book\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: issueBook(); break;
            case 5: returnBook(); break;
            case 6: cout << "Exiting... Data saved.\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 6);

    return 0;
}
