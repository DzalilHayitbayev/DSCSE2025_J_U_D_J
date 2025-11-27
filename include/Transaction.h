#pragma once
#include <string>
#include <memory>

struct Transaction {
    enum Type { DEPOSIT, WITHDRAW };

    Type type;
    double amount;
    std::string timestamp;
    std::shared_ptr<Transaction> next;

    Transaction(Type t, double a);
};

std::string currentDateTime();
