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
 * Writes the edges of the Minimum Spanning Tree (MST) to a file.
 * The file is named "edges.txt" and is located in the "generatedgraphs"
 * directory. The function appends the edges to the file in remove and append
 * mode. Additionally, it appends MST information to a CSV file named
 * "mst_info.csv".
 *
 * @param MST The Minimum Spanning Tree (MST) graph.
 * @return The filename (without extension) of the generated graph file.
 */
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

    if (file.is_open()) {
        file << "[\n";
        for (auto edge : g.edges) {
            file << "(" << edge.first << "," << edge.second << "),\n";
        }
        file << "]\n";
        file.close();
    }

    return filename_without_extension;
}

int main() {
    int nodes = 50;
    int degree = 2;
    Graph g = GraphServices::generateGrowthBoundedGraphsWithDegreeBound(nodes, degree);

    int d[nodes + 1];
    memset(d, 0, sizeof(d));

    for (auto edge : g.edges) {
        d[edge.first]++;
        d[edge.second]++;
    }

    for (int i = 0; i < nodes + 1; i++) {
        std::cout << d[i] << ", ";
    }

    string s = writeEdgesToAFile(g);
    cout << s << endl;

    return 0;
}
