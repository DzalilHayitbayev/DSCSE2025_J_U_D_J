#include "TransactionList.h"
#include <iostream>
#include <iomanip>

TransactionList::TransactionList() : head(nullptr), tail(nullptr) {}

TransactionList::~TransactionList() { clear(); }

void TransactionList::append(Transaction::Type type, double amount, const std::string& timestamp) {
    Transaction* node = new Transaction(type, amount, timestamp);
    if (!head) {
        head = tail = node;
    }
    else {
        tail->next = node;
        tail = node;
    }
}

void TransactionList::printAll() const {
    if (!head) {
        std::cout << "  No transactions yet.\n";
        return;
    }
    int idx = 1;
    Transaction* cur = head;
    while (cur) {
        std::cout << std::setw(2) << idx++ << ". ";
        if (cur->type == Transaction::DEPOSIT) std::cout << "Deposited ";
        else std::cout << "Withdrawn ";
        std::cout << std::fixed << std::setprecision(2) << cur->amount
            << " on " << cur->timestamp << "\n";
        cur = cur->next;
    }
}

int TransactionList::count() const {
    int c = 0;
    Transaction* cur = head;
    while (cur) { ++c; cur = cur->next; }
    return c;
}

void TransactionList::clear() {
    Transaction* cur = head;
    while (cur) {
        Transaction* nx = cur->next;
        delete cur;
        cur = nx;
    }
    head = tail = nullptr;
}
