#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <cctype>

class BigInt {
private:
    int sign;                   // Either +1 or -1.
    std::vector<int> digits;    // Stored in reverse order (units digit at index 0).

    // Remove any extra zeros from the most significant end.
    void removeLeadingZeros();

    // Helper to add absolute values (both numbers’ digits are added without considering sign).
    static BigInt addAbs(const BigInt &a, const BigInt &b);

    // Subtract absolute values; assume |a| >= |b|.
    static BigInt subtractAbs(const BigInt &a, const BigInt &b);

    // Compare absolute values.
    // Returns  1 if |a| > |b|, 0 if equal, -1 if |a| < |b|
    static int compareAbs(const BigInt &a, const BigInt &b);

public:
    // Default constructor: initialize to zero.
    BigInt();

    // Constructor from a C-style array of characters.
    BigInt(const char* s, int len);

    // Constructor from a vector of digits.
    BigInt(const std::vector<int>& vec);

    // Constructor from a long long integer.
    BigInt(long long num);

    // Unary minus operator to change the sign.
    BigInt operator-() const;

    // Addition operator.
    BigInt operator+(const BigInt &other) const;

    // Subtraction operator.
    BigInt operator-(const BigInt &other) const;

    // Multiplication operator.
    BigInt operator*(const BigInt &other) const;

    // Overloaded factorial operator.
    BigInt operator!() const;

    // Equality operator.
    bool operator==(const BigInt &other) const;

    // Less-than operator.
    bool operator<(const BigInt &other) const;

    // Greater-than operator.
    bool operator>(const BigInt &other) const;

    // Less-than-or-equal operator.
    bool operator<=(const BigInt &other) const;

    // Greater-than-or-equal operator.
    bool operator>=(const BigInt &other) const;

    // Prefix increment: ++a
    BigInt& operator++();

    // Postfix increment: a++
    BigInt operator++(int);

    // Prefix decrement: --a
    BigInt& operator--();

    // Postfix decrement: a--
    BigInt operator--(int);

    // Convert number to its string representation.
    std::string toString() const;

    // Overload stream insertion operator for printing.
    friend std::ostream& operator<<(std::ostream &out, const BigInt &num);

    // Overload stream extraction operator for input.
    friend std::istream& operator>>(std::istream &in, BigInt &num);
};

#endif