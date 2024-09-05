#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <vector>
using namespace std;

namespace cop4530
{
    template <typename T>
    class Stack
    {
    public:
        Stack();                                            // default constructor
        ~Stack();                                           // destructor
        bool empty() const;                                 // checks if stack is empty
        void clear();                                       // deletes all elements from stack
        void push(const T &x);                              //  adds to stack - copy version
        void push(T &&x);                                   // adds to stack - move version
        void pop();                                         // removes recently added element from stack
        T &top();                                           // returns reference to recently added element from stack
        const T &top() const;                               // accessor that returns recently added element from stack
        int size() const;                                   // returns number of elements stored in stack
        void print(std::ostream &os, char ofc = ' ') const; // print elements of stack

    private:
        vector<T> elements;
    };
}

#include "stack.hpp"

#endif