#include "Transaction.h"

Transaction::Transaction(Type t, double amt, const std::string& timestamp)
    : type(t), amount(amt), timestamp(timestamp), next(nullptr) {
}
