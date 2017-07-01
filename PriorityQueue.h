/*
 * PriorityQueue.h
 *
 */

#include "Event.h"
#include "EmptyDataCollectionException.h"
#include <string>
#include <iostream>

using namespace std;
#define SIZE 5


template <class ElementType>
class PriorityQueue {
    
private:
    
    // We must complete this section.
    ElementType array[SIZE];
    int numOfEle;
    int front;
    int back;
    void enqueueFrontGEBack(const ElementType& newElement); //enqueue when front is great/equal to back
    void enqueueFrontLTBack(const ElementType& newElement); //enqueue when front is less than back
    
public:
    
    // Let's put our constructor(s) and destructor (if any) ***here***.
    PriorityQueue<ElementType>();
    
    /******* Public Interface - START - *******/
    
    // Description: Returns the number of elements in the Priority Queue.
    // (This method eases testing.)
    // Time Efficiency: O(1)
    int getElementCount() const;
    
    // Description: Returns "true" is this Priority Queue is empty, otherwise "false".
    // Time Efficiency: O(1)
    bool isEmpty() const;
    
    // Description: Inserts newElement in sort order.
    //              It returns "true" if successful, otherwise "false".
    // Precondition: This Priority Queue is sorted.
    // Postcondition: Once newElement is inserted, this Priority Queue remains sorted.
    // Time Efficiency: O(n)
    bool enqueue(const ElementType& newElement);
    
    // Description: Removes the element with the "highest" priority.
    //              It returns "true" if successful, otherwise "false".
    // Precondition: This Priority Queue is not empty.
    // Time Efficiency: O(1)
    bool dequeue();
    
    // Description: Returns (a copy of) the element with the "highest" priority.
    // Precondition: This Priority Queue is not empty.
    // Postcondition: This Priority Queue is unchanged.
    // Exceptions: Throws EmptyDataCollectionException if this Priority Queue is empty.
    // Time Efficiency: O(1)
    ElementType peek() const throw(class EmptyDataCollectionException);
    
    /******* Public Interface - END - *******/
    
    // Let's feel free to add other private helper methods to our Priority Queue class.
    bool dequeueAll();
    
    void printQueue();
    
}; // end PriorityQueue

template <class ElementType>
PriorityQueue<ElementType>::PriorityQueue()
{
    numOfEle = 0;
    front = -1;
    back = -1;
}
    
/******* Public Interface - START - *******/

// Description: Returns the number of elements in the Priority Queue.
// (This method eases testing.)
// Time Efficiency: O(1)
template <class ElementType>
int PriorityQueue<ElementType>::getElementCount() const
{
    return numOfEle;
}

// Description: Returns "true" is this Priority Queue is empty, otherwise "false".
// Time Efficiency: O(1)
template <class ElementType>
bool PriorityQueue<ElementType>::isEmpty() const
{
    return (numOfEle == 0);
}

// Description: Inserts newElement in sort order.
//              It returns "true" if successful, otherwise "false".
// Precondition: This Priority Queue is sorted.
// Postcondition: Once newElement is inserted, this Priority Queue remains sorted.
// Time Efficiency: O(n)
template <class ElementType>
bool PriorityQueue<ElementType>::enqueue(const ElementType& newElement)
{
    //check if queue is full
    if(numOfEle == SIZE)
    {
        return false;
    }

    //initial
    if(front == -1 && back == -1)
    {
        front++;
        back++;
        array[back] = newElement;
    }
    else
    { 
        if(back == SIZE-1)
        {
            enqueueFrontGEBack(newElement);
        }
        else
        {
            if(front <= back)
            {
                enqueueFrontGEBack(newElement);
            }
            else
            {
                enqueueFrontLTBack(newElement);
            }
        }
    }

    numOfEle++;
    return true;
}

// Description: Removes the element with the "highest" priority.
//              It returns "true" if successful, otherwise "false".
// Precondition: This Priority Queue is not empty.
// Time Efficiency: O(1)
template <class ElementType>
bool PriorityQueue<ElementType>::dequeue()
{
    if (numOfEle == 0) {
        return false;
    }
    front++;
    if(front == SIZE)
    {
        front = 0;
    }
    numOfEle--;
    return true;
    // if elements are sorted upon insert, they can just be dequeued in order here
}

// Description: Returns (a copy of) the element with the "highest" priority.
// Precondition: This Priority Queue is not empty.
// Postcondition: This Priority Queue is unchanged.
// Exceptions: Throws EmptyDataCollectionException if this Priority Queue is empty.
// Time Efficiency: O(1)
template <class ElementType>
ElementType PriorityQueue<ElementType>::peek() const throw(class EmptyDataCollectionException)
{
//    if (numOfEle == 0){
//        throw EmptyDataCollectionException;
//    }
    // do we need this if we have the class?
    
    return array[front];
}

template <class ElementType>
bool PriorityQueue<ElementType>::dequeueAll()
{
    if(numOfEle == 0)
    {
        return false;
    }
    numOfEle = 0;
    return true;
}

template <class ElementType>
void PriorityQueue<ElementType>::printQueue()
{
    if(front > -1 && back > -1)
    {
        cout << "****" << endl;
        if(front <= back)
        {
            for(int i = front; i <= back; i++)
            {
                cout << array[i] << " -- " << i << endl;
            }
        }
        else
        {
            for(int i = front; i <= SIZE-1; i++)
            {
                cout << array[i] << " -- " << i << endl;
            }
            for(int i = 0; i <= back; i++)
            {
                cout << array[i] << " -- " << i << endl;
            }
        }

        cout << "****" << endl;
    }
}

template <class ElementType>
void PriorityQueue<ElementType>::enqueueFrontGEBack(const ElementType& newElement)
{
    int position = front;
    for(int i = back; i >= front; i--)
    {   
        if(array[i] > newElement)   //might need to overload > for Event
        {
            position = i+1;
            break;
        }
    }
    //set new back position depending on where the current back position is
    if(back == SIZE-1)
    {
        back = 0;
        array[back] = array[SIZE-1];
    }
    else
    {
        back++;
    }
    //shift to the right
    for(int j = back; j > position; j--)
    {
        array[j] = array[j-1];
    }
    array[position] = newElement;
}

template <class ElementType>
void PriorityQueue<ElementType>::enqueueFrontLTBack(const ElementType& newElement)
{
    int position = front;
    bool found = false;
    for(int i = back; i >= 0; i--)
    {
        if(array[i] > newElement)
        {
            position = i+1;
            found = true;
            break;
        }
    }
    for(int j = SIZE-1; j >= front && found == false; j--)
    {
        if(array[j] > newElement)
        {
            if(j == SIZE-1)
            {
                position = 0;
            }
            else
            {
                position = j+1;
            }
            break;
        }
    }
    //shift the elements
    back++;
    if(position < back)
    {
        for(int j = back; j > position; j--)
        {
            array[j] = array[j-1];
        }
    }
    else
    {
        for(int j = back; j > 0; j--)
        {
            array[j] = array[j-1];
        }
        array[0] = array[SIZE-1];
        for(int k = SIZE-1; k > position; k--)
        {
            array[k] = array[k-1];
        }
    }
    array[position]= newElement;
}