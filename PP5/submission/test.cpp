#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <cctype>

class BigInt {
private:
    int sign;                   // Either +1 or -1.
    std::vector<int> digits;    // Stored in reverse order (units digit at index 0).

    // Remove any extra zeros from the most significant end.
    void removeLeadingZeros() {
        while (digits.size() > 1 && digits.back() == 0)
            digits.pop_back();
        if (digits.size() == 1 && digits[0] == 0)
            sign = 1; // Zero is stored as positive.
    }
    
    // Helper to add absolute values (both numbers’ digits are added without considering sign).
    static BigInt addAbs(const BigInt &a, const BigInt &b) {
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
    static BigInt subtractAbs(const BigInt &a, const BigInt &b) {
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
    // Returns  1 if |a| > |b|, 0 if equal, -1 if |a| < |b|
    static int compareAbs(const BigInt &a, const BigInt &b) {
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
    
public:
    // Default constructor: initialize to zero.
    BigInt() : sign(1) {
        digits.push_back(0);
    }
    
    // Constructor from a C-style array of characters.
    // The array should contain digits in normal order; a leading '-' indicates a negative number.
    BigInt(const char* s, int len) {
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
                if (!std::isdigit(s[i]))
                    throw std::invalid_argument("Invalid character in input string");
                digits.push_back(s[i] - '0');
            }
            std::reverse(digits.begin(), digits.end());
        }
    }
    
    // Constructor from a vector of digits.
    // Convention: if the first element is negative then that specifies a negative BigInt.
    // Assume the vector is given in most-significant-digit first order.
    BigInt(const std::vector<int>& vec) {
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
            for (int d : temp)
                if (d < 0 || d > 9)
                    throw std::invalid_argument("Invalid digit in vector");
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
    BigInt(long long num) {
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
    
    // Unary minus operator to change the sign.
    BigInt operator-() const {
        BigInt result(*this);
        if (!(result.digits.size() == 1 && result.digits[0] == 0))
            result.sign = -result.sign;
        return result;
    }
    
    // Addition operator.
    BigInt operator+(const BigInt &other) const {
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
    BigInt operator-(const BigInt &other) const {
        return *this + (-other);
    }
    
    // Multiplication operator.
    BigInt operator*(const BigInt &other) const {
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
    // This computes n! for nonnegative BigInt n using iterative multiplication.
    // (For large n this will be extremely slow.)
    BigInt operator!() const {
        if (*this < BigInt(0))
            throw std::runtime_error("Factorial not defined for negative numbers.");
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
    bool operator==(const BigInt &other) const {
        return sign == other.sign && digits == other.digits;
    }
    
    // Less-than operator.
    bool operator<(const BigInt &other) const {
        if (sign != other.sign)
            return sign < other.sign;
        int cmp = compareAbs(*this, other);
        if (sign == 1)
            return cmp < 0;
        else
            return cmp > 0;
    }
    
    // Greater-than operator.
    bool operator>(const BigInt &other) const {
        return other < *this;
    }
    
    // Less-than-or-equal operator.
    bool operator<=(const BigInt &other) const {
        return !(*this > other);
    }
    
    // Greater-than-or-equal operator.
    bool operator>=(const BigInt &other) const {
        return !(*this < other);
    }
    
    // Prefix increment: ++a
    BigInt& operator++() {
        *this = *this + BigInt(1);
        return *this;
    }
    
    // Postfix increment: a++
    BigInt operator++(int) {
        BigInt temp(*this);
        *this = *this + BigInt(1);
        return temp;
    }
    
    // Prefix decrement: --a
    BigInt& operator--() {
        *this = *this - BigInt(1);
        return *this;
    }
    
    // Postfix decrement: a--
    BigInt operator--(int) {
        BigInt temp(*this);
        *this = *this - BigInt(1);
        return temp;
    }
    
    // Convert number to its string representation.
    std::string toString() const {
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
    friend std::ostream& operator<<(std::ostream &out, const BigInt &num) {
        out << num.toString();
        return out;
    }
    
    // Overload stream extraction operator for input.
    friend std::istream& operator>>(std::istream &in, BigInt &num) {
        std::string input;
        in >> input;
        num = BigInt(input.c_str(), input.size());
        return in;
    }
};

int main() {
    // -----------------------------------------
    // Construction and stream output (<<)
    // -----------------------------------------
    char num1[] = "12345678901234567890";
    BigInt bigint1(num1, sizeof(num1) - 1);
    std::cout << "bigint1: " << bigint1 << std::endl;
    
    // -----------------------------------------
    // Addition test cases:
    // -----------------------------------------
    BigInt a("12345678901234567890", 20);
    BigInt b("98765432109876543210", 20);
    BigInt sum = a + b;
    std::cout << a << " + " << b << " = " << sum << std::endl;
    // Expected: 111111111011111111100
    
    BigInt c(-5000), d(3000);
    std::cout << c << " + " << d << " = " << (c + d) << std::endl;
    // Expected: -2000
    
    // -----------------------------------------
    // Subtraction test cases:
    // -----------------------------------------
    BigInt e("100000000000000000000", 21);
    BigInt f("99999999999999999999", 20);
    std::cout << e << " - " << f << " = " << (e - f) << std::endl;
    // Expected: 1
    
    BigInt g(-5000), h(3000);
    std::cout << g << " - " << h << " = " << (g - h) << std::endl;
    // Expected: -8000
    
    // -----------------------------------------
    // Multiplication test cases:
    // -----------------------------------------
    BigInt m(12345), n(6789);
    std::cout << m << " * " << n << " = " << (m * n) << std::endl;
    // Expected: 83810205
    
    BigInt m2(-12345), n2(6789);
    std::cout << m2 << " * " << n2 << " = " << (m2 * n2) << std::endl;
    // Expected: -83810205
    
    // -----------------------------------------
    // Comparison tests:
    // -----------------------------------------
    BigInt comp1(1234567890), comp2(9876543210), comp3(1234567890);
    std::cout << "\nComparisons:" << std::endl;
    std::cout << comp1 << " == " << comp3 << " : " << (comp1 == comp3 ? "true" : "false") << std::endl;
    std::cout << comp1 << " < "  << comp2 << " : " << (comp1 < comp2 ? "true" : "false") << std::endl;
    std::cout << comp2 << " > "  << comp1 << " : " << (comp2 > comp1 ? "true" : "false") << std::endl;
    std::cout << comp1 << " <= " << comp3 << " : " << (comp1 <= comp3 ? "true" : "false") << std::endl;
    std::cout << comp1 << " >= " << comp3 << " : " << (comp1 >= comp3 ? "true" : "false") << std::endl;
    
    // -----------------------------------------
    // Increment / Decrement tests:
    // -----------------------------------------
    BigInt inc(100);
    std::cout << "\nInitial value: " << inc << std::endl;
    std::cout << "++a: " << ++inc << std::endl;  // Expected: 101
    std::cout << "a++: " << inc++ << std::endl;   // Expected: prints 101 then becomes 102
    std::cout << "After a++: " << inc << std::endl; // Expected: 102
    std::cout << "--a: " << --inc << std::endl;     // Expected: 101
    std::cout << "a--: " << inc-- << std::endl;     // Expected: prints 101 then becomes 100
    std::cout << "After a--: " << inc << std::endl;  // Expected: 100
    
    // -----------------------------------------
    // Factorial test (using small number)
    // -----------------------------------------
    BigInt factInput(5);
    std::cout << "\nFactorial of " << factInput << " is " << !factInput << std::endl;
    // Expected: 120
    
    return 0;
}

