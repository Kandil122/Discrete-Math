// Team Members: Youssif, Adham, Philo, Sandra

// Task by: sandra  


#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
using namespace std;

// Global variables to keep track of the number of premises and the list of variables used
int no_of_premises = 0;
vector<char> variables;

// Function to evaluate logical implication(conditional)
bool implies(bool A, bool B) {
    return !A || B;
}

// Function to extract variables from the argument and count the number of premises
vector<char> extractVariables(const string& argument) {
    for (char ch : argument) {
        if (isalpha(ch) && find(variables.begin(), variables.end(), ch) == variables.end()) {
            variables.push_back(ch); // Add variable if it's not already in the list
        }
        else if (ch == ';'){
            no_of_premises++; // Count premises based on ';'
        }
    }

    return variables;
}

// Function to print the table headings for the truth table
void print_headings(){
    for (char var : variables) {
        cout << var << "\t"; // Print variable names
    }
    for (int i=1; i<=no_of_premises; i++){
        cout << "P" << i << "\t"; // Print premise labels
    }
    cout << "Conc" << endl; // Print conclusion label
}

// Function to solve logical operations within a sub-expression
char operationSolver(const string& argument, const vector<bool>& values) {
    char op = '>';
    bool i1 = false;
    bool i2 = false;
    char operations[2] = {'/', '\\'};
    int not_pos = argument.find('~');
    bool containsNot = (not_pos != -1);

    if(containsNot){
        bool isAlphaAt2 = isalpha(argument[2]);
        if(isAlphaAt2){
            for (int i = 0; i < variables.size(); i++) {
                if (argument[2] == variables[i]) {
                    i1 = values[i];
                    return ((!i1) ? '1' : '0'); // Negation
                }
            }
        }
        else{
            i1 = (argument[2] == '1'); // Convert to boolean
            return ((!i1) ? '1' : '0');
        }
    }
    else{
        bool isAlphaAt1 = isalpha(argument[1]);
        bool isAlphaAtLast = isalpha(argument[argument.size()-2]);
        if(isAlphaAt1){
            for (int i = 0; i < variables.size(); i++) {
                if (argument[1] == variables[i]) {
                    i1 = values[i];
                }
            }
        }
        else{
            i1 = (argument[1] == '1'); // Convert to boolean
        }

        if(isAlphaAtLast){
            for (int i = 0; i < variables.size(); i++) {
                if (argument[argument.size()-2] == variables[i]) {
                    i2 = values[i];
                }
            }
        }
        else{
            i2 = (argument[argument.size()-2] == '1'); // Convert to boolean
        }

        for (int i = 0; i < 2; i++) {
            if (operations[i] == argument[3]) {
                op = operations[i];
                break;
            }
        }
        if (op == '/')
            return ((i1 && i2) ? '1' : '0'); // AND operation
        else if (op == '\\')
            return ((i1 || i2) ? '1' : '0'); // OR operation
        else
            return (implies(i1, i2) ? '1' : '0'); // Implication operation
    }
    return 0;
}

// Function to evaluate the logical expression with the given truth values
vector<bool> evaluateExpression(const string& argument, const vector<bool>& values) {
    vector<bool> result;

    // Create a modifiable copy of the argument
    string un_extracted_string = argument;
    for (int i=0; i<no_of_premises+1; i++) {
        while (un_extracted_string[0] != '1' && un_extracted_string[0] != '0') {
            int closing_bracket_pos = un_extracted_string.find_first_of(')');
            int opening_bracket_pos = un_extracted_string.rfind('(', closing_bracket_pos);
            int len = closing_bracket_pos - opening_bracket_pos + 1;

            string extracted_string = un_extracted_string.substr(opening_bracket_pos, len);

            char unfinished_result = operationSolver(extracted_string, values);

            // Convert the result to a string
            string result_string(1, unfinished_result);

            // Replace the extracted substring with the result string
            un_extracted_string.replace(opening_bracket_pos, len, result_string);
        }

        if (un_extracted_string[0] == '1') {
            result.push_back(true);
        } else {
            result.push_back(false);
        }

        un_extracted_string.erase(0,2); // Remove the processed part of the string
    }

    return result;
}

// Function to print the truth table and check for satisfiability and validity
void print_truth_table(const string& argument) {
    int numRows = pow(2, variables.size());
    bool isSatisfiable = false;
    bool isValid = true; // Start assuming the argument is valid

    for (int i = 0; i < numRows; ++i) {
        vector<bool> values(variables.size());

        for (int j = 0; j < variables.size(); ++j) {
            values[j] = ((i >> (variables.size() - 1 - j)) & 1);
            cout << values[j] << "\t";
        }

        vector<bool> result = evaluateExpression(argument, values);

        for (int j = 0; j < result.size(); ++j) {
            cout << result[j] << "\t";
        }

        // Check if all values in result are true
        bool allTrue = all_of(result.begin(), result.end(), [](bool v) { return v; });
        if (allTrue) {
            isSatisfiable = true;
        }

        // Check if the last value is false but all previous ones are true
        bool trueP = all_of(result.begin(), result.end() - 1, [](bool val) {
            return val == true;
        });

        if (trueP && !result.back()) {
            isValid = false; // Once false, it should remain false
        } else if (allTrue && isValid) {
            isValid = true; // Only set to true if it hasn't been set to false yet
        }

        result.clear();
        result.shrink_to_fit();
        cout << endl;
    }

    // isSatisfiable remains true if any row had all true values
    if (isSatisfiable) {
        cout << "The argument is satisfiable." << endl;
    } else {
        cout << "The argument is not satisfiable." << endl;
    }

    // Output whether the argument is valid
    if (isValid) {
        cout << "The argument is valid." << endl;
    } else {
        cout << "The argument is falsifiable." << endl;
    }
}

// Main function to run the program
int main(){
    string argument;
    cout<<"1-Open a big bracket for the whole expression and for each premise and conclusion.                                                           2-Start with the premises and add a semicolon (;) at the end of each one.                                                                  3-Write the conclusion at the end of the expression.                  4-Rewrite everything in lowercase and in plain English words.             : example :((k \/ m) > (~a));(a \/ m);(a \/ (~k)) "<<endl;
    cout << "Enter an argument"<<endl;
    getline(cin, argument);

    variables = extractVariables(argument); // Extract variables from input
    if(find(variables.begin(), variables.end(), ';') == variables.end()-1){
        cout<<"no conclusion entered,please enter the conclusion"<<endl;
                getline(cin, argument);
        variables = extractVariables(argument);
    }
        if(no_of_premises==0){
        cout<<"no premises entered,please enter at least one premise"<<endl;
        getline(cin, argument);
        variables = extractVariables(argument);
    }
    print_headings(); // Print table headings
    print_truth_table(argument); // Evaluate and print the truth table
}