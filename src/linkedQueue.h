//Header file linkedQueue.h

#ifndef H_linkedQueue
#define H_linkedQueue 

#include <iostream>
#include <cassert>
#include "queueADT.h"

using namespace std;

//Definition of the node
#ifndef nodeTypeDef
#define nodeTypeDef

template <class Type>
struct nodeType
{
  Type info;
  nodeType<Type> *link;
};
#endif


template <class Type>
class linkedQueueType: public queueADT<Type>
{
public:
    const linkedQueueType<Type>& operator=
                    (const linkedQueueType<Type>&); 
      //Overload the assignment operator.

    bool isEmptyQueue() const;
      //Function to determine whether the queue is empty. 
      //Postcondition: Returns true if the queue is empty,
      //               otherwise returns false.

    bool isFullQueue() const;
      //Function to determine whether the queue is full. 
      //Postcondition: Returns true if the queue is full,
      //               otherwise returns false.

    void initializeQueue();
      //Function to initialize the queue to an empty state.
      //Postcondition: queueFront = nullptr; queueRear = nullptr

    Type front() const;
      //Function to return the first element of the queue.
      //Precondition: The queue exists and is not empty.
      //Postcondition: If the queue is empty, the program 
      //               terminates; otherwise, the first 
      //               element of the queue is returned.

    Type back() const;
      //Function to return the last element of the queue.
      //Precondition: The queue exists and is not empty.
      //Postcondition: If the queue is empty, the program 
      //               terminates; otherwise, the last 
      //               element of the queue is returned.

    void addQueue(const Type& queueElement);
      //Function to add queueElement to the queue.
      //Precondition: The queue exists and is not full.
      //Postcondition: The queue is changed and queueElement
      //               is added to the queue.

    void deleteQueue();
      //Function  to remove the first element of the queue.
      //Precondition: The queue exists and is not empty.
      //Postcondition: The queue is changed and the first 
      //               element is removed from the queue.

    linkedQueueType(); 
      //Default constructor

    linkedQueueType(const linkedQueueType<Type>& otherQueue); 
      //Copy constructor

    ~linkedQueueType(); 
      //Destructor

private:
    nodeType<Type> *queueFront; //pointer to the front of 
                                //the queue
    nodeType<Type> *queueRear;  //pointer to the rear of 
                                //the queue
    void copyQueue(const linkedQueueType<Type>& otherQueue);
    // Private function to copy the queue into another queue
};

    //Default constructor
template <class Type>
linkedQueueType<Type>::linkedQueueType() 
{
    queueFront = nullptr; //set front to nullptr
    queueRear = nullptr;  //set rear to nullptr
} //end default constructor

template <class Type>
bool linkedQueueType<Type>::isEmptyQueue() const
{
    return (queueFront == nullptr);
} //end isEmptyQueue

template <class Type>
bool linkedQueueType<Type>::isFullQueue() const
{
    return false;
} //end isFullQueue

template <class Type>
void linkedQueueType<Type>::initializeQueue()
{
    nodeType<Type> *temp;

    while (queueFront!= nullptr)  //while there are elements 
                                  //left in the queue
    {
        temp = queueFront;  //set temp to point to the 
                            //current node
        queueFront = queueFront->link;  //advance first to  
                                        //the next node
        delete temp;    //deallocate memory occupied by temp
    }

    queueRear = nullptr;  //set rear to nullptr
} //end initializeQueue


template <class Type>
void linkedQueueType<Type>::addQueue(const Type& newElement)
{
    nodeType<Type> *newNode;

    newNode = new nodeType<Type>;   //create the node

    newNode->info = newElement; //store the info
    newNode->link = nullptr;    //initialize the link 
                                //field to nullptr

    if (queueFront == nullptr) //if initially the queue is empty
    {
        queueFront = newNode;
        queueRear = newNode;
    }
    else        //add newNode at the end
    {
        queueRear->link = newNode;
        queueRear = queueRear->link;
    }
}//end addQueue

template <class Type>
Type linkedQueueType<Type>::front() const
{
    assert(queueFront != nullptr);
    return queueFront->info; 
} //end front

template <class Type>
Type linkedQueueType<Type>::back() const
{
    assert(queueRear!= nullptr);
    return queueRear->info;
} //end back

template <class Type>
void linkedQueueType<Type>::deleteQueue()
{
    nodeType<Type> *temp;

    if (!isEmptyQueue())
    {
        temp = queueFront;  //make temp point to the 
                            //first node
        queueFront = queueFront->link; //advance queueFront 

        delete temp;    //delete the first node

        if (queueFront == nullptr) //if after deletion the 
                                   //queue is empty
            queueRear = nullptr;   //set queueRear to nullptr
    }
    else
        cout << "Cannot remove from an empty queue" << endl;
}//end deleteQueue


    //Destructor
template <class Type>
linkedQueueType<Type>::~linkedQueueType() 
{
    initializeQueue();
} //end destructor


template <class Type>
const linkedQueueType<Type>& linkedQueueType<Type>::operator=
                    (const linkedQueueType<Type>& otherQueue)
{
    if (this != &otherQueue) //avoid self-copy
      copyQueue(otherQueue);
			
    return *this;
} //end assignment operator


  //copy constructor
template <class Type>
linkedQueueType<Type>::linkedQueueType
                 (const linkedQueueType<Type>& otherQueue) 
{
    copyQueue(otherQueue);
}//end copy constructor

// copy function
template <class Type>
void linkedQueueType<Type>::copyQueue(const linkedQueueType<Type>& otherQueue)
{
    nodeType<Type> *current;

    queueFront = nullptr;
    queueRear = nullptr;

    if (isEmptyQueue() == false) // If the queue is not empty, initialize it and make it empty
      initializeQueue();

    if (otherQueue.queueFront != nullptr) // If the other queue is not empty,
    {
      current = otherQueue.queueFront; // Set the current to the queue front

      addQueue(current->info); // Add the first of the other queue to the new queue

      while (current->link != nullptr) // Iterate through this until we go through the whole queue
      {
          current = current->link;
          addQueue(current->info);
      }//end while
    }//end if
}//end copy function

#endif