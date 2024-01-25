#if !defined(GRAPHS)
#define GRAPHS

#include "color.h"
#include "UnionFind.h"
#include "tree.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string.h>
#include <vector>
#include <ctime>

using namespace std;

/**
 * @class Graph
 * @brief Represents a graph data structure.
 * 
 * The Graph class provides functionality to create and manipulate a graph.
 * It supports adding edges, storing adjacency lists, assigning colors to nodes, and performing level order traversal.
 */
class Graph {
public:
    vector<vector<int>> adj_list;
    vector<Color> colors;
    vector<vector<int>> levelOrderTraversal;
    int maxNodes;
    std::vector<pair<int, int>> edges;

    Graph(int n) {
        maxNodes = n;

        for (int i = 0; i <= n; i++) {
            vector<int> v;
            adj_list.push_back(v);
        }

        colors = vector<Color>(n + 1, Color(0));
    }

    /**
     * Adds an edge between two vertices in the graph.
     * 
     * @param from The starting vertex of the edge.
     * @param to The ending vertex of the edge.
     */
    void add_edge(int from, int to) {
        
        adj_list[from].push_back(to);
        adj_list[to].push_back(from);

        edges.push_back({from, to});
    }

    friend std::ostream &operator<<(std::ostream &, Graph &);
};


/**
 * Overloaded insertion operator for output stream.
 * Prints the adjacency list representation of the graph.
 *
 * @param stream The output stream to write to.
 * @param g The Graph object to be printed.
 * @return The output stream after writing the graph representation.
 */
std::ostream &operator<<(std::ostream &stream, Graph &g) {
    
    vector<vector<int>> adj_list = g.adj_list;
    int nodes = adj_list.size();
    for (int i = 1; i < nodes; i++) {
        stream << i << " -> ";
        for (int j : adj_list[i]) {
            stream << j << " ";
        }

        stream << "\n";
    }

    return stream;
}

namespace GraphServices {
/**
 * @brief Creates a graph by performing a level order traversal of an equivalent tree.
 * 
 * This function takes a root node of a tree and performs a level order traversal using a queue.
 * It adds edges to the graph for each child of the current node, if the child exists.
 * 
 * @param root The root node of the tree.
 * @param g The graph to which the edges will be added.
 */
void createGraphWhileLevelOrderTraversalOfEquivalentTree(Tree *root, Graph &g) {
    
    queue<Tree *> q;
    q.push(root);

    while (not q.empty()) {
        Tree *front = q.front();
        q.pop();

        for(Tree *child: front->children) {
            if (child) {
                q.push(child);
                g.add_edge(front->data, child->data);
            }
        }
    }
}

/**
 * @brief Generates an Erdos-Renyi random graph.
 * 
 * This function generates an Erdos-Renyi random graph with n nodes and an optional probability p.
 * If the probability p is not given, a random probability is generated between 0 and 1 uniformly at random.
 * 
 * @param n The number of nodes in the graph.
 * @param p The probability of an edge between any two nodes (optional).
 * @return The generated random graph.
 */
pair<Graph, double> generateGnP(int n, double p = 0) {
    // set random seed for randomization of generator
    srand(time(0));

    if (p == 0) {
        // This means that the probability is not given.
        // So we will generate a random probability.
        int probability_lower_bound = 0;
        int probability_upper_bound = 100;

        std::random_device randomDevice;
        std::mt19937 generator(randomDevice());

        std::uniform_int_distribution<int> distribution(probability_lower_bound, probability_upper_bound);

        int random_probability = distribution(generator);
        p = static_cast<double>(random_probability % 100) / 100;
    }

    // Create a graph with n nodes.
    Graph G(n);
    
    // we add each possible edge with probability p.
    // edges are un-directed, hence considered only once.
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {

            // generate a random number between 0 and 1.
            double random_number = static_cast<double>((rand() % 100)) / 100;

            // std::ofstream file("randoms.txt", std::ios::app); // Open the file in append mode
            // if (file.is_open()) {
            //     file << random_number << "\n"; // Append the random number to the file
            //     file.close();
            // } 

            if (random_number <= p) {
                // add edge between i and j.
                G.add_edge(i, j);
            }
        }
    }

    return {G, p};
}

/**
 * @brief Generates an arbitary Minimum Spanning Tree using kruskal's algorithm.
 * 
 * This function generates an arbitary Minimum Spanning Tree using kruskal's algorithm.
 * 
 * @param G The orignal graph that may contain cycle.
 * @return Once MST of the graph.
 */
Graph generateMST(Graph &G) {
    // create a disjoint set.
    DisjointSet ds(G.maxNodes);

    // create a graph with same number of nodes.
    Graph MST(G.maxNodes);

    // create a vector of edges.
    vector<pair<int, int>> edges;

    // iterate over all edges.
    for (auto edge : G.edges) {
        int from = edge.first;
        int to = edge.second;

        // if the edge does not form a cycle, add it to the MST.
        if (ds.Union(from, to)) {
            MST.add_edge(from, to);
        }
    }

    return MST;
}

}; // namespace GraphServices

#endif // GRAPHS
