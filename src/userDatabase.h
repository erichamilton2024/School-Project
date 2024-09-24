#ifndef USERDATABASE_H
#define USERDATABASE_H

#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <cassert>

#include "user.h"

const std::string DEFAULT_FILE_USER_DATABASE = "datafiles/users.txt";

class userDatabase
{
public:
  // RETRIEVAL FUNCTIONS
  bool findUser(const std::string& username) const;
  // Function that returns a boolean value based on if the user is found in the database.
  // Postcondition: Returns true if the user is found in the hashmap,
  // otherwise, returns false.
  user getUser(const std::string username) const;
  // Function that returns a user from the map based on a given username.
  // Precondition: A user of username exists within the database.
  // Postcondition: If a user is found, then this returns the user data of the user.
  // Otherwise, this returns an empty user with a warning message displayed.

  // INSERT/REMOVAL FUNCTIONS
  void addUser(user newUser); 
  // Adds a new user to the hashmap / the user database.
  // Precondition: Requires that a user with the username of newUser does not
  // already exist in the database. Otherwise, a new user is not created.
  void updateUser(user updatedUser);
  // Updates the user's data on the map.
  // Precondition: Requires that a user with username exists to replace the data.
  void removeUser(const std::string username);
  // Removes a user from the hashmap based on the provided username.
  // Precondition: A user of the username provided exists in the database.

  // DATA MANAGEMENT FUNCTIONS
  void loadFromFile(std::string fileName = DEFAULT_FILE_USER_DATABASE); // Loads the user database from a file
  void saveToFile(std::string fileName = DEFAULT_FILE_USER_DATABASE); // Saves the user database to a file

  // CONSTRUCTOR
  userDatabase(); // Constructor function
private:
  std::unordered_map<std::string, user> users;
  // The hashmap that stores the users of the database.
  // The key or unique identifier of the user is its username, where
  // the value which the hashmap returns is the user data.
};

// RETRIEVAL FUNCTIONS
bool userDatabase::findUser(const std::string& username) const
{ return users.find(username) != users.end(); }//end findUser

user userDatabase::getUser(const std::string username) const
{ return users.at(username); }//end getUser

// INSERT/REMOVAL FUNCTIONS
void userDatabase::addUser(user newUser)
{
    std::string username = newUser.getUsername();

    if (!findUser(username))
        users.insert({username, newUser});
    else
        std::cout << "User " << username << " already exists." << std::endl;
}//end addUser

void userDatabase::updateUser(user updatedUser)
{
    std::string username = updatedUser.getUsername();

    if (findUser(username))
        users[username] = updatedUser;
    else
        std::cout << "User " << username << " does not exist." << std::endl;
}//end updateUser

void userDatabase::removeUser(const std::string username)
{
    if (findUser(username))
        users.erase(username);
    else
        std::cout << "User " << username << " already does not exist." << std::endl;
}//end removeUser

// DATA MANAGEMENT FUNCTIONS
void userDatabase::loadFromFile(std::string fileName)
{
    std::ifstream inFile; // Open the file
    inFile.open(fileName);

    assert(inFile.is_open()); // Assert the file is open

    std::string line; // Declare line to be read at the end

    while(line != "-999")
    {
        user newUser;
        inFile >> newUser; // Read the user then insert it
        addUser(newUser);

        std::getline(inFile, line);
    }//end while

    inFile.close();
}//end loadFromFile

void userDatabase::saveToFile(std::string fileName)
{
    std::ofstream outFile; // Open the file
    outFile.open(fileName);

    assert(outFile.is_open()); // Assert the file is open

    bool first = true;

    // Iterate through the unordered map and add each user until there are none left
    for(auto i = users.begin(); i != users.end(); i++) {
        if (first == true) // Ensures the first one doesnt produce two lines
            first = false;
        else
            outFile << std::endl << std::endl;

        i->second.printInfo(outFile); // Save this user to the file
    }//end for

    outFile << std::endl << "-999"; // Write a -999 to indicate end of file

    outFile.close();
}//end saveToFile

// CONSTRUCTOR
userDatabase::userDatabase() {}//end constructor

#endif