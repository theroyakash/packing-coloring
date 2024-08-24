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


    std::vector<int> cases = {};

    for (int i = 1; i < 9; i++) {
        cases.push_back(i * 1000);
    }

    int trials = 20;

    std::cout << trials << " " << trials*cases.size() << "\n";
    for (auto _case : cases) {
        for (int i = 0; i < trials; i++) {
            std::cout << _case << "\n";
        }
    }

    return 0;
}