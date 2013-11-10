#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int main() {
    unsigned short n;
    cout << "Please input a non negative number and press enter: ";
    cin >> n;

    unsigned long long a = 0;
    unsigned long long b = 1;
    for(unsigned short i=0; i<n; i++, b+=a, a=b-a){ // here we save one variable and one assignment
        cout << a << " "; 
    }
    cout << endl;
    return 0;
}
