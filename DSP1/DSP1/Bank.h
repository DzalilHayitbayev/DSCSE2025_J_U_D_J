#pragma once
#include "BST.h"
#include "PendingQueue.h"
#include <string>

using namespace std;

class Bank {
public:
    Bank();
    ~Bank();

    // create account; returns true if success, false if duplicate
    bool createAccount(int accNo, const string& name, double initialBalance, const string& timestamp);

    // direct operations (perform immediately)
    bool directDeposit(int accNo, double amount, const string& timestamp);
    bool directWithdraw(int accNo, double amount, const string& timestamp);

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
    static string currentDateTime();

private:
    BST accounts;
    PendingQueue queue;
};
