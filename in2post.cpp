// ********************************************************************
// * Name: Julissa Su                                                 *
// * Date: June 28, 2024                                              *
// * Class: COP4530                                                   *
// * Assignment #4 - List, Stacks, Queues                             *
// * References: None                                                 *
// ********************************************************************

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "stack.h"

using namespace std;
using namespace cop4530;

// function prototypes
void infixToPostfix(const vector<string> &input, vector<string> &output);
void evaluatePostfix(const vector<string> &postfix, string &result);
bool isValidOperand(const string &input);
bool isValidOperator(const string &input);
int precedence(const string &input);

int main()
{
    // declare variables
    vector<string> input;
    vector<string> postfix;
    string expression;

    while (true)
    {
        input.clear();
        postfix.clear();

        // read expression from input
        cout << "Enter an expression (or 'end' to quit): " << endl;
        getline(cin, expression);

        // check for termination condition
        if (expression == "end" || expression == "END" || expression == "End")
            break;

        // display infix notation
        cout << "The Infix Notation is: " << expression << endl;

        // split exprssion into tokens and store in input vector
        stringstream ss(expression);
        while (ss >> expression)
        {
            input.push_back(expression);
        }

        // convert infix to postfix and display postfix notation
        cout << "The Postfix Notation is: ";
        infixToPostfix(input, postfix);
        for (const auto &token : postfix)
        {
            cout << token << " ";
        }
        cout << endl;

        // evaluate postfix expression and display the result
        string result;
        evaluatePostfix(postfix, result);
        cout << "Result is: " << result << endl;
    }

    return 0;
}

// function to convert infix expression to postfix notation
void infixToPostfix(const vector<string> &input, vector<string> &output)
{
    Stack<string> stack;
    string last;
    int flag = 0;

    // iterate through each token
    for (const auto &token : input)
    {
        if (isValidOperand(token))
        {
            output.push_back(token); // operand, add to output
        }
        else if (token == "(")
        {
            stack.push(token); // left parenthesis, push to stack
        }
        else if (isValidOperator(token))
        {
            // operator, handle precedence and push to output
            while (!stack.empty() && stack.top() != "(" && precedence(stack.top()) >= precedence(token))
            {
                output.push_back(stack.top());
                stack.pop();
            }
            stack.push(token);
        }
        else if (token == ")")
        {
            if (isValidOperator(last))
            {
                cout << "ERROR" << endl; // error if previous token was operator
                return;
            }
            else
            {
                // right parenthesis, pop from stack to output until left parenthesis
                do
                {
                    output.push_back(stack.top());
                    stack.pop();
                } while (stack.top() != "(");

                if (stack.top() == "(")
                {
                    flag = 1; // flag for matched parenthesis
                }
                stack.pop(); // pop left parenthesis

                if (stack.empty() && flag == 0)
                {
                    cout << "ERROR" << endl; // error if no matching left parenthesis
                    return;
                }
            }
        }
        else
        {
            cout << "ERROR" << endl; // invalid token
            return;
        }
        last = token; // update last token processed
    }

    // pop remaining operators from stack to output
    do
    {
        output.push_back(stack.top());
        stack.pop();
    } while (!stack.empty());
}

// function to evaluate postfix expression
void evaluatePostfix(const vector<string> &postfix, string &result)
{
    Stack<string> stack;

    // iterate through each token
    for (const auto &token : postfix)
    {
        if (isValidOperand(token))
        {
            stack.push(token); // operand, push to stack
        }
        else if (isValidOperator(token))
        {
            // ensure there are enough operands in the stack
            if (stack.size() < 2)
            {
                result = "Error - Too few operands";
                return;
            }

            // pop the top two operands and convert to float
            float op1 = stof(stack.top());
            stack.pop();
            float op2 = stof(stack.top());
            stack.pop();

            // perform the operation
            if (token == "*")
                stack.push(to_string(op2 * op1));
            else if (token == "/")
                stack.push(to_string(op2 / op1));
            else if (token == "+")
                stack.push(to_string(op2 + op1));
            else if (token == "-")
                stack.push(to_string(op2 - op1));
        }
    }

    if (stack.size() != 1)
    {
        result = "Error - Invalid postfix expression"; // more than one operand left
    }
    else
    {
        result = stack.top(); // store the final result
    }
}

// function to check if input is a valid operand
bool isValidOperand(const string &input)
{
    for (char i : input)
    {
        if (isalnum(i))
        {
            return true;
        }
    }
    return false;
}

// function to check if input is a valid operator
bool isValidOperator(const string &input)
{
    if (input == "*" || input == "/" || input == "+" || input == "-" || input == "_")
    {
        return true;
    }
    return false;
}

// function to determine the precedence of operators
int precedence(const string &input)
{
    if (input == "(" || input == ")")
    {
        return 2;
    }
    else if (input == "*" || input == "/")
    {
        return 1;
    }
    else if (input == "+" || input == "-")
    {
        return 0;
    }
    else
    {
        return -1; // invalid operator
    }
}
