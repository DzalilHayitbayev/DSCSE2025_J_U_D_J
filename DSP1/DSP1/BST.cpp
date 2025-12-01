#include "BST.h"
#include <iostream>
#include <iomanip>

BST::BST() : root(nullptr) {}
BST::~BST() { destroyImpl(root); }

bool BST::insert(Account* account) {
    bool inserted = false;
    root = insertImpl(root, account, inserted);
    return inserted;
}

Account* BST::insertImpl(Account* node, Account* account, bool& inserted) {
    if (!node) {
        inserted = true;
        return account;
    }
    if (account->getAccNo() < node->getAccNo()) {
        node->left = insertImpl(node->left, account, inserted);
    }
    else if (account->getAccNo() > node->getAccNo()) {
        node->right = insertImpl(node->right, account, inserted);
    }
    else {
        // duplicate: do not insert
        inserted = false;
    }
    return node;
}

Account* BST::find(int accNo) const { return findImpl(root, accNo); }

Account* BST::findImpl(Account* node, int accNo) const {
    if (!node) return nullptr;
    if (accNo == node->getAccNo()) return node;
    if (accNo < node->getAccNo()) return findImpl(node->left, accNo);
    return findImpl(node->right, accNo);
}

void BST::inOrderPrint() const { inOrderImpl(root); }

void BST::inOrderImpl(Account* node) const {
    if (!node) return;
    inOrderImpl(node->left);
    std::cout << "  " << node->getAccNo() << " | " << node->getName()
        << " | Balance: " << std::fixed << std::setprecision(2) << node->getBalance() << "\n";
    inOrderImpl(node->right);
}

void BST::destroyImpl(Account* node) {
    if (!node) return;
    destroyImpl(node->left);
    destroyImpl(node->right);
    delete node; // Account destructor will free its TransactionList
}
