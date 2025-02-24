#include <iostream>

// Incorrect: Uses const reference, does not allow modification
void swap(const int &a, const int &b) {
    std::cout << "swap(const int &a, const int &b) called - Cannot modify values! " << a << " " << b <<std::endl;
}

// Incorrect: Uses pass-by-value, modifies local copies only
void swap1(int a, int b) {
    std::cout << "swap(int a, int b) called - Swaps local copies only!\n";
    int temp = a;
    a = b;
    b = temp;
}

// Correct: Uses pass-by-reference, modifies caller's variables
void swap2(int &a, int &b) {
    std::cout << "swap(int &a, int &b) called - Modifies caller's variables!\n";
    int temp = a;
    a = b;
    b = temp;
}

// Correct: Uses pointers, modifies caller's variables
void swap3(int *a, int *b) {
    std::cout << "swap(int *a, int *b) called - Modifies caller's variables!\n";
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 5, y = 10;
    
    std::cout << "Before swap: x = " << x << ", y = " << y << "\n";

    // Test each function

    std::cout << "\nTesting swap(const int &a, const int &b):\n";
     swap(static_cast<const int&>(x), static_cast<const int&>(y));  //  Does nothing

    std::cout << "\nTesting swap(int a, int b):\n";
    swap1(x, y);  // Swaps only local copies

    std::cout << "After incorrect swaps: x = " << x << ", y = " << y << "\n";

    std::cout << "\nTesting swap(int &a, int &b):\n";
    swap2(x, y);  // Works, modifies caller's variables

    std::cout << "After reference swap: x = " << x << ", y = " << y << "\n";

    std::cout << "\nResetting values...\n";
    x = 5; y = 10;

    std::cout << "Before pointer swap: x = " << x << ", y = " << y << "\n";

    std::cout << "\nTesting swap(int *a, int *b):\n";
    swap3(&x, &y);  // Works, modifies caller's variables

    std::cout << "After pointer swap: x = " << x << ", y = " << y << "\n";

    return 0;
}