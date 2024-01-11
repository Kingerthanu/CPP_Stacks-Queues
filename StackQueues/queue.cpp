#include "queue.h"

queue::queue()
{
    // Instantiating as defaults (0)
    this->queueArray = new int[0];
    this->size = 0;
}

queue::queue(const queue &other)
{
    // Copying data from other into this
    this->queueArray = new int[other.size];
    this->size = other.size;

    for (int i = 0; i < this->size; i++){
        this->queueArray[i] = other.queueArray[i];
    }
}

queue::~queue()
{
    // Delete current allocated queue
    delete[] this->queueArray;
}

queue &queue::operator=(const queue &other)
{
    if (this == &other){
        return *this;
    }

    if (this->queueArray != nullptr){
        delete[] this->queueArray;
    }

    if (other.queueArray == nullptr){
        this->size = 0;
        this->queueArray = nullptr;
        return *this;
    }

    this->queueArray = new int[other.size];
    // Set with other values
    this->size = other.size;

    for (int i = 0; i < this->size; i++){
        this->queueArray[i] = other.queueArray[i];
    }
    return *this;
}

void queue::enqueue(int value)
{
    resize(this->size + 1); // add one
    queueArray[size] = value;
    size++;
}

int queue::dequeue()
{
    if (!this->isEmpty()){ // If queue has a element
        int tmp = queueArray[0]; // Temporary variable container
        resize(this->size - 1);  // Decrease size by one because of newly removed value
        size--;
        return tmp;
    }
    else{
        throw std::runtime_error("Stack Underflow of queueArray");
    }
}

bool queue::isEmpty()
{
    return (this->size <= 0); // If size of filled elements is 0 or less its empty (true) else, (false)
}

void queue::resize(int newCapacity)
{
    int *tmpPtr = new int[newCapacity]; // New array of capacity +|- 1 size
    int limit = this->size; // Size to iterate through
    int offset = 0; // If no offset, each equals itself 

    if (newCapacity < this->size){ // If new array is shorter, do iterate only through its size
        offset = 1; // Offset to pick every element but 0
        limit = newCapacity;
    }

    for (int i = 0; i < limit; i++){
        tmpPtr[i] = this->queueArray[i + offset]; // Copy over i+offset elements of queueArray to new
    }

    // Reallocate this->queueArray to + 1 in size version of itself
    delete[] this->queueArray;
    this->queueArray = tmpPtr;
}

void queue::flip()
{
    int tmp;
    for(int i = 0; i < this->size/2; i++){ // flip one half with other half
        tmp = this->queueArray[i]; // Store first
        this->queueArray[i] = this->queueArray[this->size-i-1]; // Change first with last
        this->queueArray[this->size-i-1] = tmp; // Change last with first
    }
}