#include "stack.h"

stack::stack()
{
    this->stackArray = new int[0];
    this->size = 0;
}

stack::stack(const stack &other)
{

    this->stackArray = new int[other.size];
    this->size = other.size;
    for (int i = 0; i < this->size; i++){
        this->stackArray[i] = other.stackArray[i];
    }
}

stack::~stack()
{
    // Delete current allocated stack
    delete[] this->stackArray;
}

stack &stack::operator=(const stack &other)
{
    if (this == &other){
        return *this;
    }

    if (this->stackArray != nullptr){
        delete[] this->stackArray;
    }

    if (other.stackArray == nullptr){
        this->size = 0;
        this->stackArray = nullptr;
        return *this;
    }

    this->stackArray = new int[other.size];

    // Set with other values
    this->size = other.size;
    for (int i = 0; i < this->size; i++){
        this->stackArray[i] = other.stackArray[i];
    }
    return *this;
}

void stack::push(int value)
{
    this->resize(this->size + 1); // Grow array by one
    stackArray[size] = value; // Add to next open value according to front
    size++;
}

int stack::pop()
{
    if (!this->isEmpty()){ // If stack has a element
        int tmp = stackArray[this->size - 1];
        resize(this->size - 1); // shorten by one
        size--;
        return tmp;
    }
    else{
        throw std::runtime_error("Stack Underflow of stackArray");
    }
}

bool stack::isEmpty()
{
    return (this->size <= 0);
}

void stack::resize(int tmpSize)
{
    int *tmpPtr = new int[tmpSize]; // New array of capacity +|- 1 size

    for (int i = 0; i < tmpSize; i++){ // Copying data from old into +|- 1
        if (i >= this->size){
            break;
        }
        tmpPtr[i] = this->stackArray[i];
    }
    delete[] this->stackArray;
    this->stackArray = tmpPtr;
}

void stack::flip()
{
    int tmp;
    for(int i = 0; i < this->size/2; i++){ // flip one half with other half
        tmp = this->stackArray[i]; // Store first
        this->stackArray[i] = this->stackArray[this->size-i-1]; // Change first with last
        this->stackArray[this->size-i-1] = tmp; // Change last with first
    }
}