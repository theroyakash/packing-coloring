#include <string.h>

#include <climits>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#include <random>

using namespace std;

void fileIO() {
    freopen("input.txt", "w", stdout);
}

int main() {
    fileIO();
    srand(time(0));

    int cases = 10;

    int probability_lower_bound = 5000;
    int probability_upper_bound = 10000;

    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());

    std::uniform_int_distribution<int> distribution(probability_lower_bound, probability_upper_bound);

    cout << cases << endl;

    while (cases--) {
        int nodes = distribution(generator);
        std::cout << nodes << "\n";
    }

    return 0;
}