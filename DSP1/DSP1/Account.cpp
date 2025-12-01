#include "Account.h"

Account::Account(int accNo_, const std::string& name_, double initialBalance)
    : accNo(accNo_), name(name_), balance(initialBalance), history(new TransactionList()),
    left(nullptr), right(nullptr)
{
    if (initialBalance > 0.0) {
        // create initial deposit transaction with placeholder timestamp (will be set by Bank)
        // Bank will call deposit(date) after insertion to record exact timestamp.
    }
}

Account::~Account() {
    delete history;
}

int Account::getAccNo() const { return accNo; }
const std::string& Account::getName() const { return name; }
double Account::getBalance() const { return balance; }

void Account::deposit(double amount, const std::string& timestamp) {
    balance += amount;
    history->append(Transaction::DEPOSIT, amount, timestamp);
}

bool Account::withdraw(double amount, const std::string& timestamp) {
    if (amount <= 0.0 || amount > balance) return false;
    balance -= amount;
    history->append(Transaction::WITHDRAW, amount, timestamp);
    return true;
}

void Account::printHistory() const { history->printAll(); }
int Account::transactionCount() const { return history->count(); }
