#include "Account.h"

using namespace std;

Account::Account(int accNo_, const string& name_, double initialBalance)
    : accNo(accNo_), name(name_), balance(initialBalance), history(new TransactionList()),
    left(nullptr), right(nullptr)
{
}

Account::~Account() {
    delete history;
}

int Account::getAccNo() const { return accNo; }
const string& Account::getName() const { return name; }
double Account::getBalance() const { return balance; }

void Account::deposit(double amount, const string& timestamp) {
    balance += amount;
    history->append(Transaction::DEPOSIT, amount, timestamp);
}

bool Account::withdraw(double amount, const string& timestamp) {
    if (amount <= 0.0 || amount > balance) return false;
    balance -= amount;
    history->append(Transaction::WITHDRAW, amount, timestamp);
    return true;
}

void Account::printHistory() const { history->printAll(); }
int Account::transactionCount() const { return history->count(); }
