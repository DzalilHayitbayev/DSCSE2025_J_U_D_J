#include "PendingQueue.h"

PendingQueue::PendingQueue() : head(nullptr), tail(nullptr) {}
PendingQueue::~PendingQueue() { clear(); }

void PendingQueue::enqueue(int accNo, Transaction::Type type, double amount) {
    PendingTx* node = new PendingTx(accNo, type, amount);
    if (!head) {
        head = tail = node;
    }
    else {
        tail->next = node;
        tail = node;
    }
}

bool PendingQueue::dequeue(PendingTx& out) {
    if (!head) return false;
    PendingTx* node = head;
    out = *node; // copy fields
    head = head->next;
    if (!head) tail = nullptr;
    delete node;
    out.next = nullptr; // safety: ensure out.next not dangling
    return true;
}

bool PendingQueue::isEmpty() const { return head == nullptr; }

void PendingQueue::clear() {
    while (head) {
        PendingTx* nx = head->next;
        delete head;
        head = nx;
    }
    tail = nullptr;
}
