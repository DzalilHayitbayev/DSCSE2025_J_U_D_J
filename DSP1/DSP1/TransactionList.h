#pragma once
#include "Transaction.h"
#include <string>

using namespace std;

class TransactionList {
public:
    TransactionList();
    ~TransactionList();

    // append a transaction (creates a Transaction node)
    void append(Transaction::Type type, double amount, const string& timestamp);

    // print all transactions in order
    void printAll() const;

    // count number of transactions
    int count() const;

    // clear all
    void clear();

private:
    Transaction* head;
    Transaction* tail;
};
