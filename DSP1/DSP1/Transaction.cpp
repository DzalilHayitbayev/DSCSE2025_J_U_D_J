#include "Transaction.h"

using namespace std;

Transaction::Transaction(Type t, double amt, const string& timestamp)
    : type(t), amount(amt), timestamp(timestamp), next(nullptr) {
}
