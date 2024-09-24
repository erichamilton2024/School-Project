#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <fstream>

class user
{
public:
  // OPERATOR OVERLOADING
  const user &operator=(const user& otherUser); // Copies the user to another user
  bool operator==(const user &) const;
  // Equality operator. Used for sorting.
  // Postcondition: Returns true if the usernames are the same.
  friend std::ifstream& operator>> (std::ifstream& inFile, user& newUser);
  // Insertion stream operator. Used for creating a new user.
  // GET FUNCTIONS
  int getBookIndex(std::string bookName) const; // Returns the index of bookName in the user's book list.
  // Postcondition: Returns the index of the book in the book array. If it doesn't exist, returns -1.

  std::string getUsername() const; // Returns the username of the user.
  // Postcondition: Returns the std::string of the username.

  // SET FUNCTIONS
  void setUsername(std::string str); // Sets the username of the user
  // Postcondition: username = str

  void setPassword(std::string str); // Sets the password of the user
  // Postcondition: password = str

  void setAdmin(bool ad = true); // Sets admin status of the user
  // Postcondition: admin = ad;

  // VALIDATION FUNCTIONS
  bool hasBook(std::string bookName) const; // Checks to see if this user has a book of bookName.
  // Postcondition: Returns true if bookName is in the user's book list, false otherwise.

  bool isAdmin() const; // Checks to see if this user is an admin.
  // Postcondition: Returns true if this user is an admin, false otherwise.

  bool hasMaxBooks() const; // Checks to see if the user has the maximum number of books.
  // Postcondition: Returns true if the user has the maximum number of books, false otherwise.

	bool hasNoBooks() const; // Checks to see if the user has no books.
	// Postcondition: Returns true if the user has no books, false otherwise.
	
  bool validate(std::string pass) const; // Checks to see if password is same as user.
  // Postcondition: Returns true if pass is the same as password.

  // BOOK FUNCTIONS

  void addBook(std::string bookName); // Adds a book to the user's inventory.
  void removeBook(std::string bookName); // Removes a book from the user's inventory if it has the book.

  // PRINT FUNCTIONS

  void printBooks() const; // Prints out the user's books.
  void printName() const; // Prints the username of the user
  void printInfo(std::ofstream& outFile); // Prints the user's data to a file.

  user(std::string name = "", std::string pass = "", bool ad = false); // Basic constructor function.
  user(const user& otherUser); // Copy constructor.

private:
  bool admin; // Whether or not the user is an admin.
  std::string password;
  std::string username; // Username of the user.
  std::string books[5]; // String array of books the user owns.
  int bookCount = 0; // Count of how many users the book has.

  void copyUser(const user& otherUser); // Private function for copying users.
};

// OPERATOR OVERLOADING

const user& user::operator=(const user& otherUser) {
    if (this != &otherUser)
      copyUser(otherUser);

    return *this;
}//end assignment operator

bool user::operator==(const user& otherUser) const {
    return otherUser.getUsername() == username;
}//end equality operator

std::ifstream& operator>>(std::ifstream& inFile, user& newUser)
{
    char adminValue; // Character to read the admin value
    std::string line; // String value to read lines

    inFile >> newUser.username >> newUser.password >> adminValue; // Get username, password, and admin value
		
    newUser.admin = (adminValue == '1'); // Convert admin value to a boolean variable based on the given character

    inFile.ignore(999, '\n'); // Ignore until the next line

    // Iterate through the book lines until a zero is reached
    std::getline(inFile, line);
    while (line != "0") {
        newUser.addBook(line);
        std::getline(inFile, line);
    }//end while

    return inFile;
}//end insertion operator

// GET FUNCTIONS

std::string user::getUsername() const
{ return username; }//end getUsername

int user::getBookIndex(std::string bookName) const {
  for (int i = 0; i < 5; i++)
    if (books[i] == bookName)
      return i;

  return -1;
}//end getBookIndex

// SET FUNCTIONS

void user::setUsername(std::string str)
{ username = str; }//end setUsername

void user::setPassword(std::string str)
{ password = str; }//end setPassword

void user::setAdmin(bool ad)
{ admin = ad; }// end setAdmin

// VALIDATION FUNCTIONS

bool user::hasBook(std::string bookName) const 
{ return (getBookIndex(bookName) != -1); }//end hasBook

bool user::isAdmin() const 
{ return admin; }//end isAdmin

bool user::hasMaxBooks() const
{ return bookCount == 5; }//end hasMaxBooks

bool user::hasNoBooks() const
{ return bookCount == 0; }//end hasNoBooks

bool user::validate(std::string pass) const
{ return pass == password; }//end validate

void user::addBook(std::string bookName) {
  if (!hasBook(bookName) && !hasMaxBooks()) // If the user doesn't have the book already and book count isn't full
	{
    int i = 0;
    while(books[i] != "")
    { i++; }//end while
    books[i] = bookName;
    bookCount += 1; // Increment book count by 1
	}
}//end addBook

void user::removeBook(std::string bookName) {
  int index = getBookIndex(bookName);
  if (index >= 0) { // If the index is valid
    books[index] = ""; // Remove the book from the array
    bookCount -= 1;
  } else
    std::cout << "You do not have this book." << std::endl;
}//end removeBook

void user::printBooks() const {
  for (int i = 0; i < 5; i++)
    if (books[i] != "")
      std::cout << books[i] << std::endl;
}//end printBooks

void user::printName() const {
  std::cout << username << std::endl;
}//end printName

void user::printInfo(std::ofstream& outFile) {
  // Print out basic information such as user, password, and whether or not they're an admin
  // on the first line
  outFile << username << " " << password << " " << admin << std::endl;

  // Print out books on the following line
  for (int i = 0; i < 5; i++)
    if (books[i] != "")
      outFile << books[i] << std::endl;

  // End with a zero to indicate book reading is finished
  outFile << "0";
}

user::user(std::string name, std::string pass, bool ad) {
  username = name;
  password = pass;
  admin = ad;
}//end constructor

user::user(const user& otherUser) {
    copyUser(otherUser);
}//end copy constructor

void user::copyUser(const user& otherUser)
{
  username = otherUser.username; // Copy the user's username, password, and admin
  password = otherUser.password;
  admin = otherUser.admin;
	
	for(int i = 0; i < 5; i++) // initialize books array
		books[i] = "";
	bookCount = 0;
	
  for (int i = 0; i < 5; i++) // copy from other books array
	{
    if (otherUser.books[i] != "")
      addBook(otherUser.books[i]);
	}
}//end copy function

#endif