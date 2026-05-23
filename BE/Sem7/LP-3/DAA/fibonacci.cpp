/*
Assignment 1 (DAA)
Write a non-recursive and recursive program to calculate Fibonacci
numbers and analyze their time and space complexity.
*/

#include <iostream>
using namespace std;

//------------------------------------------------------------------------------
// Recursive Fibonacci
// Time Complexity: O(2^n)
// Space Complexity: O(n) due to recursion stack
//------------------------------------------------------------------------------
int fibonacciRecursive(int n)
{
    if (n <= 1)
    {
        return n;
    }

    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

//------------------------------------------------------------------------------
// Iterative Fibonacci
// Time Complexity: O(n)
// Space Complexity: O(1)
//------------------------------------------------------------------------------
int fibonacciIterative(int n)
{
    if (n <= 1)
    {
        return n;
    }

    int a = 0, b = 1, fib = 0;

    for (int i = 2; i <= n; ++i)
    {
        fib = a + b;
        a = b;
        b = fib;
    }

    return fib;
}

//------------------------------------------------------------------------------
// Main Function
//------------------------------------------------------------------------------
int main()
{
    int choice = 0;
    int n;
    int ans;

    while(choice != 3)
    {
        cout<<"\nPress \n1. Recursive Fibonacci \n2. Iterative Fibonacci \n3. End \nEnter your choice : ";
        cin>>choice;
        cout<<endl;

        switch (choice)
        {
            case 1:
                cout<<"Enter n = ";
                cin>>n;
                ans = fibonacciRecursive(n);
                cout<<n<<"th Fibonacci Number (Recursive) = "<<ans<<endl;
                cout<<"Time complexity = O(2^n)"<<endl;
                cout<<"Space complexity = O(n)"<<endl;
                break;
            
            case 2:
                cout<<"Enter n = ";
                cin>>n;
                ans = fibonacciIterative(n);
                cout<<n<<"th Fibonacci Number (Iterative) = "<<ans<<endl;
                cout<<"Time complexity = O(n)"<<endl;
                cout<<"Space complexity = O(1)"<<endl;
                break;

            case 3:
                cout<<"End :)"<<endl;
                break;
            
            default:
                cout<<"Invalid Input"<<endl;
                break;
        }
    }

    return 0;
}

