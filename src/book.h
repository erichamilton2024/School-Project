#ifndef BOOK_H
#define BOOK_H

#include "linkedQueue.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class book {
public:
  // OPERATOR OVERLOADING
  const book &operator=(const book &); // Assignment operator
  bool operator==(const book &) const;
  // Equality operator. Used for sorting.
  // Postcondition: Returns true if the titles are the same.
  bool operator!=(const book &) const;
  // Inequality operator. Used for sorting.
  // Postcondition: Returns true if the titles are not the same.
  bool operator>=(const book &) const;
  // Greater than or equal to operator. Used for sorting.
  // Postcondition: Returns true if the title of this book is greater than or
  // equal to the other book.
  bool operator>(const book &) const;
  // Greater than operator. Used for sorting.
  // Postcondition: Returns true if the title of this book is greater than the other book.
  friend ifstream& operator>> (ifstream& inFile, book& newBook);
  // Insertion stream operator. Used for creating a new book.

  // SET FUNCTIONS
  void setTitle(std::string t);           // Function to set title
  void setAuthor(std::string name);       // Function to set author
  void setDate(int date);            // Function to set datePublished
  void setCatalogNumber(double num); // Function to set catalogNumber

  // GET FUNCTIONS
  std::string getTitle() const;         // Function to get title
  std::string getAuthor() const;        // Function to get author name
  int getDate() const;             // Function to get datePublished
  double getCatalogNumber() const; // Function to get catalog number
  linkedQueueType<std::string> getQueue() const; // Function to get the queue

  // BORROWING QUEUE FUNCTIONS
  bool isBorrowed() const; // Function to get if the book is borrowed or not
  std::string currentBorrower() const; // Function to return the name of the current book holder
  void addBorrower(std::string); // Function to add a borrower to the queue
  void removeBorrower(); // Function to remove the first borrower from the queue

  // PRINT FUNCTIONS
  void printTitle() const; // Function to print book title
  void printQueue(ofstream& outFile) const; // Function to print the book's full queue

  void printInfo() const; // Function to print book information to console
  void printInfo(ofstream& outFile) const; // Function to print book information to an output file

  // Constructor. Borrower always starts off as an empty string, and the book
  // always starts off as not borrowed
  book(std::string newTitle = "", std::string name = "", int publishDate = 1990,
       double num = 0);

  // Copy constructor. Makes an identical book to the book provided in the copy
  // constructor.
  book(const book &);

private:
  std::string title, author; // Book title and author
  int datePublished = 1990;       // Date published
  // not needed since we have a queue // bool borrowed = false; // Boolean value
  // to determine borrow status (implemented in phase 2)
  double catalogNumber; // Book catalog number, Dewey decimal system
  linkedQueueType<std::string> borrowerQueue;

  void copyBook(const book &); // Private function for copying books.
};

// OPERATOR OVERLOADING
const book &book::operator=(const book &otherBook) {
  if (this != &otherBook) // Checks self-assignment
  {
    copyBook(otherBook);
  }

  return *this;
} // end assignment operator

bool book::operator==(const book &otherBook) const {
  return (title == otherBook.getTitle());
} // end equality operator

bool book::operator!=(const book &otherBook) const {
  return (title != otherBook.getTitle());
} // end inequality operator

bool book::operator>=(const book &otherBook) const {
  return (title >= otherBook.getTitle());
} // end gtoe operator

bool book::operator>(const book &otherBook) const {
  return (title > otherBook.getTitle());
} // end gt operator

ifstream& operator>>(ifstream& inFile, book& newBook)
{
  std::string line; // String variable for lines that need to be
                    // converted to numbers
  std::string borrower; // String variable for borrower

  std::getline(inFile, newBook.title); // Read a line for title and author
  std::getline(inFile, newBook.author);
  
  std::getline(inFile, line); // Read a line for the year
  newBook.datePublished = std::stoi(line);

  std::getline(inFile, line); // Read a line for the catalog number
  newBook.catalogNumber = std::stod(line);

  inFile >> borrower; // Iterate through the borrowers until it reaches a "0" string
  while (borrower != "0") {
      newBook.addBorrower(borrower);
      inFile >> borrower;
  }//end while
  inFile.ignore(999, '\n'); // Ignore until the next line

  return inFile;
} // end insertion operator

// SET FUNCTIONS

void book::setTitle(std::string t) { title = t; } // end setTitle

void book::setAuthor(std::string name) { author = name; } // end setAuthor

void book::setDate(int date) { datePublished = date; } // end setDate

void book::setCatalogNumber(double num) {
  catalogNumber = num;
} // end setCatalogNumber

// GET FUNCTIONS

std::string book::getTitle() const
{ return title; } // end getTitle

std::string book::getAuthor() const
{ return author; } // end getAuthor

int book::getDate() const
{ return datePublished; } // end getDate

double book::getCatalogNumber() const 
{ return catalogNumber; } // end getCatalogNumber

linkedQueueType<string> book::getQueue() const
{ return borrowerQueue; }// end getQueue

// BORROWING QUEUE FUNCTIONS
bool book::isBorrowed() const
{ return !(borrowerQueue.isEmptyQueue()); } // end isBorrowed

void book::addBorrower(std::string borrower)
{ borrowerQueue.addQueue(borrower); } // end addBorrower

void book::removeBorrower()
{ borrowerQueue.deleteQueue(); } // end removeBorrower

std::string book::currentBorrower() const
{
	if(!borrowerQueue.isEmptyQueue())
		return borrowerQueue.front();
	else
		return "";
}

// PRINT FUNCTIONS
void book::printTitle() const
{ cout << title << endl; } // end printTitle

void book::printQueue(ofstream &outFile) const
{ 
  if (!borrowerQueue.isEmptyQueue()) // If the borrower queue is not empty 
  { // Create a temporary queue and iterate through it to print out the queue
    linkedQueueType<std::string> tempQueue = borrowerQueue;

    outFile << tempQueue.front();
    tempQueue.deleteQueue();

    while (!tempQueue.isEmptyQueue()) {
        outFile << " " << tempQueue.front();
        tempQueue.deleteQueue();
    }//end while

    outFile << " 0";
  } else
    outFile << "0";
}//end printQueue function

void book::printInfo() const
{
	cout << title << endl << author << endl << datePublished << endl
			 << catalogNumber << endl;
}

void book::printInfo(ofstream &outFile) const
{
  outFile << title << endl << author << endl << datePublished << endl <<
  catalogNumber << endl;
  printQueue(outFile);
}//end printInfo function

// CONSTRUCTORS

book::book(std::string newTitle, std::string name, int publishDate, double num) {
  setTitle(newTitle);
  setAuthor(name);
  setDate(publishDate);
  setCatalogNumber(num);
  borrowerQueue.initializeQueue();
} // end book constructor

book::book(const book &otherBook) {
  copyBook(otherBook);
} // end copy constructor

// PRIVATE FUNCTIONS

void book::copyBook(const book &otherBook) {
  title = otherBook.getTitle();
  author = otherBook.getAuthor();
  datePublished = otherBook.getDate();
  catalogNumber = otherBook.getCatalogNumber();
  borrowerQueue = otherBook.getQueue();
} // end copyBook

#endif