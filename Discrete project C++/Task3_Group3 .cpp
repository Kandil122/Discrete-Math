// Team Members: Youssif, Adham, Philo, Sandra

// Task by: philo  

#include <iostream>
using namespace std;

const int alphaCount = 21;
const char italianAlphabet[alphaCount] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'L',
        'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'Z'
};

bool isCoprime(int a, int m) {
    while (m != 0) {
        int temp = m;
        m = a % m;
        a = temp;
    }
    return a == 1;
}

int charToNum(char c) {
    for (int i = 0; i < alphaCount; i++) {
        if (c == italianAlphabet[i])
            return i;
    }
    return 0;
}

char numToChar(int n) {
    if (n >= 0 && n < alphaCount) {
        return italianAlphabet[n];
    }
    return 0;
}

string cipher(string plainMessage, int a, int b) {
    string cipheredMessage;
    cipheredMessage.reserve(plainMessage.length());
    for (int i = 0; i < plainMessage.length(); i++) {
        if (isalpha(plainMessage[i])) {
            int x = charToNum(toupper(plainMessage[i]));
            int y = (a * x + b) % alphaCount;
            cipheredMessage += numToChar(y);
        } else {
            cipheredMessage += plainMessage[i];
        }
    }
    return cipheredMessage;
}

int main() {
    char continueInput = 'y';

    while (continueInput == 'y' || continueInput == 'Y') {
        string plainMessage;
        int a, b;

        cout << "Enter the message to be ciphered (in Italian): ";
        getline(cin, plainMessage);

        do {
            cout << "Enter the ciphering keys (a then b): ";
            cin >> a >> b;

            if (a < 1 || a > alphaCount) {
                cout << "Error: 'a' must be in the range 1 to " << alphaCount << "." << endl;
            } else if (b < 0 || b > alphaCount) {
                cout << "Error: 'b' must be in the range 0 to " << alphaCount << "." << endl;
            } else if (!isCoprime(a, alphaCount)) {
                cout << "Error: 'a' must be coprime with the alphabet size (" << alphaCount << ")." << endl;
            }
        } while (a < 1 || a > alphaCount || b < 0 || b > alphaCount || !isCoprime(a, alphaCount));

        cout << "Ciphered message: " << cipher(plainMessage, a, b) << endl;

        cout << "Do you want to enter another message? (y/n): ";
        cin >> continueInput;
        cin.ignore();
    }

    cout << "terminating the program..." << endl;
    return 0;
}