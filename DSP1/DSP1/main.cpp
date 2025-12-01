#include <iostream>
#include <string>
#include <limits>
#include "Bank.h"

void printMenu() {
    std::cout << "\n--- Bank Menu ---\n"
        << "1. Create account\n2. Direct deposit\n3. Direct withdraw\n"
        << "4. Enqueue deposit\n5. Enqueue withdraw\n6. Process one pending transaction\n"
        << "7. Process all pending transactions\n8. Show transaction history\n9. Show account info\n"
        << "10. List all accounts\n0. Exit\nChoose: ";
}

// safe read helpers
int readInt() {
    int x;
    while (!(std::cin >> x)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a valid integer: ";
    }
    return x;
}

double readDouble() {
    double x;
    while (!(std::cin >> x)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a valid number: ";
    }
    return x;
}

int main() {
    Bank bank;
    while (true) {
        printMenu();
        int cmd = readInt();
        if (cmd == 0) break;

        if (cmd == 1) {
            std::cout << "Account number: ";
            int acc = readInt();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Holder name: ";
            std::string name;
            std::getline(std::cin, name);
            std::cout << "Initial balance: ";
            double bal = readDouble();
            // timestamp captured by bank
            if (bank.createAccount(acc, name, bal, Bank::currentDateTime())) {
                std::cout << "Account created.\n";
            }
            else {
                std::cout << "Account with this number already exists.\n";
            }
        }
        else if (cmd == 2) {
            std::cout << "Account number: "; int acc = readInt();
            std::cout << "Amount to deposit: "; double amt = readDouble();
            if (bank.directDeposit(acc, amt, Bank::currentDateTime())) std::cout << "Deposit successful.\n";
            else std::cout << "Deposit failed (account missing or invalid amount).\n";
        }
        else if (cmd == 3) {
            std::cout << "Account number: "; int acc = readInt();
            std::cout << "Amount to withdraw: "; double amt = readDouble();
            if (bank.directWithdraw(acc, amt, Bank::currentDateTime())) std::cout << "Withdrawal successful.\n";
            else std::cout << "Withdrawal failed (insufficient funds or account missing).\n";
        }
        else if (cmd == 4 || cmd == 5) {
            std::cout << "Account number: "; int acc = readInt();
            std::cout << "Amount: "; double amt = readDouble();
            if (cmd == 4) bank.enqueueDeposit(acc, amt);
            else bank.enqueueWithdraw(acc, amt);
            std::cout << "Transaction enqueued.\n";
        }
        else if (cmd == 6) {
            if (bank.processOnePending()) std::cout << "Processed one pending transaction.\n";
            else std::cout << "No pending transactions.\n";
        }
        else if (cmd == 7) {
            int processed = bank.processPendingAll();
            std::cout << "Processed " << processed << " pending transactions.\n";
        }
        else if (cmd == 8) {
            std::cout << "Account number: "; int acc = readInt();
            bank.showTransactionHistory(acc);
        }
        else if (cmd == 9) {
            std::cout << "Account number: "; int acc = readInt();
            bank.showAccountInfo(acc);
        }
        else if (cmd == 10) {
            bank.listAllAccounts();
        }
        else {
            std::cout << "Unknown command.\n";
        }
    }
    std::cout << "Goodbye.\n";
    return 0;
}
