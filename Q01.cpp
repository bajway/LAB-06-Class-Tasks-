/*Implement and insert the values “BORROWROB” in the stack and identify if it’s a palindrome
or not. Use the push and pop functions to accomplish this (Note: Use Arrays to accomplish this)*/

#include <iostream>
#include <string>
using namespace std;

class Stack
{
private:
    char *arr;
    int top;
    int capacity;

public:
    Stack(int size)
    {
        capacity = size;
        arr = new char[capacity];
        top = -1;
    }

    ~Stack()
    {
        delete[] arr;
    }

    void push(char value)
    {
        if (isFull())
        {
            cout << "Stack Overflow!" << value << "'" << endl;
            return;
        }
        arr[++top] = value;
        cout << "Pushed: " << value << endl;
    }

    char pop()
    {
        if (isEmpty())
        {
            cout << "Stack Underflow! Cannot pop" << endl;
            return '\0';
        }
        char value = arr[top--];
        return value;
    }

    char peek()
    {
        if (isEmpty())
        {
            cout << "Stack is empty!" << endl;
            return '\0';
        }
        return arr[top];
    }

    bool isEmpty()
    {
        return top == -1;
    }

    bool isFull()
    {
        return top == capacity - 1;
    }

    int size()
    {
        return top + 1;
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "Stack is empty!" << endl;
            return;
        }
        cout << "Stack contents (top to bottom): ";
        for (int i = top; i >= 0; i--)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

bool isPalindrome(string str)
{
    int length = str.length();
    Stack stack(length);

    cout << "\n=== Pushing characters to stack ===" << endl;
    for (int i = 0; i < length; i++)
    {
        stack.push(str[i]);
    }

    cout << "\n";
    stack.display();

    cout << "\n=== Popping characters and comparing ===" << endl;
    string reversed = "";
    for (int i = 0; i < length; i++)
    {
        char poppedChar = stack.pop();
        cout << "Popped: " << poppedChar << " | Comparing with: " << str[i] << endl;
        reversed += poppedChar;
    }

    cout << "\nOriginal String: " << str << endl;
    cout << "Reversed String: " << reversed << endl;

    return str == reversed;
}

int main()
{
    string input = "BORROWROB";

    cout << "CHECK PALINDROME USING STACK" << endl;

    cout << "ENTER A STRING " << input << endl;

    bool result = isPalindrome(input);
    if (result)
    {
        cout << "RESULT: \"" << input << "\" IS a PALINDROME! ✓" << endl;
    }
    else
    {
        cout << "RESULT: \"" << input << "\" IS NOT a PALINDROME! ✗" << endl;
    }

    return 0;
}