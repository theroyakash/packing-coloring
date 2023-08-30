#include <iostream>
#include <math.h>
using namespace std;

void fileIO() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

int main() {
    fileIO();
    unsigned long long int id = 1;
    unsigned long long int i = 0;

    unsigned long long int l; cin >> l;
    
    cout << l << endl;

    while(l--) {
        unsigned long long int to = pow(2, i);
        i++;
        for (unsigned long long int i = 0; i < to; i++) {
            cout << id << " ";
            id++;
        }

        cout << endl;
    }

    cout << id - 1;
}
