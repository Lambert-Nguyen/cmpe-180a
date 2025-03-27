#include "merge_string.h"
#include <algorithm>
#include <stdexcept>

std::string mergeStrings(const std::vector<std::string>& a) {
    // Check for empty vector
    if (a.empty()) {
        throw std::invalid_argument("Input vector is empty.");
    }

    std::string result;
    size_t maxLength = 0;

    // Find the maximum length of strings in the vector
    for (const std::string &str : a) {
        maxLength = std::max(maxLength, str.size());
    }

    // Interleave characters from each string
    for (size_t i = 0; i < maxLength; ++i) {
        for (const std::string &str : a) {
            if (i < str.size()) {
                result += str[i];
            }
        }
    }

    return result;
}
