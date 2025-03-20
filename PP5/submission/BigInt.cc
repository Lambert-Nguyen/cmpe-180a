#include "BigInt.h"
#include <iostream>

// Remove leading zeros.
void BigInt::removeLeadingZeros() {
    while (digits.size() > 1 && digits.back() == 0)
        digits.pop_back();
    if (digits.size() == 1 && digits[0] == 0)
        sign = 1; // Zero is stored as positive.
}

// Add absolute values.
BigInt BigInt::addAbs(const BigInt &a, const BigInt &b) {
    BigInt result;
    result.digits.clear(); // Clear the default zero.
    int carry = 0;
    int n = std::max(a.digits.size(), b.digits.size());
    for (int i = 0; i < n || carry; i++) {
        int digitA = (i < a.digits.size() ? a.digits[i] : 0);
        int digitB = (i < b.digits.size() ? b.digits[i] : 0);
        int sum = digitA + digitB + carry;
        result.digits.push_back(sum % 10);
        carry = sum / 10;
    }
    result.removeLeadingZeros();
    return result;
}

// Subtract absolute values; assume |a| >= |b|.
BigInt BigInt::subtractAbs(const BigInt &a, const BigInt &b) {
    BigInt result;
    result.digits.clear(); // Clear the default zero.
    int carry = 0;
    for (size_t i = 0; i < a.digits.size(); i++) {
        int digitA = a.digits[i];
        int digitB = (i < b.digits.size() ? b.digits[i] : 0);
        int sub = digitA - digitB - carry;
        if (sub < 0) {
            sub += 10;
            carry = 1;
        } else {
            carry = 0;
        }
        result.digits.push_back(sub);
    }
    result.removeLeadingZeros();
    return result;
}

// Compare absolute values.
int BigInt::compareAbs(const BigInt &a, const BigInt &b) {
    if (a.digits.size() > b.digits.size())
        return 1;
    if (a.digits.size() < b.digits.size())
        return -1;
    for (int i = a.digits.size() - 1; i >= 0; i--) {
        if (a.digits[i] > b.digits[i])
            return 1;
        if (a.digits[i] < b.digits[i])
            return -1;
    }
    return 0;
}

// Default constructor.
BigInt::BigInt() : sign(1) {
    digits.push_back(0);
}

// Constructor from a C-style array of characters.
BigInt::BigInt(const char* s, int len) {
    if (len <= 0)
        throw std::invalid_argument("Empty string provided");
    int index = 0;
    if (s[0] == '-') {
        sign = -1;
        index = 1;
    } else {
        sign = 1;
        if (s[0] == '+')
            index = 1;
    }
    // Skip any leading zeros.
    while (index < len && s[index] == '0')
        index++;
    if (index == len) {
        sign = 1;
        digits.push_back(0);
    } else {
        // Read the digits in normal order then reverse.
        for (int i = index; i < len; i++) {
            if (!std::isdigit(s[i])) {
                std::cerr << "Error: Invalid character in input string: " << s[i] << std::endl;
                throw std::invalid_argument("Invalid character in input string");
            }
            digits.push_back(s[i] - '0');
        }
        std::reverse(digits.begin(), digits.end());
    }
}

// Constructor from a vector of digits.
BigInt::BigInt(const std::vector<int>& vec) {
    if (vec.empty()) {
        sign = 1;
        digits.push_back(0);
    } else {
        std::vector<int> temp = vec;
        if (temp[0] < 0) {
            sign = -1;
            temp[0] = -temp[0]; // make the digit positive
        } else {
            sign = 1;
        }
        for (int d : temp) {
            if (d < 0 || d > 9) {
                std::cerr << "Error: Invalid digit in vector: " << d << std::endl;
                throw std::invalid_argument("Invalid digit in vector");
            }
        }
        auto it = temp.begin();
        while (it != temp.end() - 1 && *it == 0)
            it++;
        temp.erase(temp.begin(), it);
        digits = temp;
        std::reverse(digits.begin(), digits.end());
    }
    removeLeadingZeros();
}

// Constructor from a long long integer.
BigInt::BigInt(long long num) {
    if (num < 0) {
        sign = -1;
        num = -num;
    } else {
        sign = 1;
    }
    if (num == 0)
        digits.push_back(0);
    while (num) {
        digits.push_back(num % 10);
        num /= 10;
    }
}

// Unary minus operator.
BigInt BigInt::operator-() const {
    BigInt result(*this);
    if (!(result.digits.size() == 1 && result.digits[0] == 0))
        result.sign = -result.sign;
    return result;
}

// Addition operator.
BigInt BigInt::operator+(const BigInt &other) const {
    BigInt result;
    if (sign == other.sign) {
        result = addAbs(*this, other);
        result.sign = sign;
    } else {
        int cmp = compareAbs(*this, other);
        if (cmp == 0)
            return BigInt(0); // they cancel each other
        else if (cmp > 0) {
            result = subtractAbs(*this, other);
            result.sign = sign;
        } else {
            result = subtractAbs(other, *this);
            result.sign = other.sign;
        }
    }
    result.removeLeadingZeros();
    return result;
}

// Subtraction operator.
BigInt BigInt::operator-(const BigInt &other) const {
    return *this + (-other);
}

// Multiplication operator.
BigInt BigInt::operator*(const BigInt &other) const {
    BigInt result;
    result.sign = sign * other.sign;
    result.digits.assign(digits.size() + other.digits.size(), 0);
    
    for (size_t i = 0; i < digits.size(); i++) {
        long carry = 0;
        for (size_t j = 0; j < other.digits.size() || carry; j++) {
            long cur = result.digits[i + j] +
                       digits[i] * (j < other.digits.size() ? other.digits[j] : 0) + carry;
            result.digits[i + j] = cur % 10;
            carry = cur / 10;
        }
    }
    result.removeLeadingZeros();
    return result;
}

// Overloaded factorial operator.
BigInt BigInt::operator!() const {
    if (*this < BigInt(0)) {
        std::cerr << "Error: Factorial not defined for negative numbers." << std::endl;
        throw std::runtime_error("Factorial not defined for negative numbers.");
    }
    if (*this <= BigInt(1))
        return BigInt(1);
    BigInt result(1);
    BigInt counter(2);
    BigInt end(*this);
    while (counter <= end) {
        result = result * counter;
        counter++;
    }
    return result;
}

// Equality operator.
bool BigInt::operator==(const BigInt &other) const {
    return sign == other.sign && digits == other.digits;
}

// Less-than operator.
bool BigInt::operator<(const BigInt &other) const {
    if (sign != other.sign)
        return sign < other.sign;
    int cmp = compareAbs(*this, other);
    if (sign == 1)
        return cmp < 0;
    else
        return cmp > 0;
}

// Greater-than operator.
bool BigInt::operator>(const BigInt &other) const {
    return other < *this;
}

// Less-than-or-equal operator.
bool BigInt::operator<=(const BigInt &other) const {
    return !(*this > other);
}

// Greater-than-or-equal operator.
bool BigInt::operator>=(const BigInt &other) const {
    return !(*this < other);
}

// Prefix increment: ++a
BigInt& BigInt::operator++() {
    *this = *this + BigInt(1);
    return *this;
}

// Postfix increment: a++
BigInt BigInt::operator++(int) {
    BigInt temp(*this);
    *this = *this + BigInt(1);
    return temp;
}

// Prefix decrement: --a
BigInt& BigInt::operator--() {
    *this = *this - BigInt(1);
    return *this;
}

// Postfix decrement: a--
BigInt BigInt::operator--(int) {
    BigInt temp(*this);
    *this = *this - BigInt(1);
    return temp;
}

// Convert number to its string representation.
std::string BigInt::toString() const {
    std::string str;
    if (digits.empty())
        return "0";
    if (sign == -1)
        str.push_back('-');
    for (int i = digits.size() - 1; i >= 0; i--)
        str.push_back('0' + digits[i]);
    return str;
}

// Overload stream insertion operator for printing.
std::ostream& operator<<(std::ostream &out, const BigInt &num) {
    out << num.toString();
    return out;
}

// Overload stream extraction operator for input.
std::istream& operator>>(std::istream &in, BigInt &num) {
    std::string input;
    in >> input;
    num = BigInt(input.c_str(), input.size());
    return in;
}