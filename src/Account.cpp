#include "Account.h"

Account::Account(int n, std::string nm, double b)
    : accNo(n), name(std::move(nm)), balance(b),
      historyHead(nullptr), left(nullptr), right(nullptr) {}
