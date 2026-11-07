# Book Manager

A C++ command-line library management system for viewing, searching, borrowing, and returning books.

## How it works
- Loads books from `bookData.txt` on startup
- Lets the user view all books, search by title or author, borrow, or return a book
- Saves changes back to `bookData.txt` after every borrow/return

## Files
- `book_manager.cpp` — main program
- `bookData.txt` — book database (CSV format: `title,author,pages,id,borrowed`)

## How to run
```bash
g++ book_manager.cpp -o book_manager
./book_manager
```

## Menu options
```
1. View all books
2. Search by title or author
3. Borrow a book
4. Return a book
0. Exit
```

## Example
```
1. View all books
--- Book List ---
[B001] The Great Gatsby by F. Scott Fitzgerald (180 pages) - Available
[B002] 1984 by George Orwell (328 pages) - Borrowed
```
