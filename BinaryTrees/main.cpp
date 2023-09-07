/**
****************************************************************
* @file:	main.cpp
* @author:	@theroyakash
* @contact:	hey@theroyakash.com
* @date:	30/08/2023 21:12:17 Wednesday
* @brief:	Tree Generation and transformation into a graph object
****************************************************************
**/

#include <chrono>
#include <iostream>
#include <queue>
#include <set>
#include <string.h>
#include <vector>

#include "color.h"
#include "graph.h"
#include "tree.h"

using namespace std;

void fileIO() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

int main() {

    fileIO();

    vector<int> v;
    int levels;
    cin >> levels;

    int maxNodeID;
    cin >> maxNodeID;

    levels++;

    while (levels--) {
        char a[1250000];
        cin.getline(a, 1250000);

        // String TOKENIZER to get all the numbers and convert them into integers
        // then push it into the vector
        char *ans = strtok(a, " ");
        while (ans != NULL) {
            v.push_back(stoi(ans));
            ans = strtok(NULL, " ");
        }
    }

    Tree* tree = TreeServices::createTreeFromVector(v);
    Graph g(maxNodeID);

    GraphServices::createGraphWhileLevelOrderTraversal(tree, g);

    auto procedure_start = std::chrono::high_resolution_clock::now();
    // given the tree structure do approximatePackingColor on graph g.
    g.approximatePackingColor(tree);
    auto procedure_end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<float> duration = procedure_end - procedure_start;
    cout << "[TOTAL TIME]: " << duration.count() << " seconds" << endl;

    vector<Color> colors = g.colors;

    int maxColor = -1;

    for (int i = 0; i < colors.size(); i++) {
        // if ((i + 1) % 3 == 0) cout << endl;
        maxColor = std::max(colors[i].colorID, maxColor);
        // cout << "[NODE]: " << i << " color -> " << colors[i] << endl;
    }

    cout << "[MAXCOLOR] used: " << maxColor << "\n";

    // cout << g << endl;

    return 0;
}