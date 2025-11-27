#include "Bank.h"
#include <iostream>
#include <iomanip>

Bank::Bank() : root(nullptr) {}
Bank::~Bank() { freeTree(root); }

Account* Bank::insertNode(Account* node, int accNo, 
    const std::string& name, double balance, bool &inserted)
{
    if (!node) {
        inserted = true;
        return new Account(accNo, name, balance);
    }

    if (accNo < node->accNo)
        node->left = insertNode(node->left, accNo, name, balance, inserted);
    else if (accNo > node->accNo)
        node->right = insertNode(node->right, accNo, name, balance, inserted);
    else
        inserted = false;

    return node;
}

Account* Bank::searchNode(Account* node, int accNo) {
    if (!node) return nullptr;
    if (accNo == node->accNo) return node;
    return accNo < node->accNo ? searchNode(node->left, accNo)
                               : searchNode(node->right, accNo);
}

void Bank::freeTree(Account* node) {
    if (!node) return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}

void Bank::appendTransaction(Account* acc, Transaction::Type type, double amount) {
    auto tx = std::make_shared<Transaction>(type, amount);
    if (!acc->historyHead) acc->historyHead = tx;
    else {
        auto cur = acc->historyHead;
        while (cur->next) cur = cur->next;
        cur->next = tx;
    }
}

bool Bank::createAccount(int accNo, const std::string& name, double balance) {
    bool inserted = false;
    root = insertNode(root, accNo, name, balance, inserted);

    if (inserted && balance > 0) {
        auto acc = search(accNo);
        appendTransaction(acc, Transaction::DEPOSIT, balance);
    }

    return inserted;
}

Account* Bank::search(int accNo) { return searchNode(root, accNo); }

bool Bank::directDeposit(int accNo, double amount) {
    if (amount <= 0) return false;
    auto* acc = search(accNo);
    if (!acc) return false;
    acc->balance += amount;
    appendTransaction(acc, Transaction::DEPOSIT, amount);
    return true;
}

bool Bank::directWithdraw(int accNo, double amount) {
    if (amount <= 0) return false;
    auto* acc = search(accNo);
    if (!acc || acc->balance < amount) return false;
    acc->balance -= amount;
    appendTransaction(acc, Transaction::WITHDRAW, amount);
    return true;
}

void Bank::enqueueTransaction(int accNo, Transaction::Type type, double amount) {
    pending.emplace(accNo, type, amount);
}

bool Bank::processOnePending() {
    if (pending.empty()) return false;

    auto p = pending.front();
    pending.pop();

    Account* acc = search(p.accNo);
    if (!acc) {
        std::cout << "Account not found.\n";
        return true;
    }

    if (p.type == Transaction::DEPOSIT) {
        acc->balance += p.amount;
        appendTransaction(acc, Transaction::DEPOSIT, p.amount);
    } else {
        if (acc->balance >= p.amount) {
            acc->balance -= p.amount;
            appendTransaction(acc, Transaction::WITHDRAW, p.amount);
        } else {
            std::cout << "Insufficient funds.\n";
        }
    }
    return true;
}

void Bank::processAllPending() {
    while (!pending.empty()) processOnePending();
}

void Bank::showTransactionHistory(int accNo) {
    auto* acc = search(accNo);
    if (!acc) {
        std::cout << "Account not found.\n";
        return;
    }

    std::cout << "History for " << acc->accNo << " (" << acc->name << ")\n";
    auto cur = acc->historyHead;
    int i = 1;
    while (cur) {
        std::cout << i++ << ". "
                  << (cur->type == Transaction::DEPOSIT ? "Deposited " : "Withdrawn ")
                  << cur->amount << " at " << cur->timestamp << "\n";
        cur = cur->next;
    }
}

void Bank::showAccountInfo(int accNo) {
    auto* acc = search(accNo);
    if (!acc) {
        std::cout << "Not found.\n";
        return;
    }

    std::cout << "Account " << acc->accNo << "\nName: " << acc->name
              << "\nBalance: " << acc->balance << "\n";
}

void Bank::inOrderPrint(Account* node) {
    if (!node) return;
    inOrderPrint(node->left);
    std::cout << node->accNo << " | " << node->name 
              << " | Balance: " << node->balance << "\n";
    inOrderPrint(node->right);
}

void Bank::listAllAccounts() {
    inOrderPrint(root);
}
