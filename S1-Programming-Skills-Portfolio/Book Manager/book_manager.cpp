// book_manager.cpp
// Simple library manager: load/save books from a CSV file and let the user
// view, search, borrow, and return books via a text menu.

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

struct Book {
    std::string title, author, id;
    int pages;
    bool borrowed;
};

// --- Helper functions ---

std::string toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

int readInt() {
    int val;
    while (!(std::cin >> val)) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid input, try again: ";
    }
    std::cin.ignore(1000, '\n');
    return val;
}

// --- File operations ---

std::vector<Book> loadBooks(const std::string& filename) {
    std::vector<Book> books;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filename << "\n";
        return books;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Book b;
        std::string pages, borrowed;

        std::getline(ss, b.title,  ',');
        std::getline(ss, b.author, ',');
        std::getline(ss, pages,    ',');
        std::getline(ss, b.id,     ',');
        std::getline(ss, borrowed, ',');

        try { b.pages = std::stoi(pages); } catch (...) { b.pages = 0; }
        b.borrowed = (borrowed == "true");

        books.push_back(b);
    }

    return books;
}

void saveBooks(const std::string& filename, const std::vector<Book>& books) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not save books.\n";
        return;
    }

    for (const auto& b : books) {
        file << b.title  << ","
             << b.author << ","
             << b.pages  << ","
             << b.id     << ","
             << (b.borrowed ? "true" : "false") << "\n";
    }
}

// --- Display functions ---

void displayBooks(const std::vector<Book>& books) {
    std::cout << "\n--- Book List ---\n";
    for (const auto& b : books) {
        std::cout << "[" << b.id << "] "
                  << b.title << " by " << b.author
                  << " (" << b.pages << " pages)"
                  << " - " << (b.borrowed ? "Borrowed" : "Available") << "\n";
    }
}

void searchBooks(const std::vector<Book>& books, const std::string& query) {
    std::string q = toLower(query);
    bool found = false;

    for (const auto& b : books) {
        bool titleMatch  = toLower(b.title).find(q)  != std::string::npos;
        bool authorMatch = toLower(b.author).find(q) != std::string::npos;

        if (titleMatch || authorMatch) {
            std::cout << "[" << b.id << "] "
                      << b.title << " by " << b.author
                      << " - " << (b.borrowed ? "Borrowed" : "Available") << "\n";
            found = true;
        }
    }

    if (!found) {
        std::cout << "No books found.\n";
    }
}

// --- Borrow / Return ---

// Finds a book by exact ID or partial title. Returns nullptr if not found.
Book* findBook(std::vector<Book>& books, const std::string& input) {
    // Try exact ID match first
    for (auto& b : books) {
        if (b.id == input) {
            return &b;
        }
    }

    // Try partial title match (case-insensitive)
    std::string q = toLower(input);
    std::vector<Book*> matches;

    for (auto& b : books) {
        if (toLower(b.title).find(q) != std::string::npos) {
            matches.push_back(&b);
        }
    }

    if (matches.size() == 1) {
        return matches[0];
    }

    if (matches.size() > 1) {
        std::cout << "Multiple matches found, please use the book ID:\n";
        for (const auto& m : matches) {
            std::cout << "  [" << m->id << "] " << m->title << "\n";
        }
    }

    return nullptr;
}

void borrowBook(std::vector<Book>& books, const std::string& input) {
    Book* b = findBook(books, input);

    if (b == nullptr) {
        std::cout << "Book not found.\n";
        return;
    }

    if (b->borrowed) {
        std::cout << "\"" << b->title << "\" is already borrowed.\n";
        return;
    }

    b->borrowed = true;
    std::cout << "\"" << b->title << "\" has been borrowed.\n";
}

void returnBook(std::vector<Book>& books, const std::string& input) {
    Book* b = findBook(books, input);

    if (b == nullptr) {
        std::cout << "Book not found.\n";
        return;
    }

    if (!b->borrowed) {
        std::cout << "\"" << b->title << "\" is not currently borrowed.\n";
        return;
    }

    b->borrowed = false;
    std::cout << "\"" << b->title << "\" has been returned.\n";
}

// --- Main ---

int main() {
  try {
    const std::string filename = "bookData.txt";
    std::vector<Book> books = loadBooks(filename);

    int choice;
    do {
        std::cout << "\n1. View all books\n"
                     "2. Search\n"
                     "3. Borrow a book\n"
                     "4. Return a book\n"
                     "0. Exit\n"
                     "Choice: ";
        choice = readInt();

        if (choice == 1) {
            displayBooks(books);

        } else if (choice == 2) {
            std::string query;
            std::cout << "Search by title or author: ";
            std::getline(std::cin, query);
            if (query.empty()) {
                std::cout << "Please enter a search term.\n";
            } else {
                searchBooks(books, query);
            }

        } else if (choice == 3) {
            std::string input;
            std::cout << "Enter book ID or title to borrow: ";
            std::getline(std::cin, input);
            if (input.empty()) {
                std::cout << "Please enter a book ID or title.\n";
            } else {
                borrowBook(books, input);
                saveBooks(filename, books);
            }

        } else if (choice == 4) {
            std::string input;
            std::cout << "Enter book ID or title to return: ";
            std::getline(std::cin, input);
            if (input.empty()) {
                std::cout << "Please enter a book ID or title.\n";
            } else {
                returnBook(books, input);
                saveBooks(filename, books);
            }
        }

    } while (choice != 0);

  } catch (const std::exception& e) {
      std::cerr << "Unexpected error: " << e.what() << "\n";
      return 1;
  }

    return 0;
}
