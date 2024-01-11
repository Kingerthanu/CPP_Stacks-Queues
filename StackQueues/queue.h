#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>

class queue
{

private:
    // Holds integers
    int *queueArray = nullptr;

    // Size of queueArray (amount of elements currently)
    int size;

    // Resize array + amount (1 or -1 to downsize)
    void resize(int newCapacity);

public:

    /*
    Precondition: Must be called empty
    Postcodition: Will set all values to default (0).
    */
    queue();

    /*
    Precondition: Must have passed a instantiation of queue
    Postcodition: Will deallocate dynamically-allocated queueArray.
    */
    ~queue();

    /*
    Precondition: Must receive a integer value; must have allocated queueArray
    Postcodition: Places int in queueArray at size (last open space) and resizes
    to +1 if already maxed.
    */
    void enqueue(int value);

    /*
    Precondition: Must have allocated queueArray of at least size 1
    Postcodition: Will return removed value at 0 and will resize queueArray -1.
    */
    int dequeue();

    /*
    Precondition: Must have a instatiated member of the class
    Postcodition: Returns 1 if empty; 0 if not.
    */
    bool isEmpty();

    /*
    Precondition: Must have a instatiated queueArray
    Postcodition: Flips the contents of the array 0 = last and last = 0.
    */
    void flip();

    /*
    Precondition: Must have passed a instantiation of another queue
    Postcodition: Will copy all data from other into returned queue;
    having the array of values be copied in a new spot in memory.
    */
    queue(const queue &other);

    /*
    Precondition: Must have passed a instantiation of another queue (not itself)
    Postcodition: Will copy all data of other into returned queue; clearing and
    remapping its values to other queue as well as its size and capacity state.
    */
    queue &operator=(const queue &other);
 
};

#endif