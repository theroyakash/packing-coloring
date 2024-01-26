#if !defined(TEST_UTILS)
#define TEST_UTILS

#include <cassert>
#include <iomanip>
#include <iostream>
#include <string>

void printPassing() {
    std::cout << "\033[32m[ passed ]\033[0m" << std::endl;
}

void printNotPassing() {
    std::cout << "\033[31m[ failed ]\033[0m" << std::endl;
}

void printBox(const std::string &message) {
    int width = message.length() + 2;

    // Top border
    std::cout << '+' << std::string(width, '-') << '+' << std::endl;

    // Message with padding
    std::cout << "    " << message << std::endl;

    // Bottom border
    std::cout << '+' << std::string(width, '-') << '+' << std::endl;
}

namespace TestAssertService {
void setUp(std::string fn_name) {
    std::string message = "starting tests for: \033[32m" + fn_name + "\033[0m";
    printBox(message);
}

void cleanUp(std::string fn_name) {
    std::string message = "ending tests for: \033[31m" + fn_name + "\033[0m";
    printBox(message);
}

template <typename T>
static void assertEqual(T actual, T expected, const std::string &testName) {
    std::cout << std::left << std::setw(30) << testName;
    if (actual == expected)
        printPassing();
    else
        printNotPassing();
}

template <typename T>
static void assertNotEqual(T actual, T expected, const std::string &testName) {
    std::cout << std::left << std::setw(30) << testName;
    if (actual != expected)
        printPassing();
    else
        printNotPassing();
}

template <typename T>
static void assertLessThan(T actual, T expected, const std::string &testName) {
    std::cout << std::left << std::setw(30) << testName;
    if (actual < expected)
        printPassing();
    else
        printNotPassing();
}

template <typename T>
static void assertGreaterThan(T actual, T expected, const std::string &testName) {
    std::cout << std::left << std::setw(30) << testName;
    if (actual > expected)
        printPassing();
    else
        printNotPassing();
}

template <typename T>
static void assertLessThanOrEqual(T actual, T expected, const std::string &testName) {
    std::cout << std::left << std::setw(30) << testName;
    if (actual <= expected)
        printPassing();
    else
        printNotPassing();
}

template <typename T>
static void assertGreaterThanOrEqual(T actual, T expected, const std::string &testName) {
    std::cout << std::left << std::setw(30) << testName;
    if (actual >= expected)
        printPassing();
    else
        printNotPassing();
}

template <typename T>
static void assertNull(T actual, const std::string &testName) {
    std::cout << std::left << std::setw(30) << testName;
    if (actual == nullptr)
        printPassing();
    else
        printNotPassing();
}

template <typename T>
static void assertNotNull(T actual, const std::string &testName) {
    std::cout << std::left << std::setw(30) << testName;
    if (actual != nullptr)
        printPassing();
    else
        printNotPassing();
}

template <typename T>
static void assertTrue(T condition, const std::string &testName) {
    std::cout << std::left << std::setw(30) << testName;
    if (condition)
        printPassing();
    else
        printNotPassing();
}

template <typename T>
static void assertFalse(T condition, const std::string &testName) {
    std::cout << std::left << std::setw(30) << testName;
    if (!condition)
        printPassing();
    else
        printNotPassing();
}
}  // namespace TestAssertService

#endif  // TEST_UTILS
