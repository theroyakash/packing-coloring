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
#include <map>
#include <math.h>

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

    int maxNodeID = 0;
    
    for (int i = 0; i < levels; i++) {
        maxNodeID += pow(3, i);
    }

    cout << "TOTAL NODES: " << maxNodeID << endl;

    for (int i = 1; i <= maxNodeID; i++) {
        v.push_back(i);
    }

    Tree *tree = TreeServices::createTreeFromVector(v);
    Graph g(maxNodeID);

    GraphServices::createGraphWhileLevelOrderTraversal(tree, g);

    auto procedure_start = std::chrono::high_resolution_clock::now();
    // given the tree structure do approximatePackingColor on graph g.
    int uniquelyUsedColors = g.approximatePackingColor(tree);
    auto procedure_end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<float> duration = procedure_end - procedure_start;
    cout << "[TOTAL TIME]: " << duration.count() << " seconds" << endl;

    vector<Color> colors = g.colors;

    int maxColor = -1;

    map<int, int> colorCounter;

    for (int i = 1; i < colors.size(); i++) {
        // if ((i + 1) % 3 == 0) cout << endl;
        maxColor = std::max(colors[i].colorID, maxColor);
        // cout << "[NODE]: " << i << " color -> " << colors[i] << endl;
        colorCounter[colors[i].colorID]++;
    }

    cout << "[MAXCOLOR] used: " << maxColor << "\n";

    for (auto counter : colorCounter) {
        cout << "color: " << counter.first << " -> " << counter.second << "\n";
    }

    cout << "uniquelyUsedColors: " << uniquelyUsedColors << endl;
    
    int totalColorsUsed = maxColor + uniquelyUsedColors;
    cout << "Total Colors Used = " << totalColorsUsed << endl;

    return 0;
}