#include <iostream>
using namespace std;

int countWays(int n) {
    if (n < 0) return 0;
    if (n == 0) return 1;
    return countWays(n - 1) + countWays(n - 2) + countWays(n - 3);
}

int main() {
    int n = 3;  // Example: A staircase of 3 steps
    cout << "Number of ways to climb " << n << " steps: " << countWays(n) << endl;
    return 0;
}
