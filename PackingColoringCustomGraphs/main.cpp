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
#include "root_selector.cpp"
#include "tree.h"

#define FILE_CREATION_ERR "file_error"
#define MULTIPLE_GRAPH_STATS_DIR "./stastistics/"
#define GENERATED_GRAPHS_PATH "./generatedgraphs/"
#define MULTIPLE_RUN_CSV_HEADER "Case ID,Nodes,Edges,Starting Node,Duration,Total Colors Used,n/x Ratio,Color 1 Count,Color 2 Count,Color 1 Ratio,Total Leaves"

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
    freopen("edges.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

string writeEdgesToAFile(Graph g) {
    // write the edges of the MST in the file named "edges.txt"
    // remove and append mode

    // Get the current time
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Convert the current time to a string
    std::tm *timeInfo = std::localtime(&currentTime);
    std::stringstream ss;
    ss << std::put_time(timeInfo, "%Y%m%d_%H%M%S");

    // Create a file name with the current date and time
    std::string fileName = "random_graph_" + ss.str() + ".txt";
    std::string filename_without_extension = "random_graph_" + ss.str();

    std::ofstream file(GENERATED_GRAPHS_PATH + fileName, std::ios::trunc);
    file.close();

    file.open(GENERATED_GRAPHS_PATH + fileName, std::ios::app);

    file << g.maxNodes << "\n";

    if (file.is_open()) {
        for (auto edge : g.edges) {
            file << edge.first << " " << edge.second << "\n";
        }

        file.close();
    }

    return filename_without_extension;
}

void MULTIPLE_GROWTH_DEGREE_BOUNDED_STATS_RECORD(int caseid, Graph& g) {
    int nodes = g.maxNodes;

    int PACKING_COLORING_NODE_START =
        RootSelector::treeCenterRootSelectionScheme(g);


    std::cout << "Choosen Root Node = " << PACKING_COLORING_NODE_START << "\n";

    auto procedure_start = std::chrono::high_resolution_clock::now();
    int uniquelyUsedColors =
        g.approximatePackingColor(PACKING_COLORING_NODE_START);
    auto procedure_end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<float> duration = procedure_end - procedure_start;

    vector<Color> colors = g.colors;

    int maximumReusableColorID = -1;

    map<int, int> colorCounter;

    for (int i = 1; i < (int)colors.size(); i++) {
        maximumReusableColorID =
            std::max(colors[i].colorID, maximumReusableColorID);
        colorCounter[colors[i].colorID]++;
    }

    int totalColorsUsed = maximumReusableColorID + uniquelyUsedColors;

    int total_leaves = GraphServices::countTotalLeaves(g);

    /**
     * Write the statistics to a CSV file
     * Columns are listed below
     * - Case ID ✅
     * - Number of nodes ✅
     * - Root Node ✅
     * - Time taken to perform the packing coloring ✅
     * - Maximum reusable colors used ✅
     * - Total colors used ✅
     * - Uniquely used colors ✅
     * - n/x ratio ✅
     * - Total number of Color 1 used ✅
     * - Total number of Color 2 used ✅
     * - Fraction of Color 1 used w.r.t total nodes ✅
     * - Total number of leaves in the tree ✅
     */

    std::string stats = std::string(MULTIPLE_GRAPH_STATS_DIR) + "stats.csv";
    std::ofstream file(stats, std::ios::app);

    if (!file.is_open()) {
        std::cout << "Error opening this [file] \nexiting"
                  << endl;
        return;
    }

    file << caseid << ","
         << nodes << ","
         << g.edges.size() << ","
         << PACKING_COLORING_NODE_START << ","
         << duration.count() << " seconds,"
         << totalColorsUsed << ","
         << "n/" << nodes / totalColorsUsed << ","
         << colorCounter[1] << ","
         << colorCounter[2] << ","
         << ((double)colorCounter[1] / nodes) * 100 << "%,"
         << total_leaves << ","
         << "\n";

    // Close the stats file at the end
    file.close();

    cout << "Case with nodes " << nodes << " complete"
         << "\n"
         << endl;
}

int PACKING_COLOR_ON_CUSTOM_GRAPHS() {
    fileIO();
    int testcases;
    cin >> testcases;

    int caseid = 1;

    std::string stats = std::string(MULTIPLE_GRAPH_STATS_DIR) + "stats.csv";
    std::ofstream file(stats, std::ios::trunc);
    file.close();

    file.open(stats, std::ios::app);
    if (!file.is_open()) {
        std::cout << "Error opening this [file] \nexiting"
                  << endl;
        return -1;
    }

    file << MULTIPLE_RUN_CSV_HEADER << endl;
    file.close();

    while (testcases--) {
        int n, m;
        cin >> n >> m;

        Graph g(n);

        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            g.add_edge(u, v);
        }

        MULTIPLE_GROWTH_DEGREE_BOUNDED_STATS_RECORD(caseid++, g);

        for (int i = 1; i <= g.maxNodes; i++) {
            int color = g.colors[i].colorID;
            if (i % 2 == 0) std::cout << "Node: " << i << " color: " << color << "\n";
        }
    }

    return 0;
}


int MONTE_CARLO_SIMULATION_AVG_NEIGBOURHOOD(int n, int d, int trials, int dist) {
    double total_neighbors_within_d = 0.0;
    for (int trial = 0; trial < trials; ++trial) {
        Graph G = GraphServices::generateGrowthBoundedGraphsWithDegreeBound(n, d);
        int start_node = RootSelector::treeCenterRootSelectionScheme(G);

        // BFS to count the number of nodes within distance d
        std::vector<bool> visited(n + 1, false);
        std::vector<int> distance(n + 1, 0);

        std::queue<int> q;
        q.push(start_node);
        visited[start_node] = true;

        while (!q.empty()) {
            int current_node = q.front();
            q.pop();

            for (int neighbor : G.adj_list[current_node]) {
                if (!visited[neighbor] && distance[current_node] < dist) {
                    visited[neighbor] = true;
                    distance[neighbor] = distance[current_node] + 1;
                    q.push(neighbor);
                    total_neighbors_within_d += 1; // Increment for each node within distance d
                }
            }
        }
    }

    return total_neighbors_within_d / trials; // Average over all trials
}


int MONTECARLO_main() {
    fileIO();
    std::vector<int> tests = {100, 200, 300, 400, 500, 600, 700, 1000, 2000}; // number of nodes
    
    for (auto n : tests) {
        int d = 4;    // Maximum degree bound
        int num_trials = 1000; // Number of Monte Carlo trials

        double avg_neighbors_within_d = MONTE_CARLO_SIMULATION_AVG_NEIGBOURHOOD(n, d, num_trials, 10);
        
        std::cout << "Average number of neighbors within distance " << n/10 << " from any node: " << avg_neighbors_within_d << " and n = " << n << std::endl;

    }

    return 0;
}


int main() {
    PACKING_COLOR_ON_CUSTOM_GRAPHS();
}