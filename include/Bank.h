#pragma once
#include <queue>
#include <string>
#include "Account.h"
#include "PendingTx.h"

class Bank {
private:
    Account* root;
    std::queue<PendingTx> pending;

    Account* insertNode(Account* node, int accNo, const std::string& name,
                        double balance, bool& inserted);

    Account* searchNode(Account* node, int accNo);

    void freeTree(Account* node);

    void appendTransaction(Account* acc, Transaction::Type type, double amount);

    void inOrderPrint(Account* node);

public:
    Bank();
    ~Bank();

    bool createAccount(int accNo, const std::string& name, double initialBalance);

    Account* search(int accNo);

    bool directDeposit(int accNo, double amount);
    bool directWithdraw(int accNo, double amount);

    void enqueueTransaction(int accNo, Transaction::Type type, double amount);

    bool processOnePending();
    void processAllPending();

    void showTransactionHistory(int accNo);
    void showAccountInfo(int accNo);

    void listAllAccounts();
};
