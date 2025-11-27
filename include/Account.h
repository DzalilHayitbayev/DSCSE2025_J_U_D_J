#pragma once
#include <string>
#include <memory>
#include "Transaction.h"

struct Account {
    int accNo;
    std::string name;
    double balance;

    std::shared_ptr<Transaction> historyHead;

    Account* left;
    Account* right;

    Account(int n, std::string nm, double b);
};
