#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Book {
private:
    string title;
    string author;
    int copies;

    static int validCopies(int value) {
        return value < 0 ? 0 : value;
    }

public:
    Book() : Book("", "Unknown", 0) {}

    Book(const string& bookTitle)
        : Book(bookTitle, "Unknown", 1) {}

    Book(const string& bookTitle, const string& bookAuthor, int copyCount)
        : title(bookTitle), author(bookAuthor), copies(validCopies(copyCount)) {}

    void display() const {
        cout << "Title: " << (title.empty() ? "Untitled" : title)
             << ", Author: " << author
             << ", Copies: " << copies << '\n';
    }
};

int main() {
    Book emptyBook;
    Book donatedBook("The Alchemist");
    Book fullBook("C++ Primer", "Stanley Lippman", 5);
    Book invalidBook("Invalid Book", "Unknown", -3);

    cout << "Default constructor:\n";
    emptyBook.display();

    cout << "Title-only constructor:\n";
    donatedBook.display();

    cout << "Parameterized constructor:\n";
    fullBook.display();

    cout << "Negative copies test:\n";
    invalidBook.display();

    // Explicit constructor example:
    // Book b = "C++"; // rejected if a single-argument converting constructor is explicit
    return 0;
}