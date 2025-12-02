#pragma once
#include "Transaction.h"
#include <string>

using namespace std;

class TransactionList {
public:
    TransactionList();
    ~TransactionList();

    // create a Transaction node
    void append(Transaction::Type type, double amount, const string& timestamp);

    void printAll() const;

    // number of transactions
    int count() const;

    // clear all
    void clear();

private:
    Transaction* head;
    Transaction* tail;
};
