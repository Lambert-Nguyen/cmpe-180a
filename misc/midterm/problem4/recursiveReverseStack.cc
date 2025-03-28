#include <stack>

void reverseStack(std::stack<int>& s) {
    if (s.empty()) {
        return;
    }
    int top = s.top();
    s.pop();
    reverseStack(s);
    
    // Insert 'top' at the bottom
    if (s.empty()) {
        s.push(top);
    } else {
        int temp = s.top();
        s.pop();
        s.push(top);
        reverseStack(s);
        s.push(temp);
    }
}