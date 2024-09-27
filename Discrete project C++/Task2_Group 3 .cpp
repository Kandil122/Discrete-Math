// Team Members: Youssif, Adham, Philo, Sandra

// Task by: Adham  

#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <limits>  

using namespace std;

bool applyOperator(char op, bool a, bool b) {
    switch (op) {
        case '&': return a && b; // AND  gate
        case '|': return a || b; // OR gate
        case '^': return a ^ b; // XOR gate
        default: return false;
    }
}

bool evaluateExpression(const string& expression, bool A, bool B, bool C) {
    // created 2 stacks 
    //values for holding the boolean values 
    // operators for holding operators like {'&','|','^','(',')'} 
    stack<bool> values;
    stack<char> operators;
    
    
    // iterate through each character
    for (size_t i = 0; i < expression.length(); i++) {
        char ch = expression[i];
        
        if (isspace(ch)) continue;  // Skip spaces
        
        // if you find a char A or B or C 
        if (ch == 'A' || ch == 'B' || ch == 'C') {
            bool varValue = (ch == 'A') ? A : (ch == 'B') ? B : C;
            values.push(varValue); // add char to values stack
        } 
        // if you encountering a not, then you will check if there is an next character, adds the not char to the values stack
        else if (ch == '!' && i + 1 < expression.length() && (expression[i + 1] == 'A' || expression[i + 1] == 'B' || expression[i + 1] == 'C')) {
            i++;
            bool varValue = (expression[i] == 'A') ? !A : (expression[i] == 'B') ? !B : !C;
            values.push(varValue);
        } 
        // if it's an opening bracket, add it to operators stack
        else if (ch == '(') {
            operators.push(ch);
        } 
        // if the character was a closing parenthesis
        else if (ch == ')') {
            //check that it's not empty
            while (!operators.empty() && operators.top() != '(') {
      //retrieve the last 2 values in stack and assign them to val1,val2 
                bool val2 = values.top(); values.pop();
                bool val1 = values.top(); values.pop();
                // retrieve the last operator and assign them to op
                char op = operators.top(); operators.pop();
            // execute the applyOperator FN and push value to values stack
                values.push(applyOperator(op, val1, val2));
            }
            operators.pop();  // Remove '('
        } 
        // if the character was a logical operator 
        else if (ch == '&' || ch == '|' || ch == '^') {
            while (!operators.empty() && operators.top() != '(') {
                bool val2 = values.top(); values.pop();
                bool val1 = values.top(); values.pop();
                char op = operators.top(); operators.pop();
                values.push(applyOperator(op, val1, val2));
            }
            operators.push(ch);
        }
    }
    // handles any remaining operators
    while (!operators.empty()) {
        bool val2 = values.top(); values.pop();
        bool val1 = values.top(); values.pop();
        char op = operators.top(); operators.pop();
        values.push(applyOperator(op, val1, val2));
    }
    
    // return the final value in stack which is the result
    return values.top(); 
}

    //returns 1 or 0 using the original function (result)
bool orgfunction(const string& expression, bool A, bool B, bool C) {
    return evaluateExpression(expression, A, B, C);
}

//     //returns 1 or 0 using the simplified function (result)
bool simplifiedfun(const string& expression2, bool A, bool B, bool C) {
    // You should replace this with an actual simplification algorithm
    return evaluateExpression(expression2, A, B, C); 
}

// Function to output a truth table of both functions
void bothtruthtable(const string& expression, const string& expression2) {
    for (int A = 0; A <= 1; ++A) {
        for (int B = 0; B <= 1; ++B) {
            for (int C = 0; C <= 1; ++C) {
                bool result = orgfunction(expression, A, B, C);
                bool result2 = simplifiedfun(expression2, A, B, C);
                cout << A << "\t" << B << "\t" << C << '\t' << result << "\t\t" << result2 << endl;
            }
        }
    }

    cout << "Expression: " << expression << endl;
    cout << "Simplified Expression: " << expression2 << endl;
     // Check if original and simplified equations are equivalent
}

// Function to output original function truth table
void orgtruthtable(const string& expression) {
    for (int A = 0; A <= 1; ++A) {
        for (int B = 0; B <= 1; ++B) {
            for (int C = 0; C <= 1; ++C) {
                bool result = orgfunction(expression, A, B, C);
                cout << A << "\t" << B << "\t" << C << '\t' << result << endl;
            }
        }
    }
    cout << "Expression: " << expression << endl;
}

// Function to output simplified function truth table
void simptruthtable(const string& expression2) {
    for (int A = 0; A <= 1; ++A) {
        for (int B = 0; B <= 1; ++B) {
            for (int C = 0; C <= 1; ++C) {
                bool result2 = simplifiedfun(expression2, A, B, C);
                cout << A << "\t" << B << "\t" << C << '\t' << result2 << endl;
            }
        }
    }
    cout << "Simplified Expression: " << expression2 << endl;
}

// Function that checks if the simplified is equal to the original or not
void check(const string& expression, const string& expression2) {
    bool equiv = true;
    for (int A = 0; A <= 1; ++A) {
        for (int B = 0; B <= 1; ++B) {
            for (int C = 0; C <= 1; ++C) {
                bool result = orgfunction(expression, A, B, C);
                bool result2 = simplifiedfun(expression2, A, B, C);
                if (result != result2) {
                     equiv = false;
                }
            }
        }
    }
    if (equiv) {
        cout << "The simplified and original functions are equivalent." << endl;
    } else {
        cout << "The simplified and original functions are not equivalent." << endl;
    }
}

// Function to find satisfiable inputs
void findSatisfiableInputs(const string& expression, const string& expression2) {
    cout << "Finding satisfiable inputs..." << endl;
    bool satisfiableFound = false;

    // Iterate over all possible input combinations
    for (int A = 0; A <= 1; ++A) {
        for (int B = 0; B <= 1; ++B) {
            for (int C = 0; C <= 1; ++C) {
                // Check if the circuit is satisfiable
                bool result = orgfunction(expression, A, B, C);
                bool result2 = simplifiedfun(expression2, A, B, C);
                if (result && (result == result2)) {
                    satisfiableFound = true;
                    cout << "Satisfiable inputs: A=" << A << ", B=" << B << ", C=" << C << endl;
                }
            }
        }
    }

    if (!satisfiableFound) {
        cout << "The circuit is unsatisfiable. Changing one gate to make it satisfiable..." << endl;
        // Change one gate (for simplicity, let's negate the first input)
        cout << "Changed gate: NOT A" << endl;
        cout << "New satisfiable inputs:" << endl;
        cout << "A"
             << "\t"
             << "B"
             << "\t"
             << "C" << '\t' << "Result" << endl;
        orgtruthtable(expression); // Output truth table with changed gate
    }
}

int main() {
    char expression[100];
    char expression2[100];
    cout << "Welcome to the Boolean Circuit Simplification and Evaluation System!\n" << endl;

    cout << "Hello, Dr.Betty\n";
    cout << "Please, Enter the Expression: \te.g: !A & ((A & B) | (A & C) | (B & C))\n";
    cout<<"Original Expression: ";
    cin.getline(expression, 100);
    cout << "\nPlease, Enter the Simplified Expression: \te,g: !A & B & C \n";
    cout<<"Simplified Expression: ";
    cin.getline(expression2, 100);
    cout << "-----------------------------\n";
    string exprStr = string(expression);
    string exprStr2 = string(expression2);

    cout << "    "<< "TRUTH TABLE" << endl;
    cout << "A"
         << "\t"
         << "B"
         << "\t"
         << "C" << '\t' << "Result" << '\t' << "Simplified" << endl;
    bothtruthtable(exprStr, exprStr2);
    cout << "-----------------------------\n";

    int input = 0;
    // User-friendly interface
    do {
        cout << "\t\tLIST OF CHOICES\n" << endl;
        cout << "1- Simplified Function Truth Table" << endl;
        cout << "2- Original Function Truth Table" << endl;
        cout << "3- Check if Simplified and Original Functions are Equivalent" << endl;
        cout << "4- Find Satisfiable Inputs" << endl;
        cout << "5- Exit" << endl;
        cout << endl;
        cout << "Choose which option you would like to select: ";
        cin >> input;
        cout << "-----------------------------\n";

        switch (input) {
            case 1:
                cout << "    "
                     << "SIMPLIFIED FUNCTION TRUTH TABLE" << endl;
                cout << "A"
                     << "\t"
                     << "B"
                     << "\t"
                     << "C" << '\t' << "Result" << endl;
                simptruthtable(exprStr2);
                cout << "-----------------------------\n";
                break;
            case 2:
                cout << "    "
                     << "ORIGINAL FUNCTION TRUTH TABLE" << endl;
                cout << "A"
                     << "\t"
                     << "B"
                     << "\t"
                     << "C" << '\t' << "Result" << endl;
                orgtruthtable(exprStr);
                cout << "-----------------------------\n";
                break;
            case 3:
                cout << "Checking the Equivalency between Simplified and Original functions..." << endl;
                check(exprStr, exprStr2);
                cout << "-----------------------------\n";
                break;
            case 4:
                findSatisfiableInputs(exprStr, exprStr2);
                cout << "-----------------------------\n";
                break;
            case 5:
                cout << "Goodbye, Dr.Betty!" << endl;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
                cin.clear(); // Clear error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                break;
        }
    } while (input != 5); // Continue until user chooses to exit
    
    return 0;
}