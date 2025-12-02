#pragma once
#include "Transaction.h"

struct PendingTx {
    int accNo;
    Transaction::Type type;
    double amount;
    PendingTx* next;
    PendingTx(int a, Transaction::Type t, double amt) : accNo(a), type(t), amount(amt), next(nullptr) {}
};

class PendingQueue {
public:
    PendingQueue();
    ~PendingQueue();

    void enqueue(int accNo, Transaction::Type type, double amount);
    bool dequeue(PendingTx& out); // returns false if empty
    bool isEmpty() const;
    void clear();

private:
    PendingTx* head;
    PendingTx* tail;
};
