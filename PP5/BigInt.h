#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


class BigInt{
    private:
    std::vector<int> digit;
    bool isNegative;
    void removeLeadingZeros();

    public: 
    BigInt();
    BigInt(const std::vector<int> &digit);
    BigInt(const char num[], size_t size);

    BigInt operator+(const BigInt& other) const;
    BigInt operator-(const BigInt& other) const;
    BigInt operator*(const BigInt& other) const;
    BigInt operator!() const;

    bool operator==(const BigInt& other) const;
    bool operator<(const BigInt& other) const;
    bool operator>(const BigInt& other) const;
    bool operator<=(const BigInt& other) const;
    bool operator>=(const BigInt& other) const;

    BigInt& operator++();  // Pre-increment
    BigInt operator++(int); // Post-increment
    BigInt& operator--();  // Pre-decrement
    BigInt operator--(int); // Post-decrement

    friend std::ostream& operator<<(std::ostream& out, const BigInt& num);
    friend std::istream& operator>>(std::istream& in, BigInt& num);
};

#endif