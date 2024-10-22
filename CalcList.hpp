#ifndef CALCLIST_HPP
#define CALCLIST_HPP

#include "CalcListInterface.hpp"
#include <sstream>
#include <iomanip>

class Node {
public:
    double totalBefore;          // Total before the operation
    double operand;              // Operand used in the operation
    FUNCTIONS operation;         // Operation performed
    double totalAfter;           // Total after the operation
    int step;                    // Step number of the operation
    Node* prev;                  // Pointer to the previous node

    // Constructor to initialize the values
    Node(double before, double opnd, FUNCTIONS func, double after, int s)
        : totalBefore(before), operand(opnd), operation(func), totalAfter(after), step(s), prev(nullptr) {}
};


class CalcList : public CalcListInterface {
private:
    Node* tail;           // Pointer to the last operation (most recent)
    int stepCount;        // Number of operations performed
    double currentTotal;  // Current total after all operations

public:
    CalcList();
    ~CalcList();

    double total() const override;
    void newOperation(const FUNCTIONS func, const double operand) override;
    void removeLastOperation() override;
    std::string toString(unsigned short precision) const override;
};

#endif