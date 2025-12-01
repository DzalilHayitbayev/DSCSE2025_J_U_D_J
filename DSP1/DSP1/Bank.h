#pragma once
#include "BST.h"
#include "PendingQueue.h"
#include <string>

class Bank {
public:
    Bank();
    ~Bank();

    // create account; returns true if success, false if duplicate
    bool createAccount(int accNo, const std::string& name, double initialBalance, const std::string& timestamp);

    // direct operations (perform immediately)
    bool directDeposit(int accNo, double amount, const std::string& timestamp);
    bool directWithdraw(int accNo, double amount, const std::string& timestamp);

    // queue operations (enqueue only)
    void enqueueDeposit(int accNo, double amount);
    void enqueueWithdraw(int accNo, double amount);

    // process queue: returns number of processed tx (attempted)
    int processPendingAll();
    bool processOnePending(); // process single

    // display
    void showTransactionHistory(int accNo) const;
    void showAccountInfo(int accNo) const;
    void listAllAccounts() const;

    // utility to get current timestamp string
    static std::string currentDateTime();

private:
    BST accounts;
    PendingQueue queue;
};
