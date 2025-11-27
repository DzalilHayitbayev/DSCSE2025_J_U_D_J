#include <iostream>
#include "Bank.h"

void printMenu() {
    std::cout << "\n--- Bank Menu ---\n"
              << "1. Create account\n2. Direct deposit\n3. Direct withdraw\n"
              << "4. Enqueue deposit\n5. Enqueue withdraw\n6. Process one\n"
              << "7. Process all\n8. Show history\n9. Show account\n10. List\n0. Exit\n> ";
}

int main() {
    Bank bank;
    while (true) {
        printMenu();
        int cmd;
        std::cin >> cmd;
        if (cmd == 0) break;

        if (cmd == 1) {
            int acc; std::string name; double bal;
            std::cout << "Account#: "; std::cin >> acc;
            std::cout << "Name: "; std::cin >> name;
            std::cout << "Initial balance: "; std::cin >> bal;
            bank.createAccount(acc, name, bal);
        }
        else if (cmd == 2) {
            int acc; double amt;
            std::cout << "Account#: "; std::cin >> acc;
            std::cout << "Deposit: "; std::cin >> amt;
            bank.directDeposit(acc, amt);
        }
        else if (cmd == 3) {
            int acc; double amt;
            std::cout << "Account#: "; std::cin >> acc;
            std::cout << "Withdraw: "; std::cin >> amt;
            bank.directWithdraw(acc, amt);
        }
        else if (cmd == 4 || cmd == 5) {
            int acc; double amt;
            std::cout << "Account#: "; std::cin >> acc;
            std::cout << "Amount: "; std::cin >> amt;
            bank.enqueueTransaction(acc, 
                cmd == 4 ? Transaction::DEPOSIT : Transaction::WITHDRAW,
                amt);
        }
        else if (cmd == 6) {
            bank.processOnePending();
        }
        else if (cmd == 7) {
            bank.processAllPending();
        }
        else if (cmd == 8) {
            int acc; std::cout << "Account#: "; std::cin >> acc;
            bank.showTransactionHistory(acc);
        }
        else if (cmd == 9) {
            int acc; std::cout << "Account#: "; std::cin >> acc;
            bank.showAccountInfo(acc);
        }
        else if (cmd == 10) {
            bank.listAllAccounts();
        }
    }
}
