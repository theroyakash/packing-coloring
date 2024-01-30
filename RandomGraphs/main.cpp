/**
****************************************************************
* @file:	main.cpp
* @author:	@theroyakash
* @contact:	hey@theroyakash.com
* @date:	30/08/2023 21:12:17 Wednesday
* @brief:   Random Graph Generation Scheme
****************************************************************
**/

#include <math.h>
#include <string.h>

#include <chrono>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>

#include "color.h"
#include "graph.hpp"
#include "tree.h"

using namespace std;

/**
 * @brief Redirects standard input and output to files.
 *
 * This function redirects the standard input to "input.txt" file and the
 * standard output to "output.txt" file. This is useful when you want to read
 * input from a file and write output to a file instead of the console.
 *
 * @note Make sure to call this function before performing any input/output
 * operations.
 */
void fileIO() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

/**
 * @brief Solves a problem for a given case ID.
 *
 * This function generates a random graph using the G(n,p) model, where n is the
 * number of nodes and p is the probability of an edge between any two nodes. It
 * then generates the minimum spanning tree (MST) of the random graph and writes
 * the edges of the MST to a file named "edges.txt".
 *
 * @param caseid The ID of the case to solve.
 */
void GenerateRandomGraphExample(int caseid) {
    srand(time(0));
    int nodes;
    cin >> nodes;
    double logn_f_n = log2(nodes) / nodes;

    // choose a probability uniformly at random
    // between 1 * logn_f_n and 2 * logn_f_n
    double probability = (rand() % 100) / 100.0;
    probability = probability * logn_f_n;
    probability += logn_f_n;

    auto result = GraphServices::generateGnP(nodes, probability);
    std::cout << "[Probability]: " << result.second << "\n";

    Graph MST = GraphServices::generateMST(result.first);

    // write the edges of the MST in the file named "edges.txt"
    // remove and append mode
    std::ofstream file("./pyth-ext/edges.txt", std::ios::trunc);
    file.close();

    file.open("./pyth-ext/edges.txt", std::ios::app);

    if (file.is_open()) {
        for (auto edge : MST.edges) {
            file << edge.first << " " << edge.second << "\n";
        }
        file.close();
    }
}

/**
 * @input-format The first line contains the number of test cases.
 * The first line of each test case contains the number of nodes in the graph.
 * Then we generate the random graph using the G(n,p) model, where n is the
 * number of nodes and p is the probability of an edge between any two nodes.
 * 
 * We choose p uniformly at random between 1 * logn_f_n and 2 * logn_f_n
 * where logn_f_n is log2(n) / n.
 */
void solve(int caseid) {
    int total_nodes; cin >> total_nodes;
}

int main() {
    fileIO();

    int testcases = 1;
    // cin >> testcases;

    int caseid = 0;
    while (testcases--) {
        // solve(caseid++);
        GenerateRandomGraphExample(caseid++);
    }
}
