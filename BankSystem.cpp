// banking.cpp
#include <iostream>
#include <string>
#include <queue>
#include <memory>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <limits>


using namespace std;

// Utility: get current date/time string
string currentDateTime() {
    auto now = chrono::system_clock::now();
    time_t t = chrono::system_clock::to_time_t(now);
    tm tm{};
#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    char buf[64];
    strftime(buf, sizeof(buf), "%d-%m-%Y %I:%M:%S %p", &tm);
    return string(buf);
}

// Transaction linked-list node
struct Transaction {
    enum Type { DEPOSIT, WITHDRAW } type;
    double amount;
    string timestamp;
    shared_ptr<Transaction> next;

    Transaction(Type t, double a)
        : type(t), amount(a), timestamp(currentDateTime()), next(nullptr) {}
};

// Account node of BST
struct Account {
    int accNo;
    string name;
    double balance;
    shared_ptr<Transaction> historyHead; // head of linked list
    Account* left;
    Account* right;

    Account(int n, string nm, double b)
        : accNo(n), name(move(nm)), balance(b), historyHead(nullptr), left(nullptr), right(nullptr) {}
};

// Pending transaction for queue
struct PendingTx {
    int accNo;
    Transaction::Type type;
    double amount;
    // optional scheduled time or id could be added
    PendingTx(int a, Transaction::Type t, double amt) : accNo(a), type(t), amount(amt) {}
};

// Bank class
class Bank {
private:
    Account* root;
    queue<PendingTx> pending;

    // BST insert helper
    Account* insertNode(Account* node, int accNo, const string& name, double balance, bool &inserted) {
        if (!node) {
            inserted = true;
            return new Account(accNo, name, balance);
        }
        if (accNo < node->accNo) node->left = insertNode(node->left, accNo, name, balance, inserted);
        else if (accNo > node->accNo) node->right = insertNode(node->right, accNo, name, balance, inserted);
        else {
            inserted = false; // duplicate
        }
        return node;
    }

    // search helper
    Account* searchNode(Account* node, int accNo) {
        if (!node) return nullptr;
        if (accNo == node->accNo) return node;
        if (accNo < node->accNo) return searchNode(node->left, accNo);
        return searchNode(node->right, accNo);
    }

    // free BST recursively
    void freeTree(Account* node) {
        if (!node) return;
        freeTree(node->left);
        freeTree(node->right);
        delete node;
    }

    // append transaction to account's linked list
    void appendTransaction(Account* acc, Transaction::Type type, double amount) {
        auto tx = make_shared<Transaction>(type, amount);
        if (!acc->historyHead) {
            acc->historyHead = tx;
        } else {
            auto cur = acc->historyHead;
            while (cur->next) cur = cur->next;
            cur->next = tx;
        }
    }

public:
    Bank() : root(nullptr) {}
    ~Bank() { freeTree(root); }

    bool createAccount(int accNo, const string& name, double initialBalance) {
        bool inserted = false;
        root = insertNode(root, accNo, name, initialBalance, inserted);
        if (inserted) {
            // record initial deposit as a transaction if balance > 0
            Account* acc = search(accNo);
            if (acc && initialBalance > 0) appendTransaction(acc, Transaction::DEPOSIT, initialBalance);
        }
        return inserted;
    }

    Account* search(int accNo) { return searchNode(root, accNo); }

    bool directDeposit(int accNo, double amount) {
        if (amount <= 0) return false;
        Account* acc = search(accNo);
        if (!acc) return false;
        acc->balance += amount;
        appendTransaction(acc, Transaction::DEPOSIT, amount);
        return true;
    }

    bool directWithdraw(int accNo, double amount) {
        if (amount <= 0) return false;
        Account* acc = search(accNo);
        if (!acc) return false;
        if (acc->balance < amount) return false;
        acc->balance -= amount;
        appendTransaction(acc, Transaction::WITHDRAW, amount);
        return true;
    }

    void enqueueTransaction(int accNo, Transaction::Type type, double amount) {
        pending.emplace(accNo, type, amount);
    }

    // Process one pending transaction (FIFO). Returns true if processed; false if queue empty
    bool processOnePending() {
        if (pending.empty()) return false;
        PendingTx p = pending.front();
        pending.pop();
        Account* acc = search(p.accNo);
        if (!acc) {
            cout << "Pending tx failed: account " << p.accNo << " not found. Skipping.\n";
            return true;
        }
        if (p.type == Transaction::DEPOSIT) {
            acc->balance += p.amount;
            appendTransaction(acc, Transaction::DEPOSIT, p.amount);
        } else {
            if (acc->balance < p.amount) {
                cout << "Pending tx: insufficient funds for account " << p.accNo << ". Skipping.\n";
            } else {
                acc->balance -= p.amount;
                appendTransaction(acc, Transaction::WITHDRAW, p.amount);
            }
        }
        return true;
    }

    void processAllPending() {
        while (!pending.empty()) processOnePending();
    }

    void showTransactionHistory(int accNo) {
        Account* acc = search(accNo);
        if (!acc) {
            cout << "Account not found.\n";
            return;
        }
        cout << "Transaction history for " << acc->accNo << " (" << acc->name << ")\n";
        auto cur = acc->historyHead;
        if (!cur) {
            cout << "  No transactions yet.\n";
            return;
        }
        int idx = 1;
        while (cur) {
            cout << idx++ << ". ";
            cout << (cur->type == Transaction::DEPOSIT ? "Deposited " : "Withdrawn ");
            cout << fixed << setprecision(2) << cur->amount << " on " << cur->timestamp << '\n';
            cur = cur->next;
        }
    }

    void showAccountInfo(int accNo) {
        Account* acc = search(accNo);
        if (!acc) {
            cout << "Account not found.\n";
            return;
        }
        cout << "Account: " << acc->accNo << "\n  Name: " << acc->name
             << "\n  Balance: " << fixed << setprecision(2) << acc->balance << "\n";
        // count transactions
        int cnt = 0;
        auto cur = acc->historyHead;
        while (cur) { ++cnt; cur = cur->next; }
        cout << "  Total transactions: " << cnt << "\n";
    }

    // in-order traversal to list accounts sorted by accNo
    void listAllAccounts() {
        cout << "Accounts (in-order):\n";
        inOrderPrint(root);
    }

private:
    void inOrderPrint(Account* node) {
        if (!node) return;
        inOrderPrint(node->left);
        cout << "  " << node->accNo << " | " << node->name << " | Balance: " << fixed << setprecision(2) << node->balance << '\n';
        inOrderPrint(node->right);
    }
};

// ---------- Simple interactive menu ----------
void printMenu() {
    cout << "\n--- Bank Menu ---\n"
         << "1. Create account\n2. Direct deposit\n3. Direct withdraw\n4. Enqueue deposit\n5. Enqueue withdraw\n6. Process one pending transaction\n7. Process all pending transactions\n8. Show transaction history\n9. Show account info\n10. List all accounts\n0. Exit\nChoose: ";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Bank bank;
    while (true) {
        printMenu();
        int cmd;
        if (!(cin >> cmd)) break;
        if (cmd == 0) break;

        if (cmd == 1) {
            int acc; string name; double balance;
            cout << "Account number: "; cin >> acc;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Holder name: "; getline(cin, name);
            cout << "Initial balance: "; cin >> balance;
            if (bank.createAccount(acc, name, balance)) cout << "Account created.\n";
            else cout << "Account with this number already exists.\n";
        } else if (cmd == 2) {
            int acc; double amt;
            cout << "Account number: "; cin >> acc;
            cout << "Amount to deposit: "; cin >> amt;
            if (bank.directDeposit(acc, amt)) cout << "Deposit successful.\n";
            else cout << "Deposit failed (account missing or invalid amount).\n";
        } else if (cmd == 3) {
            int acc; double amt;
            cout << "Account number: "; cin >> acc;
            cout << "Amount to withdraw: "; cin >> amt;
            if (bank.directWithdraw(acc, amt)) cout << "Withdrawal successful.\n";
            else cout << "Withdrawal failed (insufficient funds or account missing).\n";
        } else if (cmd == 4 || cmd == 5) {
            int acc; double amt;
            cout << "Account number: "; cin >> acc;
            cout << "Amount: "; cin >> amt;
            Transaction::Type t = (cmd == 4 ? Transaction::DEPOSIT : Transaction::WITHDRAW);
            bank.enqueueTransaction(acc, t, amt);
            cout << "Transaction enqueued.\n";
        } else if (cmd == 6) {
            if (bank.processOnePending()) cout << "Processed one pending transaction.\n";
            else cout << "No pending transactions.\n";
        } else if (cmd == 7) {
            bank.processAllPending();
            cout << "All pending processed.\n";
        } else if (cmd == 8) {
            int acc; cout << "Account number: "; cin >> acc;
            bank.showTransactionHistory(acc);
        } else if (cmd == 9) {
            int acc; cout << "Account number: "; cin >> acc;
            bank.showAccountInfo(acc);
        } else if (cmd == 10) {
            bank.listAllAccounts();
        } else {
            cout << "Unknown command.\n";
        }
    }

    cout << "Goodbye.\n";
    return 0;
}
