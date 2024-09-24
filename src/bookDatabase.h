#ifndef BOOKDATABASE_H
#define BOOKDATABASE_H

#include "binarySearchTree.h"
#include "book.h"

#include <string>
#include <fstream>
#include <cassert>

const std::string DEFAULT_FILE_BOOK_DATABASE = "datafiles/books.txt";

class bookDatabase : public bSearchTreeType<book>
{
public:
    book getBookFromTitle(std::string title) const;
    // Function that gets a book based on the given title string.
    // Precondition: The book exists in the book database.
    // Postcondition: Returns a book if its found, returns an empty book if not.

    // LOAN FUNCTIONS
    void printAllLoans() const;

    // BORROW/RETURN FUNCTIONS
    void borrow(std::string title, std::string user);
    // Function that adds a user to the borrower queue of a book
    // in the database.
    // Postcondition: If the book exists, then user is added
    // to the borrower queue of the book.

    // DATA MANAGEMENT FUNCTIONS
    void saveToFile(std::string fileName = DEFAULT_FILE_BOOK_DATABASE);
    void loadFromFile(std::string fileName = DEFAULT_FILE_BOOK_DATABASE);
private:
    void printLoan(binaryNodeType<book> *b) const; // Inorder traversal to print loans
    void printBook(binaryNodeType<book> *b, ofstream& outFile) const; // Preorder traversal to print books
};

// Custom search function that returns a book if its found, and an empty book when its not.
book bookDatabase::getBookFromTitle(std::string title) const 
{
    binaryNodeType<book> *current; // Declare a node type of book.

    if (root == nullptr)
        cout << "Cannot search an empty tree." << endl;
    else
    { 
       current = root;

       while (current != nullptr)
        {
            if ((current->info).getTitle() == title)
                return current->info; // Return the book if its found.
            else if ((current->info).getTitle() > title)
                current = current->lLink; // If not, move to the next node.
            else
                current = current->rLink;
        }//end while
    }//end else

    // If the book isn't found, return an empty book.
    return book();
}//end getBookFromTitle

// LOAN FUNCTIONS
// Custom inorder traversal that prints all loans from books.
void bookDatabase::printAllLoans() const {
    printLoan(root);
}//end printALlLoans

// In order traversal that prints the loan of the book, then iterates to the next book.
void bookDatabase::printLoan(binaryNodeType<book> *b) const {
    if (b != nullptr)
    {
        printLoan(b->lLink);
        if (b->info.isBorrowed())
        {
            b->info.printTitle();
            cout << "Current Borrower: " << b->info.currentBorrower() << endl;
        }
        printLoan(b->rLink);
    }
}//end printLoan

// BORROW/RETURN FUNCTIONS
void bookDatabase::borrow(std::string title, std::string user)
{
  binaryNodeType<book> *current; // Declare a node type of book.
  if (root == nullptr)
        cout << "Cannot borrow from an empty library." << endl;
  else
  { 
    current = root;
      while (current != nullptr)
      {
          if ((current->info).getTitle() == title)
          {
            (current->info).addBorrower(user); // Add borrower to the book if its found.
            break;
          }
          else if ((current->info).getTitle() > title)
            current = current->lLink; // If not, move to the next node.
          else
            current = current->rLink;
      }//end while
  }
}

// SAVE FUNCTIONS
void bookDatabase::saveToFile(std::string fileName) {
    std::ofstream outFile;
    outFile.open(fileName); // Open the file from the file name

    assert(outFile.is_open()); // Assert that the file is open and was found

    if (root != nullptr) {
        root->info.printInfo(outFile);
        printBook(root->lLink, outFile);
        printBook(root->rLink, outFile);
    }

    outFile << std::endl << "-999";
    outFile.close(); // Close the file
}//end saveToFile

// Private function that performs preorder traversal starting at node b
void bookDatabase::printBook(binaryNodeType<book> *b, ofstream& outFile) const {
    if (b != nullptr)
    {
        outFile << std::endl << std::endl;
        b->info.printInfo(outFile);
        printBook(b->lLink, outFile);
        printBook(b->rLink, outFile);
    }
}

// LOAD FUNCTIONS
void bookDatabase::loadFromFile(std::string fileName) {
    std::ifstream inFile;
    inFile.open(fileName);

    assert(inFile.is_open());

    std::string line;
    while (line != "-999") {
        book newBook;
        inFile >> newBook; // Read the book then insert it
        insert(newBook);

        std::getline(inFile, line); // Read the next line to see if its -999
    }

    inFile.close(); // Close the file
}

#endif