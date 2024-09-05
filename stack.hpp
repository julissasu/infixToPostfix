#include "stack.h"
namespace cop4530
{
    template <typename T>
    Stack<T>::Stack() // default constructor
    {
    }

    template <typename T>
    Stack<T>::~Stack() // destructor
    {
        clear();
    }

    template <typename T>
    bool Stack<T>::empty() const // check if stack is empty
    {
        return elements.empty();
    }

    template <typename T>
    void Stack<T>::clear() // clear all elements in the stack
    {
        elements.clear();
    }

    template <typename T>
    void Stack<T>::push(const T &x) // push an element onto the stack (copy version)
    {
        elements.push_back(x);
    }

    template <typename T>
    void Stack<T>::push(T &&x)
    {
        elements.push_back(std::move(x)); // push an element onto the stack (move version)
    }

    template <typename T>
    void Stack<T>::pop() // remove top element from stack
    {
        if (!empty())
            elements.pop_back();
    }

    template <typename T>
    T &Stack<T>::top() // access the top element of the stack
    {
        if (!empty())
            return elements.back();
        else
            throw std::underflow_error("Stack is empty"); // throw exception if stack is empty
    }

    template <typename T>
    const T &Stack<T>::top() const // access top element of the stack (const version)
    {
        if (!empty())
            return elements.back();
        else
            throw std::underflow_error("Stack is empty"); // throw exception if stack is empty
    }

    template <typename T>
    int Stack<T>::size() const // return number of elements in the stack
    {
        return elements.size();
    }

    template <typename T>
    void Stack<T>::print(std::ostream &os, char ofc) const // print elements of the stack from top to bottom
    {
        for (auto it = elements.rbegin(); it != elements.rend(); ++it)
            os << *it << ofc;
    }

}
