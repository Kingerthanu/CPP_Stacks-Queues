// Benjamin Rudolph Spitzauer
// Project 3 - "Stack and Queues"
// 11/6/2022
/* Tests out declaration of queue and stack and its implementation using
functions which test different sections of the class. One being a random
generator which processes random function calls of the classes; and 
another testing storage of data with a summation function which does
both negative and positive summations. The last is a fibonacci
test which works with a stack instance and looks if it can
properly calculate the first 10 digits of the fibonacci sequence. 
*/


#include "queue.h"
#include "stack.h"

#include <random>
#include <iostream>

// ~~~~~~~~~~~~ ProtoTypes ~~~~~~~~~~~~

/*
Precondition: Must take in a primed mt19 generator;
as well as uniform_int_dist to transform the int
passed in the generator.
Postcondition: Will print the state of the
queue as its being mutated, showing amount
being added to queue, as well as amount
dequeued and if empty state. It will 
also display action being randomly 
performed on queue.
*/
void queueRandTest(std::mt19937 &seeder, 
std::uniform_int_distribution<int> &randInteger, 
std::uniform_int_distribution<int> &randFunction);

/*
Precondition: Must take in a primed mt19 generator;
as well as uniform_int_dist to transform the int
passed in the generator.
Postcondition: Will print the state of the
stack as its being mutated, showing amount
being added to stack, as well as amount
popped and if empty state. It will 
also display action being randomly 
performed on stack.
*/
void stackRandTest(std::mt19937 &seeder, 
std::uniform_int_distribution<int> &randInteger, 
std::uniform_int_distribution<int> &randFunction);

/*
Precondition: None. Depends on queue class
and local instantiation of a member.
Postcondition: Will display a attempt
to underflow queue and a error exception to it;
also will add the numbers 0-99 into the queue
and look if popped is equal to real values.
*/
void queueTestSum();

/*
Precondition: Must take in a primed mt19 generator.
Postcondition: Will pick a positive random number to 
summate through its range and will compare the
stack and queue and their totals compared to the
actual totals using different ranges for each.
*/
void testPositiveSummation(std::mt19937 &seeder);

/*
Precondition: Must take in a primed mt19 generator.
Postcondition: Will pick a negative random number to 
summate through its range and will compare the
stack and queue and their totals compared to the
actual totals using different negative ranges for each.
*/
void testNegativeSummation(std::mt19937 &seeder);

/*
Precondition: None.
Postcondition: Will test the stack and if it holds
the first 10 fibonacci values.
*/
void stackTestFibonacci();

/*
Precondition: Must have queue to index.
Postcondition: Will print out the contents of queueToIndex.
*/
void display(int capacity, queue &queueToIndex);

/*
Precondition: Must have stack to index.
Postcondition: Will print out the contents of stackToIndex.
*/
void display(int capacity, queue &stackToIndex);

// ~~~~~~~~ END ProtoTypes ~~~~~~~~~~~~

void display(int capacity, queue &queueToIndex) // Display queue values 
{
    int tmp;
    std::cout << "Displaying queue values: \n[ ";

    for (int i = 0; i < capacity; i++){
        tmp = queueToIndex.dequeue(); // Copy first
        std::cout << tmp << ", ";
        queueToIndex.enqueue(tmp); // Replace first
    }
    std::cout << "]\nEnd Size: " << capacity << "\n\n---------------------------------------\n";
}

void display(int capacity, stack &stackToIndex) // Display stack values 
{
    int tmp[capacity];
    std::cout << "Displaying stack values: \n[ ";

    for (int i = 0; i < capacity; i++){ // Place into temp
        tmp[i] = stackToIndex.pop();  
    }

    for(int i = capacity-1; 0 <= i; i--){ // Print the temp in reverse (pop goes last to first)
        std::cout << tmp[i] << ", ";
    }

    for (int i = capacity-1; 0 <= i; i--){ // Replace elements in stack
        stackToIndex.push(tmp[i]);
    }
    std::cout << "]\nEnd Size: " << capacity << "\n\n---------------------------------------\n";
}

void queueRandTest(std::mt19937 &seeder, 
std::uniform_int_distribution<int> &randInteger, 
std::uniform_int_distribution<int> &randFunction)
{
    std::cout << "\n\nRANDOM QUEUE TESTING: \n"; // Main prompt
    const int TEST_QUEUE_SIZE = randInteger(seeder); // Size of queue for functions
    queue *newQueue = new queue();

    // Display queue state; and display adding to queue
    try{
        std::cout << "Is queue empty? " << ((newQueue->isEmpty()) ? "yes\n" : "no\n") << "Adding " 
        << TEST_QUEUE_SIZE << " elements to queue...\n";
    }
    catch(std::runtime_error &caughtError){
        std::cout << "Cannot check if empty from queue; check implementation of queue for fix...\n\n";
    }

    // Add to queue
    for (int i = 0; i < TEST_QUEUE_SIZE; i++){
        try{
            newQueue->enqueue(randInteger(seeder));
        }
        catch(std::runtime_error &runtimeError){
            std::cout << "Cannot enqueue into queue; check implementation of queue for fix...\n\n";
        }
    }

    // Display finishing of enqueuement; start dequeueing with prompt
    std::cout << "Done adding " << TEST_QUEUE_SIZE << " elements to queue...\n\n"
    << "Dequeuing all elements...\n";

    // Iterate through
    for (int i = 0; i < TEST_QUEUE_SIZE; i++){
        try{
            newQueue->dequeue();
        }
        catch(std::runtime_error &runtimeError){
            std::cout << "Cannot dequeue from queue; check implementation of queue for fix...\n\n";
        }
    }

    // Display done queueing
    std::cout << "Done Dequeueing.\n"; 

    // Check if it is actually empty (should always be yes)
    std::cout << "Is queue empty? " << ((newQueue->isEmpty()) ? "yes\n" : "no\n");

    queue *otherQueue = new queue(*newQueue); // Copy constructed

    // 20 calls of a random function per iteration
    std::cout << "\n\nSTART OF RANDOM FUNCTION CALLINGS OF QUEUE: \n";
    for (int i = 0; i < 20; i++){

        switch (randFunction(seeder)){ // 0-8 inclusive
        case 0: // Enqueue
            std::cout << "\nENQUEING\n";
            newQueue->enqueue(randInteger(seeder));
            break;
        case 1: // Dequeue
            try{
                std::cout << "\nDEQUEING\n";
                newQueue->dequeue();
            }
            catch (std::runtime_error &caughtError){
                std::cout << "\n~~~~~~~~Trying to dequeue when stack is 0 (Stack Underflow)~~~~~~~~\n\n";
            }
            break;
        case 2: // First = second
            std::cout << "\nFIRST EQUALS SECOND\n";
            *newQueue = *otherQueue;
            break;
        case 3: // Second = first
            std::cout << "\nSECOND EQUALS FIRST\n";
            *otherQueue = *newQueue;
            break;
        case 4: // First = nullptr
            std::cout << "\nFIRST EQUALS NULLPTR\n";
            delete newQueue;
            newQueue = new queue();
            break;
        case 5: // Second = nullptr
            std::cout << "\nSECOND EQUALS NULLPTR\n";
            delete otherQueue;
            otherQueue = new queue();
            break;
        case 6: // first = new queue(second)
            std::cout << "\nFIRST INITIALIZED WITH SECOND\n";
            delete newQueue;
            newQueue = new queue(*otherQueue);
            break;
        case 7: // second = new queue(first)
            std::cout << "\nSECOND INITIALIZED WITH FIRST\n";
            delete otherQueue;
            otherQueue = new queue(*newQueue);
            break;
        case 8: // first is empty?
            std::cout << "\nIS FIRST QUEUE EMPTY? " << ((newQueue->isEmpty()) ? "yes\n" : "no\n");
            break;
        case 9: // second is empty?
            std::cout << "\nIS SECOND QUEUE EMPTY? " << ((otherQueue->isEmpty()) ? "yes\n" : "no\n");
            break;
        }

        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"; // Visual line break per iteration
    }
    std::cout << "\n\n-END OF RANDOM QUEUE TESTING- \n\n\n";

    // Deallocate pointed data (call destructor)
    delete otherQueue;
    delete newQueue;

    // Sectional break
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"; // Sectional break
}

void stackRandTest(std::mt19937 &seeder, 
std::uniform_int_distribution<int> &randInteger, 
std::uniform_int_distribution<int> &randFunction)
{
    std::cout << "\n\nRANDOM STACK TESTING: \n"; // Main prompt

    const int TEST_STACK_SIZE = randInteger(seeder); // Size of stack for functions

    stack *newStack = new stack(); // stack variable

    // Check if empty and display status and show elements are being pushed
    try{
        std::cout << "Is stack empty? " << ((newStack->isEmpty()) ? "yes\n\n" : "no\n\n") << "Adding " 
        << TEST_STACK_SIZE << " elements to stack...\n";
    }
    catch(std::runtime_error &caughtError){
        std::cout << "Cannot check if empty from stack; check implementation of stack for fix...\n\n";
    }

    // Add to stack
    for (int i = 0; i < TEST_STACK_SIZE; i++){
        try{
            newStack->push(randInteger(seeder));
        }
        catch(std::runtime_error &runtimeError){
            std::cout << "Cannot push into stack; check implementation of stack for fix...\n\n";
        }
    }
    // Display done pushing; now show popping elements
    std::cout << "Done adding " << TEST_STACK_SIZE << " elements to stack...\n\n"
    << "Popping all elements...\n";

    // Iterate through
    for (int i = 0; i < TEST_STACK_SIZE; i++){
        try{
            newStack->pop();
        }
        catch(std::runtime_error &runtimeError){
            std::cout << "Cannot pop from stack; check implementation of stack for fix...\n\n";
        }
    }

    std::cout << "Done Popping.\n"; 

    // Check if it is actually empty (should always be yes)
    std::cout << "Is stack empty? " << ((newStack->isEmpty()) ? "yes\n" : "no\n");

    stack *otherStack = new stack(*newStack); // Copy constructed

    // Start of random function calling for 20 iterations
    std::cout << "\n\nSTART OF RANDOM FUNCTION CALLINGS OF STACK: \n";
    for (int i = 0; i < 20; i++){

        switch (randFunction(seeder)){
        case 0: // Push
            std::cout << "\nPUSHING\n";
            newStack->push(randInteger(seeder));
            break;
        case 1: // Pop
            try{
                std::cout << "\nPOPPING\n";
                newStack->pop();
            }
            catch (std::runtime_error &caughtError){
                std::cout << "\n~~~~~~~~Trying to pop when stack is 0 (Stack Underflow)~~~~~~~~\n\n";
            }
            break;
        case 2: // First = second
            std::cout << "\nFIRST EQUALS SECOND\n";
            *newStack = *otherStack;
            break;
        case 3: // Second = first
            std::cout << "\nSECOND EQUALS FIRST\n";
            *otherStack = *newStack;
            break;
        case 4: // First = nullptr
            std::cout << "\nFIRST EQUALS NULLPTR\n";
            delete newStack;
            newStack = new stack();
            break;
        case 5: // Second = nullptr
            std::cout << "\nSECOND EQUALS NULLPTR\n";
            delete otherStack;
            otherStack = new stack();
            break;
        case 6: // First = new stack(second)
            std::cout << "\nFIRST INITIALIZED WITH SECOND\n";
            delete newStack;
            newStack = new stack(*otherStack);
            break;
        case 7: // Second = new stack(first)
            std::cout << "\nSECOND INITIALIZED WITH FIRST\n";
            delete otherStack;
            otherStack = new stack(*newStack);
            break;
        case 8: // first is empty?
            std::cout << "\nIS FIRST STACK EMPTY? " << ((newStack->isEmpty()) ? "yes\n" : "no\n");
            break;
        case 9: // second is empty?
            std::cout << "\nIS SECOND STACK EMPTY? " << ((otherStack->isEmpty()) ? "yes\n" : "no\n");
            break;
        }

        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"; // Line break per iteration   
    }
    std::cout << "\n\n-END RANDOM STACK TESTING- \n\n\n";
    
    // Deallocate pointed data (call destructor)
    delete otherStack;
    delete newStack;

    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"; // Section break
}

void queueTestSum()
{
    std::cout << "\n\nQUEUE TEST SUM OF SIZE 10: \n\n"; // Queue summation with size 10 queue

    const int CAPACITY = 10;

    queue *queueArray = new queue(); // Call new alloocated instantiation

    // Test for underflow detection
    try{
        std::cout << "Attempting to underflow the queue..." << std::endl;
        queueArray->dequeue();
    }
    catch (std::runtime_error &runtimeError){
        std::cout << "The dequeue function correctly threw an error. Good work!"
        << std::endl
        << std::endl;
    }
    std::cout << "Adding together the numbers from 0 to 99, "
    << "grouped by last digit..." << std::endl
    << std::endl;

    // Fill the queue with the initial sums
    for (int i = 0; i < 10; i++){
        queueArray->enqueue(i);
    }

    // Loop through the queue 9 times, adding the
    for (int i = 10; i < 100; i++){
        int runningSum = queueArray->dequeue();
        runningSum += i;
        queueArray->enqueue(runningSum);
    }

    // These are the sums we should expect.
    int trueSums[CAPACITY] = {450, 460, 470, 480, 490, 500, 510, 520, 530, 540};
    bool mismatch = false;

    // Iterate through and print the final sums, reporting bad values when they are found
    for (int i = 0; i < 10; i++){
        int finalSum = queueArray->dequeue();
        if (finalSum != trueSums[i]){
            std::cout << "Error: The " << i << " th calcualted sum has value " << finalSum
            << " but the expected value is " << trueSums[i] << std::endl
            << std::endl;
            mismatch = true;
        }
    }
    if (!mismatch){
        std::cout << "Each sum of numbers with common final digits was correct."
        << std::endl
        << std::endl;
    }
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"; // Sectional break

    // Deallocate dynamic queue
    delete queueArray;
}

void testPositiveSummation(std::mt19937 &seeder)
{
    std::cout << "\n\nSTACK TEST SUM OF 0-randSum (random value): \n\n";
    std::uniform_int_distribution<int> randSum(1, 3000); // Values to test
    

    // Create local queue and stack
    queue tmpQueue = queue();
    stack tmpStack = stack();

    int amountToCount = randSum(seeder); // Amount of values to count up from

    int actualTotal = 0; // Actual total of 0-amountToCount
    int testedTotal = 0; // Sum of popped elements 

    // Show number range being calculated
    std::cout << "Adding 0-" << amountToCount << " to stack...\n"; 

    // Add to stack 0->amountToCount
    for (int i = 0; i <= amountToCount; i++){
        try{
            tmpStack.push(i);
            actualTotal += i;
        }
        catch(std::runtime_error &runtimeError){
            std::cout << "Cannot push into stack; check implementation of stack for fix...\n\n";
        }
    }

    // State its done summing; and now that its now getting popped value
    std::cout << "Done adding 0-" << amountToCount << ".\n\n" 
    << "Popping 0-" << amountToCount << "...\n";

    // Pop elements in stack
    for (int i = 0; i <= amountToCount; i++){
        try{
            testedTotal += tmpStack.pop();
        }
        catch(std::runtime_error &runtimeError){
            std::cout << "Cannot pop stack; check implementation of stack for fix...\n\n";
        }
    }

    // Display total(s)
    std::cout << "Done popping 0-" << amountToCount << ".\n\n"
    << "popped total = " << testedTotal << " actual total = "
    << actualTotal << "\n";

    if (testedTotal == actualTotal){ // If popped values is equal to currect total
        std::cout << "\n\nCORRECT CALC\n\n";
    }
    else{
        std::cout << "\n\nWRONG CALC\n\n";
    }
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"; // Section break

    std::cout << "\n\nQUEUE TEST SUM OF 0-randSum (random value): \n\n"; 

    amountToCount = randSum(seeder); // get new sum to count
    
    // Reset values
    actualTotal = 0;
    testedTotal = 0;

    // Add to queue 0-amountToCount
    std::cout << "Adding 0-" << amountToCount << " to queue...\n";   
    for (int i = 0; i <= amountToCount; i++){
        try{
            tmpQueue.enqueue(i);
            actualTotal += i;
        }
        catch(std::runtime_error &runtimeError){
            std::cout << "Cannot enqueue into queue; check implementation of queue for fix...\n\n";
        }
    }

    // State its done summing; and now that its now getting popped value
    std::cout << "Done adding 0-" << amountToCount << ".\n\n" 
    << "Dequeuing 0-" << amountToCount << "...\n";

    for (int i = 0; i <= amountToCount; i++){
        try{
            testedTotal += tmpQueue.dequeue();
        }
        catch(std::runtime_error &runtimeError){
            std::cout << "Cannot dequeue from queue; check implementation of queue for fix...\n\n";
        }
    }

    // Display total(s) 
    std::cout << "Done dequeueing 0-" << amountToCount << ".\n\n"
    << "dequeued total = " << testedTotal << " actual total = "
    << actualTotal << "\n";

    if (testedTotal == actualTotal){ // If popped values is equal to currect total
        std::cout << "\n\nCORRECT CALC\n\n";
    }
    else{
        std::cout << "\n\nWRONG CALC\n\n";
    }
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"; // Section break
}

void testNegativeSummation(std::mt19937 &seeder)
{
    std::cout << "\n\nSTACK TEST SUM OF 0-randSum (random negative value): \n\n";
    std::uniform_int_distribution<int> randSum(1, 3000); // Values to test
    

    // Create local queue and stack
    queue tmpQueue = queue();
    stack tmpStack = stack();
    
    int amountToCount = -randSum(seeder); // Amount of values to count up from

    int actualTotal = 0; // Actual total of 0-amountToCount
    int testedTotal = 0; // Sum of popped elements 

    // Show number range being calculated
    std::cout << "Adding 0-" << amountToCount << " to stack...\n"; 

    // Add to stack 0->amountToCount
    for (int i = 0; i >= amountToCount; i--){
        try{
            tmpStack.push(i);
            actualTotal += i;
        }
        catch(std::runtime_error &runtimeError){
            std::cout << "Cannot push into stack; check implementation of stack for fix...\n\n";
        }
    }

    // State its done summing; and now that its now getting popped value
    std::cout << "Done adding 0-" << amountToCount << ".\n\n" 
    << "Popping 0-" << amountToCount << "...\n";

    // Pop elements in stack
    for (int i = 0; i >= amountToCount; i--){
        try{
            testedTotal += tmpStack.pop();
        }
        catch(std::runtime_error &runtimeError){
            std::cout << "Cannot pop stack; check implementation of stack for fix...\n\n";
        }
    }

    // Display total(s)
    std::cout << "Done popping 0-" << amountToCount << ".\n\n"
    << "popped total = " << testedTotal << " actual total = "
    << actualTotal << "\n";

    if (testedTotal == actualTotal){ // If popped values is equal to currect total
        std::cout << "\n\nCORRECT CALC\n\n";
    }
    else{
        std::cout << "\n\nWRONG CALC\n\n";
    }
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"; // Section break
    std::cout << "\n\nQUEUE TEST SUM OF 0-randSum (random negative value): \n\n"; 

    amountToCount = -randSum(seeder); // get new sum to count
    
    // Reset values
    actualTotal = 0;
    testedTotal = 0;

    // Add to queue 0-amountToCount
    std::cout << "Adding 0-" << amountToCount << " to queue...\n";   
    for (int i = 0; i >= amountToCount; i--){
        try{
            tmpQueue.enqueue(i);
            actualTotal += i;
        }
        catch(std::runtime_error &runtimeError){
            std::cout << "Cannot enqueue into queue; check implementation of queue for fix...\n\n";
        }
    }

    // State its done summing; and now that its now getting popped value
    std::cout << "Done adding 0-" << amountToCount << ".\n\n" 
    << "Dequeuing 0-" << amountToCount << "...\n";

    for (int i = 0; i >= amountToCount; i--){
        try{
            testedTotal += tmpQueue.dequeue();
        }
        catch(std::runtime_error &runtimeError){
            std::cout << "Cannot dequeue from queue; check implementation of queue for fix...\n\n";
        }
    }

    // Display total(s) 
    std::cout << "Done dequeueing 0-" << amountToCount << ".\n\n"
    << "dequeued total = " << testedTotal << " actual total = "
    << actualTotal << "\n";

    if (testedTotal == actualTotal){ // If popped values is equal to currect total
        std::cout << "\n\nCORRECT CALC\n\n";
    }
    else{
        std::cout << "\n\nWRONG CALC\n\n";
    }
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"; // Section break
}

void stackTestFibonacci()
{
    std::cout << "\nTESTING FIBONACCI SEQUENCE\n";
    const int CAPACITY = 10; // Set range of numbers testing in fibonacci

    stack *stackArray = new stack(); // Create new dynamic instantiation of stack

    // Using a stack to calculate the first 10 fibonacci numbers
    try{
        stackArray->push(1);
        stackArray->push(1);
    }
    catch(std::runtime_error &runtimeError){
        std::cout << "Cannot push into stack; check implementation of stack for fix...\n\n";
    }

    // Go through 0-8 elements
    for (int i = 0; i < (CAPACITY - 2); i++){
        int upper = stackArray->pop();
        int lower = stackArray->pop();
        int sum = upper + lower;
        stackArray->push(lower);
        stackArray->push(upper);
        stackArray->push(sum);
    }

    bool mismatch = false;

    // The first 10 fibonacci numbers
    int expectedSeries[CAPACITY] = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55};

    // Double-check that the calculated numbers match the real sequence.
    std::cout << "Calculating the first 10 fibonacci numbers..." << std::endl
    << std::endl;

    for (int i = 0; i < CAPACITY; i++){
        try{
            int popped = stackArray->pop();
            if (popped != expectedSeries[CAPACITY - 1 - i]){
                std::cout << "ERROR: The element at index " << (CAPACITY - 1 - i)
                << " has value " << popped << " which does not match the "
                << " corresponding fibonacci number " << expectedSeries[CAPACITY - 1 - i]
                << std::endl
                << std::endl;
                mismatch = true;
            }
        }
        catch(std::runtime_error &runtimeError){
            std::cout << "Cannot pop from stack; check implementation of stack for fix...\n\n";
        }
    }

    if (!mismatch){
        std::cout << "Fibonnacci numbers successfully calculated" << std::endl
        << std::endl;
    }
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

    // Deallocate dynamic stack
    delete stackArray;
}

int main()
{
    
    // --------------Seed random with current time for random gen---------------

    std::random_device rand;   // Making seeded gen
    std::mt19937 seed(rand()); // Seeding with quicker gen with seed of rand gen
    std::uniform_int_distribution<int> randInt(1, 1000); // Gives number 1-1000 inclusive
    std::uniform_int_distribution<int> randFunc(0, 9);

    // --------------------------------------------------------------------------

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Stack~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    stackRandTest(seed, randInt, randFunc);
    std::cin.ignore();

    stackTestFibonacci();
    std::cin.ignore();

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~END Stack~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Queue~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    queueRandTest(seed, randInt, randFunc);
    std::cin.ignore();

    queueTestSum();
    std::cin.ignore();

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~END Queue~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Test both~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    testPositiveSummation(seed); // Test stack and queue for random positive summations
    std::cin.ignore();

    testNegativeSummation(seed); // Test stack and queue for random negative summations
    std::cin.ignore();

    // Use to show flip
    queue newQueue = queue();
    stack newStack = stack();

    const int COUNT_TO = 100;

    for(int i = 0; i < COUNT_TO; i++){ // Store 1-COUNT_TO in queue
        newQueue.enqueue(i+1);
    }

    for(int i = 0; i < COUNT_TO; i++){ // Store 1-COUNT_TO in stack
        newStack.push(i+1);
    }

    // Display before flip
    std::cout << "\nVALUES BEFORE FLIP: \n";
    display(COUNT_TO, newQueue);
    display(COUNT_TO, newStack);
    std::cin.ignore();

    // Now flip
    newQueue.flip();
    newStack.flip();

    // Display after flip
    std::cout << "\nVALUES AFTER FLIP: \n";
    display(COUNT_TO, newQueue);
    display(COUNT_TO, newStack);
    std::cin.ignore();

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

}