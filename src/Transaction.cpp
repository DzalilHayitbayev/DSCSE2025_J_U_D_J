#include "Transaction.h"
#include <chrono>
#include <ctime>

std::string currentDateTime() {
    auto now = std::chrono::system_clock::now();
    time_t t = std::chrono::system_clock::to_time_t(now);
    tm tm{};
#if defined(_WIN32)
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    char buf[64];
    strftime(buf, sizeof(buf), "%d-%m-%Y %I:%M:%S %p", &tm);
    return std::string(buf);
}

Transaction::Transaction(Type t, double a)
    : type(t), amount(a), timestamp(currentDateTime()), next(nullptr) {}
