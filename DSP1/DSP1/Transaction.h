#pragma once
#include <string>

class Transaction {
public:
    enum Type { DEPOSIT, WITHDRAW };

    Transaction(Type t, double amt, const std::string& timestamp);
    ~Transaction() = default;

    Type type;
    double amount;
    std::string timestamp;
    Transaction* next; // single linked list
};
