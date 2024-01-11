#ifndef STACK_H
#define STACK_H

#include <stdexcept>

class stack
{

private:

    // Stores int values of stack
    int *stackArray = nullptr;

    // Size of stackArray (amount of elements currently)
    int size;

    // Resize array + 1
    void resize(int direction);

public:
    /*
    Precondition: Must be called empty
    Postcodition: Will set all values to default (0).
    */
    stack();

    /*
    Precondition: Must have passed a instantiation of queue
    Postcodition: Will deallocate dynamically-allocated queueArray.
    */
    ~stack();

    /*
    Precondition: Must receive a integer value; must have allocated stackArray
    Postcodition: Places int in stackArray at size (last open space) and resizes
    to +1 if already maxed.
    */
    void push(int value);

    /*
    Precondition: Must have allocated stackArray of at least size 1
    Postcodition: Will return removed value at 0 and will resize stackArray -1.
    */
    int pop();

    /*
    Precondition: Must have a instatiated member of the class
    Postcodition: Returns 1 if empty; 0 if not.
    */
    bool isEmpty();

    /*
    Precondition: Must have a instatiated stackArray
    Postcodition: Flips the contents of the array 0 = last and last = 0.
    */
    void flip();

    /*
    Precondition: Must have passed a instantiation of another stack
    Postcodition: Will copy all data from other into returned stack;
    having the array of values be copied in a new spot in memory.
    */
    stack(const stack &other);

    /*
    Precondition: Must have passed a instantiation of another stack (not itself)
    Postcodition: Will copy all data of other into returned stack; clearing and
    remapping its values to other stack as well as its size and capacity state.
    */
    stack &operator=(const stack &other);
};

#endif