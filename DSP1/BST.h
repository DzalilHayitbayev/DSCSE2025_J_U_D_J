#pragma once
#include "Account.h"

class BST {
public:
    BST();
    ~BST();

    // insert account; returns true if inserted, false if duplicate
    bool insert(Account* account);

    // find account by account number
    Account* find(int accNo) const;

    // in-order traversal printing a brief info line
    void inOrderPrint() const;

    // apply a function to every node (in-order). fun(Account*)
    template<typename Func>
    void traverseInOrder(Func f) const {
        traverseInOrderImpl(root, f);
    }

private:
    Account* root;

    Account* insertImpl(Account* node, Account* account, bool& inserted);
    Account* findImpl(Account* node, int accNo) const;
    void inOrderImpl(Account* node) const;
    void destroyImpl(Account* node);

    template<typename Func>
    void traverseInOrderImpl(Account* node, Func f) const {
        if (!node) return;
        traverseInOrderImpl(node->left, f);
        f(node);
        traverseInOrderImpl(node->right, f);
    }
};
