#include "BigInt.h"
#include <cctype>
using std::vector;
using std::reverse;
using std::isdigit;

BigInt::BigInt() : isNegative(false){
    digit.push_back(0);
}

BigInt::BigInt(const vector<int> &num){
    if(!num.empty() && num[0] < 0){
        isNegative = true;
        digit.assign(num.begin() + 1, num.end());
    } else{
        isNegative = false;
        digit = num;
    }
    reverse(digit.begin(), digit.end());
    removeLeadingZeros();
}

BigInt::BigInt(const char num[], size_t sizeNum) {
    isNegative = (num[0] == '-');  
    for (size_t i = (isNegative ? 1 : 0); i < sizeNum; i++) {
        if (isdigit(num[i])) {
            digit.insert(digit.begin(), num[i] - '0');
        } else if (num[i] == '\0') {  // ✅ Allow null terminator for strings
            continue;
        } else {
            std::cerr << "Invalid character in input string." << std::endl;
            exit(1);
        }
    }
    removeLeadingZeros();
}

void BigInt::removeLeadingZeros(){
    while (digit.size() > 1 && digit.back() == 0){
        digit.pop_back();
    }
    if(digit.size() == 1 && digit[0] == 0){
        isNegative = false;
    }
}

// Addition operator
BigInt BigInt::operator+(const BigInt& other) const {
    if (isNegative == other.isNegative) {
        BigInt result;
        result.isNegative = isNegative;
        int carry = 0;
        size_t maxSize = std::max(digit.size(), other.digit.size());

        for (size_t i = 0; i < maxSize || carry; i++) {
            int sum = carry;
            if (i < digit.size()) sum += digit[i];
            if (i < other.digit.size()) sum += other.digit[i];

            result.digit.push_back(sum % 10);
            carry = sum / 10;
        }

        if (carry) {
            result.digit.push_back(carry);
        }

        result.removeLeadingZeros();
        return result;
    } else {
        if (*this > -other) {  // ✅ Correct negative comparison
            return *this - (-other);
        } else {
            return -((-*this) - other);
        }
    }
}

// Subtraction operator
BigInt BigInt::operator-(const BigInt& other) const {
    if (isNegative != other.isNegative) {
        return *this + (-other);
    }

    if (*this < other) {
        return -(other - *this);
    }

    BigInt result;
    result.isNegative = isNegative;
    int borrow = 0;

    for (size_t i = 0; i < digit.size(); i++) {
        int diff = digit[i] - borrow - (i < other.digit.size() ? other.digit[i] : 0);
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.digit.push_back(diff);
    }

    result.removeLeadingZeros();  // ✅ Remove extra zeros
    return result;
}

// Multiplication operator
BigInt BigInt::operator*(const BigInt& other) const {
    BigInt result;
    size_t prodSize = digit.size() + other.digit.size();
    result.digit.resize(prodSize, 0);
    result.isNegative = (isNegative != other.isNegative);

    for (size_t i = 0; i < digit.size(); i++) {
        int carry = 0;
        for (size_t j = 0; j < other.digit.size() || carry; j++) {
            int sum = result.digit[i + j] + digit[i] * (j < other.digit.size() ? other.digit[j] : 0) + carry;
            result.digit[i + j] = sum % 10;
            carry = sum / 10;
        }
    }

    result.removeLeadingZeros();
    return result;
}

// Logical NOT operator
BigInt BigInt::operator!() const {
    return (*this == BigInt("0", 2)) ? BigInt("1", 2) : BigInt("0", 2);
}

BigInt BigInt::operator-() const {
    BigInt result = *this;
    if (!(result.digit.size() == 1 && result.digit[0] == 0)) { // Avoid flipping zero sign
        result.isNegative = !isNegative;
    }
    return result;
}

// Comparison operators
bool BigInt::operator==(const BigInt& other) const {
    return digit == other.digit && isNegative == other.isNegative;
}

bool BigInt::operator<(const BigInt& other) const {
    if (isNegative != other.isNegative)
        return isNegative;
    
    if (digit.size() != other.digit.size())
        return (digit.size() < other.digit.size()) ^ isNegative;
    
    for (size_t i = digit.size(); i-- > 0; ) {
        if (digit[i] != other.digit[i])
            return (digit[i] < other.digit[i]) ^ isNegative;
    }
    return false;
}

bool BigInt::operator>(const BigInt& other) const {
    return other < *this;
}

bool BigInt::operator<=(const BigInt& other) const {
    return !(other < *this);
}

bool BigInt::operator>=(const BigInt& other) const {
    return !(*this < other);
}

// Stream operators
std::ostream& operator<<(std::ostream& out, const BigInt& num) {
    if (num.isNegative) out << '-';
    for (size_t i = num.digit.size(); i-- > 0; ) {
        out << num.digit[i];
    }
    return out;
}

std::istream& operator>>(std::istream& in, BigInt& num) {
    std::string input;
    in >> input;
    num = BigInt(input.c_str(), input.size());
    return in;
}
// Pre-increment operator
BigInt& BigInt::operator++() {
    int carry = 1;
    for (size_t i = 0; i < digit.size() && carry; i++) {
        int sum = digit[i] + carry;
        digit[i] = sum % 10;
        carry = sum / 10;
    }
    if (carry) digit.push_back(carry);
    return *this;
}

BigInt BigInt::operator++(int) {
    BigInt temp = *this;
    ++(*this);
    return temp;
}

// Pre-decrement operator
BigInt& BigInt::operator--() {
    if (*this == BigInt("0", 2)) {
        return *this; // Prevent underflow (negative numbers not supported)
    }

    int borrow = 1;
    for (size_t i = 0; i < digit.size() && borrow; i++) {
        if (digit[i] > 0) {
            digit[i]--;
            borrow = 0;
        } else {
            digit[i] = 9;
        }
    }

    removeLeadingZeros();
    return *this;
}

BigInt BigInt::operator--(int) {
    BigInt temp = *this;
    --(*this);
    return temp;
}