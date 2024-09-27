// Team Members: Youssif, Adham, Philo, Sandra

// Task by: Youssef  

#include <iostream>
using namespace std;

int returnAsInt(char x) {
    return (x - 'a');
}

char returnAsChar(int x) {
    return char(x + 'a');
}

bool isUpper(char x) {
    return x >= 'A' && x <= 'Z';
}

bool isAlphabet(char x) {
    return (x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z');
}

int stringLength(const char str[]) {
    int i = 0;
    while (str[i] != '\0') { // loop until null terminator
        i++;
    }
    return i;
}

bool isCoprime(int a, int m = 26) {
    if (m == 0) {
        return a == 1;
    }
    return isCoprime(m, a % m);
}

char* decipherLogic(const char cipher[], int array_length, int inverse_a, int b) {
    char* y = new char[array_length + 1];
    for (int i = 0; i < array_length; ++i) {
        char c = cipher[i];

        if (!isAlphabet(c)) {
            y[i] = c;
        } else {

            if (isUpper(c)) {
                c += 32; // to lowercase
            }

            int charToInt = returnAsInt(c);
            int inverse = (inverse_a * (charToInt - b)) % 26;
            if (inverse < 0) {inverse += 26;}
            y[i] = returnAsChar(inverse);
        }

    }
    y[array_length] = '\0';
    return y;
}

int modInverse(int b, int a = 26) {
    int t1 = 0, t2 = 1;
    int original_a = a;

    while (b > 0) {
        int q = a/b;
        int r = a % b;
        int t = t1 - t2 * q;
        a = b;
        b = r;
        t1 = t2;
        t2 = t;
    }

    if (t1 < 0) { // if result is negative
        t1 += original_a;
    }

    return t1;
}

void affine_decipher(char cipher[], int a, int b) {
    int cipherLength = stringLength(cipher);
    int inverse_a = modInverse(a);

    char* deciphered = decipherLogic(cipher, cipherLength, inverse_a, b);

    cout << "Deciphered message: " << deciphered << endl;
    delete[] deciphered;
}

int main() {
    //char cipher[] = {"OFHSBJFHM HXZPU"};
    char cipher[250];
    int a = 0, b = 0;
    char choice;

    do {
        cout << "Enter the ciphered message:";
        cin.getline(cipher, 250);

        cout << "Enter the ciphering keys\n";
        do {
            cout << "Enter the a:";
            if (cin >> a && isCoprime(a)) break;
            cout << "Error: make sure your input is an integer and is coprime with 26\n";
            cin.clear();
            cin.ignore(1000, '\n');
        } while (true);

        do {
            cout << "Enter the b:";
            if (cin >> b) break;
            cout << "Error: make sure your input is an integer";
            cin.clear();
            cin.ignore(1000, '\n');
        } while (true);

        //cin.ignore();

        affine_decipher(cipher, a, b);

        cout << "Would you like to decipher another message (y/n):";
        cin >> choice;
        cin.ignore();

    } while (choice == 'y');

    return 0;
}