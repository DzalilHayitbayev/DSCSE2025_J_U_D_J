#pragma once
#include "Transaction.h"

struct PendingTx {
    int accNo;
    Transaction::Type type;
    double amount;

    PendingTx(int a, Transaction::Type t, double amt)
        : accNo(a), type(t), amount(amt) {}
};
