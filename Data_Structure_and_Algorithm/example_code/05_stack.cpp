// 05_stack.cpp - Stack: Postfix Evaluation, Balanced Symbols
// Knowledge points: LIFO, push/pop O(1), applications

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// ===== Array-based Stack =====
template <typename T>
class Stack {
private:
    T* array;
    int topIdx;
    int capacity;

public:
    Stack(int cap = 100) : capacity(cap), topIdx(-1) {
        array = new T[capacity];
    }
    ~Stack() { delete[] array; }

    bool isEmpty() const { return topIdx == -1; }
    bool isFull() const { return topIdx == capacity - 1; }
    int size() const { return topIdx + 1; }

    void push(T val) {
        if (isFull()) { cout << "Stack overflow!" << endl; return; }
        array[++topIdx] = val;
    }

    T pop() {
        if (isEmpty()) { cout << "Stack underflow!" << endl; return T(); }
        return array[topIdx--];
    }

    T top() const {
        if (isEmpty()) { cout << "Stack is empty!" << endl; return T(); }
        return array[topIdx];
    }
};

// ===== Application 1: Postfix Expression Evaluation =====
// Algorithm: scan left to right, push operands, pop 2 for operators
int evaluatePostfix(string expr) {
    Stack<int> s;

    for (char c : expr) {
        if (isspace(static_cast<unsigned char>(c))) continue;
        if (isdigit(c)) {
            s.push(c - '0');  // Convert char to int
        } else {
            if (s.size() < 2) {
                cout << "Invalid postfix expression!" << endl;
                return 0;
            }
            int op2 = s.pop();
            int op1 = s.pop();
            switch (c) {
                case '+': s.push(op1 + op2); break;
                case '-': s.push(op1 - op2); break;
                case '*': s.push(op1 * op2); break;
                case '/':
                    if (op2 == 0) {
                        cout << "Division by zero!" << endl;
                        return 0;
                    }
                    s.push(op1 / op2);
                    break;
                default:
                    cout << "Invalid token in postfix expression!" << endl;
                    return 0;
            }
        }
    }
    if (s.size() != 1) {
        cout << "Invalid postfix expression!" << endl;
        return 0;
    }
    return s.pop();
}

// ===== Application 2: Balanced Symbols =====
bool isBalanced(string s) {
    Stack<char> stk;

    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            stk.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (stk.isEmpty()) return false;
            char top = stk.pop();
            if ((c == ')' && top != '(') ||
                (c == ']' && top != '[') ||
                (c == '}' && top != '{')) {
                return false;
            }
        }
    }
    return stk.isEmpty();
}

// ===== Application 3: Infix to Postfix Conversion =====
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

string infixToPostfix(string infix) {
    Stack<char> s;
    string postfix = "";

    for (char c : infix) {
        if (isspace(static_cast<unsigned char>(c))) continue;
        if (isalnum(c)) {
            postfix += c;
        } else if (c == '(') {
            s.push(c);
        } else if (c == ')') {
            while (!s.isEmpty() && s.top() != '(') {
                postfix += s.pop();
            }
            if (s.isEmpty()) {
                cout << "Mismatched parentheses!" << endl;
                return "";
            }
            s.pop();  // Remove '('
        } else {  // operator
            while (!s.isEmpty() && precedence(s.top()) >= precedence(c)) {
                postfix += s.pop();
            }
            s.push(c);
        }
    }
    while (!s.isEmpty()) {
        if (s.top() == '(') {
            cout << "Mismatched parentheses!" << endl;
            return "";
        }
        postfix += s.pop();
    }
    return postfix;
}

int main() {
    cout << "========================================" << endl;
    cout << "  Stack Demo" << endl;
    cout << "========================================" << endl;

    // Basic operations
    cout << "\n--- Basic Stack Operations ---" << endl;
    Stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);
    cout << "Push 10, 20, 30" << endl;
    cout << "Top: " << s.top() << endl;
    cout << "Pop: " << s.pop() << endl;
    cout << "Pop: " << s.pop() << endl;
    cout << "Top: " << s.top() << endl;

    // Postfix evaluation
    cout << "\n--- Postfix Expression Evaluation ---" << endl;
    string expr1 = "62+31-4*7+*";  // (6+2)*((3-1)*4+7) = 8*(2*4+7) = 8*15 = 120
    cout << "Expression: " << expr1 << endl;
    cout << "  6 2 + = 8" << endl;
    cout << "  3 1 - = 2" << endl;
    cout << "  2 4 * = 8" << endl;
    cout << "  8 7 + = 15" << endl;
    cout << "  8 15 * = 120" << endl;
    cout << "Result: " << evaluatePostfix(expr1) << endl;

    string expr2 = "53+82-*";  // (5+3)*(8-2) = 8*6 = 48
    cout << "\nExpression: " << expr2 << endl;
    cout << "Result: " << evaluatePostfix(expr2) << endl;

    // Balanced symbols
    cout << "\n--- Balanced Symbols ---" << endl;
    string tests[] = {"(())", "([]){}", "[()]", "(()", "([)]", "{[()]}"};
    for (string t : tests) {
        cout << "\"" << t << "\" -> " << (isBalanced(t) ? "Balanced" : "NOT balanced") << endl;
    }

    // Infix to Postfix
    cout << "\n--- Infix to Postfix Conversion ---" << endl;
    string infix = "(A+B)*(C-D)";
    cout << "Infix:   " << infix << endl;
    cout << "Postfix: " << infixToPostfix(infix) << endl;

    string infix2 = "A+B*C-D/E";
    cout << "\nInfix:   " << infix2 << endl;
    cout << "Postfix: " << infixToPostfix(infix2) << endl;

    cout << "\n========================================" << endl;
    cout << "  Stack Properties" << endl;
    cout << "========================================" << endl;
    cout << "LIFO: Last-In-First-Out" << endl;
    cout << "Push/Pop/Top: O(1)" << endl;
    cout << "Applications: function calls, backtracking, expression eval" << endl;

    return 0;
}
