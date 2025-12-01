#include "Bank.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "Account.h"

std::string Bank::currentDateTime() {
    auto now = std::chrono::system_clock::now();
    time_t t = std::chrono::system_clock::to_time_t(now);
    tm tm{};
#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    char buf[64];
    std::strftime(buf, sizeof(buf), "%d-%m-%Y %I:%M:%S %p", &tm);
    return std::string(buf);
}

Bank::Bank() {}
Bank::~Bank() {}

bool Bank::createAccount(int accNo, const std::string& name, double initialBalance, const std::string& timestamp) {
    Account* acc = new Account(accNo, name, initialBalance);
    bool inserted = accounts.insert(acc);
    if (!inserted) {
        delete acc; // avoid leak
        return false;
    }
    // record initial deposit if > 0
    if (initialBalance > 0.0) {
        Account* a = accounts.find(accNo);
        if (a) a->deposit(initialBalance, timestamp);
    }
    return true;
}

bool Bank::directDeposit(int accNo, double amount, const std::string& timestamp) {
    Account* a = accounts.find(accNo);
    if (!a || amount <= 0.0) return false;
    a->deposit(amount, timestamp);
    return true;
}

bool Bank::directWithdraw(int accNo, double amount, const std::string& timestamp) {
    Account* a = accounts.find(accNo);
    if (!a || amount <= 0.0) return false;
    return a->withdraw(amount, timestamp);
}

void Bank::enqueueDeposit(int accNo, double amount) {
    queue.enqueue(accNo, Transaction::DEPOSIT, amount);
}

void Bank::enqueueWithdraw(int accNo, double amount) {
    queue.enqueue(accNo, Transaction::WITHDRAW, amount);
}

bool Bank::processOnePending() {
    PendingTx p(0, Transaction::DEPOSIT, 0.0);
    if (!queue.dequeue(p)) return false; // nothing to process
    Account* a = accounts.find(p.accNo);
    std::string ts = currentDateTime();
    if (!a) {
        std::cout << "Pending tx failed: account " << p.accNo << " not found. Skipping.\n";
        return true; // we consumed it
    }
    if (p.type == Transaction::DEPOSIT) {
        a->deposit(p.amount, ts);
    }
    else {
        if (!a->withdraw(p.amount, ts)) {
            std::cout << "Pending tx: insufficient funds for account " << p.accNo << ". Skipping.\n";
        }
    }
    return true;
}

int Bank::processPendingAll() {
    int cnt = 0;
    while (processOnePending()) ++cnt;
    return cnt;
}

void Bank::showTransactionHistory(int accNo) const {
    Account* a = accounts.find(accNo);
    if (!a) {
        std::cout << "Account not found.\n";
        return;
    }
    std::cout << "Transaction history for " << a->getAccNo() << " (" << a->getName() << ")\n";
    a->printHistory();
}

void Bank::showAccountInfo(int accNo) const {
    Account* a = accounts.find(accNo);
    if (!a) {
        std::cout << "Account not found.\n";
        return;
    }
    std::cout << "Account: " << a->getAccNo() << "\n  Name: " << a->getName()
        << "\n  Balance: " << std::fixed << std::setprecision(2) << a->getBalance()
        << "\n  Total transactions: " << a->transactionCount() << "\n";
}

void Bank::listAllAccounts() const {
    std::cout << "Accounts (in-order):\n";
    accounts.inOrderPrint();
}
