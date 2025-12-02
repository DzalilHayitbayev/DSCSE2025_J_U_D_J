#pragma once
#include <string>
#include "TransactionList.h"

using namespace std;

class Account {
public:
    Account(int accNo, const string& name, double initialBalance);
    ~Account();

    int getAccNo() const;
    const string& getName() const;
    double getBalance() const;

    void deposit(double amount, const string& timestamp);
    bool withdraw(double amount, const string& timestamp);

    void printHistory() const;
    int transactionCount() const;

    Account* left;
    Account* right;

private:
    int accNo;
    string name;
    double balance;
    TransactionList* history;
};
