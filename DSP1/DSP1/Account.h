#pragma once
#include <string>
#include "TransactionList.h"

class Account {
public:
    Account(int accNo, const std::string& name, double initialBalance);
    ~Account();

    int getAccNo() const;
    const std::string& getName() const;
    double getBalance() const;

    void deposit(double amount, const std::string& timestamp);
    bool withdraw(double amount, const std::string& timestamp);

    // access transaction history
    void printHistory() const;
    int transactionCount() const;

    // BST pointers (public for simplicity in BST implementation)
    Account* left;
    Account* right;

private:
    int accNo;
    std::string name;
    double balance;
    TransactionList* history;
};
