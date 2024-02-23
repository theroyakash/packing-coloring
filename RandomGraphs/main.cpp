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
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
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
 * Writes the edges of the Minimum Spanning Tree (MST) to a file.
 * The file is named "edges.txt" and is located in the "generatedgraphs" directory.
 * The function appends the edges to the file in remove and append mode.
 * Additionally, it appends MST information to a CSV file named "mst_info.csv".
 *
 * @param MST The Minimum Spanning Tree (MST) graph.
 * @return The filename (without extension) of the generated graph file.
 */
string writeMSTEdgesToAFile(Graph MST) {
    // write the edges of the MST in the file named "edges.txt"
    // remove and append mode

    // Get the current time
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Convert the current time to a string
    std::tm* timeInfo = std::localtime(&currentTime);
    std::stringstream ss;
    ss << std::put_time(timeInfo, "%Y%m%d_%H%M%S");

    // Create a file name with the current date and time
    std::string fileName = "random_graph_" + ss.str() + ".txt";
    std::string filename_without_extension = "random_graph_" + ss.str();

    std::ofstream file("./generatedgraphs/" + fileName, std::ios::trunc);
    file.close();

    file.open("./generatedgraphs/" + fileName, std::ios::app);

    if (file.is_open()) {
        for (auto edge : MST.edges) {
            file << edge.first << " " << edge.second << "\n";
        }
        file.close();
    }

    return filename_without_extension;
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
pair<Graph, string> generateRandomGraph(int nodes) {
    srand(time(0));
    double logn_f_n = log2(nodes) / nodes;

    // choose a probability uniformly at random
    // between 1 * logn_f_n and 2 * logn_f_n
    double probability = (rand() % 100) / 100.0;
    probability = probability * logn_f_n;
    probability += logn_f_n;

    auto result = GraphServices::generateGnP(nodes, probability);
    std::cout << "[Probability]: " << result.second << "\n";

    Graph MST = GraphServices::generateMST(result.first);
    std::string filename = writeMSTEdgesToAFile(MST);

    std::string stat_fileName = filename + "_stats.txt";

    std::ofstream stat_file("./generatedgraphs/" + stat_fileName, std::ios::trunc);
    if (!stat_file.is_open()) {
        std::cout << "Error opening this [file] \nexiting" << "\n";
        return {MST, "file_error"};
    }

    stat_file << "Number of nodes: " << nodes << "\n";
    stat_file << "Probability: " << result.second << "\n";
    stat_file << "Number of edges in MST: " << MST.edges.size() << "\n";

    stat_file << "****************************************" << "\n";
    stat_file.close();

    return {MST, stat_fileName};
}

/**
 * @brief Chooses a root node for the tree.
 *
 * This function chooses a root node for the tree. It returns the nodeID of the
 * root node in the graph.
 *
 * @param g The graph.
 * @return The nodeID of the choosen root node.
 */
int chooseARoot(Graph g) {
    int root = 1;
    return root;
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
    int total_nodes;
    cin >> total_nodes;

    pair<Graph, string> result = generateRandomGraph(total_nodes);
    Graph MST = result.first;
    std::string stats = result.second;

    if (stats == "file_error") return;

    std::ofstream stat_file("./generatedgraphs/" + stats, std::ios::app);
    if (!stat_file.is_open()) {
        std::cout << "Error opening this [file] \nexiting" << "\n";
        return;
    }


    // will start the packing coloring from node 1, arbitarily
    int PACKING_COLORING_NODE_START = 1;
    auto procedure_start = std::chrono::high_resolution_clock::now();
    int uniquelyUsedColors = MST.approximatePackingColor(PACKING_COLORING_NODE_START);
    auto procedure_end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<float> duration = procedure_end - procedure_start;
    stat_file << "⏳ " << duration.count() << " seconds" << "\n";

    vector<Color> colors = MST.colors;

    int maximumReusableColorID = -1;

    map<int, int> colorCounter;

    for (int i = 1; i < (int)colors.size(); i++) {
        maximumReusableColorID = std::max(colors[i].colorID, maximumReusableColorID);
        colorCounter[colors[i].colorID]++;
    }

    stat_file << "Maximum Reusable Colors used: " << maximumReusableColorID << "\n";

    for (auto counter : colorCounter) {
        stat_file << "[COLOR]: " << counter.first << " -> " << counter.second << "\n";
    }

    stat_file << "uniquelyUsedColors: " << uniquelyUsedColors << "\n";
    
    int totalColorsUsed = maximumReusableColorID + uniquelyUsedColors;
    stat_file << "Total Colors Used = " << totalColorsUsed << "\n";

    stat_file << "****************************************" << "\n";
    stat_file.close();
}

/**
 * @brief The main function of the program.
 *
 * This function is the entry point of the program. It initializes the necessary components,
 * reads the input from a file, and executes the required operations.
 *
 * @return int The exit status of the program.
 */
int main() {
    fileIO();

    int testcases = 1;
    // cin >> testcases;

    int caseid = 0;
    while (testcases--) {
        solve(caseid++);
    }
}
