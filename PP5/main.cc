#include "BigInt.h"
#include <iostream>
#include <vector>

int main() {
    // Test constructors
    char num1[] = "12345678901234567890";
    BigInt bigint1(num1, sizeof(num1) - 1);
    std::cout << "bigint1: " << bigint1 << std::endl; // Expected: 12345678901234567890

    std::vector<int> vec = {1, 2, 3, 4, 5};
    BigInt bigint2(vec);
    std::cout << "bigint2: " << bigint2 << std::endl; // Expected: 12345

    // Test addition
    BigInt sum1 = BigInt("12345678901234567890", 20) + BigInt("98765432109876543210", 20);
    std::cout << "Addition Test: " << sum1 << std::endl; // Expected: 111111111011111111100

    BigInt sum2 = BigInt("-3000", 5) + BigInt("30000", 5);
    std::cout << "Addition Test: " << sum2 << std::endl; // Expected: -2000

    // Test subtraction
    BigInt diff1 = BigInt("100000000000000000000", 21) - BigInt("99999999999999999999", 20);
    std::cout << "Subtraction Test: " << diff1 << std::endl; // Expected: 1

    BigInt diff2 = BigInt("-5000", 5) - BigInt("3000", 4);
    std::cout << "Subtraction Test: " << diff2 << std::endl; // Expected: -8000

    // Test multiplication
    BigInt prod1 = BigInt("12345", 5) * BigInt("6789", 4);
    std::cout << "Multiplication Test: " << prod1 << std::endl; // Expected: 83810205

    BigInt prod2 = BigInt("-12345", 6) * BigInt("6789", 4);
    std::cout << "Multiplication Test: " << prod2 << std::endl; // Expected: -83810205

    // Test comparisons
    BigInt big1("1234567890", 10), big2("9876543210", 10), big3("1234567890", 10);
    std::cout << "Comparison Test 1 (==): " << (big1 == big3) << std::endl; // Expected: 1 (true)
    std::cout << "Comparison Test 2 (<): " << (big1 < big2) << std::endl;    // Expected: 1 (true)
    std::cout << "Comparison Test 3 (>): " << (big2 > big1) << std::endl;    // Expected: 1 (true)
    std::cout << "Comparison Test 4 (<=): " << (big1 <= big3) << std::endl;   // Expected: 1 (true)
    std::cout << "Comparison Test 5 (>=): " << (big1 >= big3) << std::endl;   // Expected: 1 (true)

    // Test increment/decrement
    BigInt a("100", 3);
    std::cout << "Increment Test 1 (++a): " << ++a << std::endl;             // Expected: 101
    std::cout << "Increment Test 2 (a++): " << a++ << std::endl;              // Expected: 101
    std::cout << "Increment Test 3 (a after a++): " << a << std::endl;          // Expected: 102
    std::cout << "Decrement Test 1 (--a): " << --a << std::endl;              // Expected: 101
    std::cout << "Decrement Test 2 (a--): " << a-- << std::endl;               // Expected: 101
    std::cout << "Decrement Test 3 (a after a--): " << a << std::endl;          // Expected: 100

    return 0;
}
