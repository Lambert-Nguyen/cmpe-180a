#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept> // For std::invalid_argument

std::string mergeStrings(const std::vector<std::string> &a){
    if(a.empty()){
        throw std::invalid_argument("Input vector is empty.");
    }
    std::string result;
    size_t maxLength = 0;

    for(const std::string &str : a){
        maxLength = std::max(maxLength, str.size());
    }
    for(size_t i = 0; i < maxLength; ++i){
        for (const std::string &str : a){
            if (i < str.size()) {
                result += str[i];
            }
        }
    }
    return result;
}
