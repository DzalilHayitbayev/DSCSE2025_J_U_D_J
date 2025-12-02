#include <iostream>
#include <string>
#include <limits>
#include "Bank.h"

using namespace std;

void printMenu() {
    cout << "\n________________ Bank Menu ________________\n"
        << "1. Create account\n2. Direct deposit\n3. Direct withdraw\n"
        << "4. Enqueue deposit\n5. Enqueue withdraw\n6. Process one pending transaction\n"
        << "7. Process all pending transactions\n8. Show transaction history\n9. Show account info\n"
        << "10. List all accounts\n0. Exit\nChoose: ";
}

int readInt() {
    int x;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter a valid integer: ";
    }
    return x;
}

double readDouble() {
    double x;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter a valid number: ";
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
            cout << "Account number: ";
            int acc = readInt();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Holder name: ";
            string name;
            getline(cin, name);
            cout << "Initial balance: ";
            double bal = readDouble();
            // timestamp captured by bank
            if (bank.createAccount(acc, name, bal, Bank::currentDateTime())) {
                cout << "Account created.\n";
            }
            else {
                cout << "Account with this number already exists.\n";
            }
        }
        else if (cmd == 2) {
            cout << "Account number: "; int acc = readInt();
            cout << "Amount to deposit: "; double amt = readDouble();
            if (bank.directDeposit(acc, amt, Bank::currentDateTime())) cout << "Deposit successful.\n";
            else cout << "Deposit failed (account missing or invalid amount).\n";
        }
        else if (cmd == 3) {
            cout << "Account number: "; int acc = readInt();
            cout << "Amount to withdraw: "; double amt = readDouble();
            if (bank.directWithdraw(acc, amt, Bank::currentDateTime())) cout << "Withdrawal successful.\n";
            else cout << "Withdrawal failed (insufficient funds or account missing).\n";
        }
        else if (cmd == 4 || cmd == 5) {
            cout << "Account number: "; int acc = readInt();
            cout << "Amount: "; double amt = readDouble();
            if (cmd == 4) bank.enqueueDeposit(acc, amt);
            else bank.enqueueWithdraw(acc, amt);
            cout << "Transaction enqueued.\n";
        }
        else if (cmd == 6) {
            if (bank.processOnePending()) cout << "Processed one pending transaction.\n";
            else cout << "No pending transactions.\n";
        }
        else if (cmd == 7) {
            int processed = bank.processPendingAll();
            cout << "Processed " << processed << " pending transactions.\n";
        }
        else if (cmd == 8) {
            cout << "Account number: "; int acc = readInt();
            bank.showTransactionHistory(acc);
        }
        else if (cmd == 9) {
            cout << "Account number: "; int acc = readInt();
            bank.showAccountInfo(acc);
        }
        else if (cmd == 10) {
            bank.listAllAccounts();
        }
        else {
            cout << "Unknown command.\n";
        }
    }
    cout << "Goodbye.\n";
    return 0;
}
