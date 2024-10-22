// Manik Jindal - U07146364

// This program implements a linked list-based calculator that performs 
// basic arithmetic operations while tracking each operation. 
// It can undo the last operation and display the operations history with specified precision.

// Include the CalcList header file and required standard libraries
#include "CalcList.hpp"
#include <stdexcept>  // For exception handling
#include <iostream>   // For input/output operations

// Constructor: Initializes an empty list with no tail, stepCount as 0, and total as 0.0
CalcList::CalcList() : tail(nullptr), stepCount(0), currentTotal(0.0) {}

// Destructor: Removes all nodes by calling removeLastOperation until the list is empty
CalcList::~CalcList() {
    while (tail != nullptr) {
        removeLastOperation();
    }
}

// Returns the current total of the calculator
double CalcList::total() const {
    return currentTotal;
}

// Adds a new operation to the calculator and updates the total
void CalcList::newOperation(const FUNCTIONS func, const double operand) {
    // Check for division by zero, which is undefined
    if (func == DIVISION && operand == 0.0) {
        throw std::invalid_argument("Division by zero is undefined.");
    }

    double newTotal; // Stores the new total after the operation
    // Perform the correct arithmetic operation based on the provided function
    switch (func) {
        case ADDITION:
            newTotal = currentTotal + operand;
            break;
        case SUBTRACTION:
            newTotal = currentTotal - operand;
            break;
        case MULTIPLICATION:
            newTotal = currentTotal * operand;
            break;
        case DIVISION:
            newTotal = currentTotal / operand;
            break;
        default:
            throw std::invalid_argument("Invalid operation.");
    }

    // Create a new node to store the current operation
    Node* newNode = new Node(currentTotal, operand, func, newTotal, ++stepCount);
    newNode->prev = tail;  // Link the new node to the previous one
    tail = newNode;        // Update the tail to point to the new node

    currentTotal = newTotal;  // Update the current total with the new total
}

// Removes the last operation from the list and restores the previous total
void CalcList::removeLastOperation() {
    if (tail == nullptr) {
        // If the list is empty, throw an exception
        throw std::out_of_range("No operations to remove.");
    }

    Node* temp = tail;              // Temporary pointer to hold the current tail node
    currentTotal = tail->totalBefore; // Restore the total to the value before the last operation
    tail = tail->prev;              // Move the tail pointer to the previous node
    --stepCount;                    // Decrease the step count

    delete temp;  // Delete the old tail node to free memory
}

// Converts the list of operations to a string with the given precision
std::string CalcList::toString(unsigned short precision) const {
    if (tail == nullptr) {
        return "";  // Return an empty string if there are no operations
    }

    std::ostringstream oss;  // Output string stream to build the result
    oss << std::fixed << std::setprecision(precision);  // Set the precision for floating-point numbers

    Node* current = tail;  // Start from the last operation
    // Iterate through the list and add each operation to the string
    while (current != nullptr) {
        char opSymbol;
        // Determine the symbol for the operation
        switch (current->operation) {
            case ADDITION:
                opSymbol = '+';
                break;
            case SUBTRACTION:
                opSymbol = '-';
                break;
            case MULTIPLICATION:
                opSymbol = '*';
                break;
            case DIVISION:
                opSymbol = '/';
                break;
            default:
                opSymbol = '?';
                break;
        }

        // Format the current operation as a string
        oss << current->step << ": "
            << current->totalBefore << opSymbol
            << current->operand << "="
            << current->totalAfter << "\n";

        current = current->prev;  // Move to the previous operation
    }

    return oss.str();  // Return the formatted string of operations
}


// Uncomment for local testing
/*
int main() {
    CalcList calc;

    calc.newOperation(ADDITION, 10);          // Total: 10
    calc.newOperation(MULTIPLICATION, 5);     // Total: 50
    calc.newOperation(SUBTRACTION, 15);       // Total: 35
    calc.newOperation(DIVISION, 7);           // Total: 5
    calc.removeLastOperation();               // Undo division, Total: 35
    calc.newOperation(SUBTRACTION, 30);       // Total: 5
    calc.newOperation(ADDITION, 5);           // Total: 10
    calc.removeLastOperation();               // Undo addition, Total: 5

    std::cout << calc.toString(2);
    // Expected output:
    // 4: 35.00-30.00=5.00
    // 3: 50.00-15.00=35.00
    // 2: 10.00*5.00=50.00
    // 1: 0.00+10.00=10.00

    return 0;
}
*/

// compilation command:
// g++ -std=c++17 -Wall CalcList.cpp PP1Test.cpp -o calc_test
// execute the file:
// ./calc_test 
