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
    int sign;// Either +1 or -1.
    std::vector<int> digits;
    void removeLeadingZeros();
    static BigInt addAbs(const BigInt &a, const BigInt &b);
    static BigInt subtractAbs(const BigInt &a, const BigInt &b);
    static int compareAbs(const BigInt &a, const BigInt &b);

public:
    BigInt();
    BigInt(const char* s, int len);
    BigInt(const std::vector<int>& vec);
    BigInt(long long num);

    BigInt operator-() const;
    BigInt operator+(const BigInt &other) const;
    BigInt operator-(const BigInt &other) const;
    BigInt operator*(const BigInt &other) const;
    BigInt operator!() const;
    bool operator==(const BigInt &other) const;
    bool operator<(const BigInt &other) const;
    bool operator>(const BigInt &other) const;
    bool operator<=(const BigInt &other) const;
    bool operator>=(const BigInt &other) const;
    BigInt& operator++();
    BigInt operator++(int);
    BigInt& operator--();
    BigInt operator--(int);
    std::string toString() const;
    friend std::ostream& operator<<(std::ostream &out, const BigInt &num);
    friend std::istream& operator>>(std::istream &in, BigInt &num);
};

#endif