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
    removeLeadingZero();

}

BigInt::BigInt(const char num[], size_t sizeNum){
    isNegative = (num[0] == '-');
    for (size_t i =(isNegative ? 1:0); i < sizeNum; i++){
        if(isdigit(num[i])){
            digit.insert(digit.begin(), num[i] - '0');
        }
        removeLeadingZero();
    }
}

void BigInt::removeLeadingZero(){
    while (digit.size() > 1 && digit.back ==0){
        digit.pop_back();
    }
    if(digit.size() == 1 && digit[0] == 0){
        isNegative = false;
    }



}