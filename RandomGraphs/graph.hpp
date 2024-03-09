#if !defined(GRAPHS)
#define GRAPHS

#include <string.h>

#include <ctime>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

#include "UnionFind.hpp"
#include "color.h"
#include "tree.h"

using namespace std;

class Graph {
public:
    vector<vector<int>> adj_list;
    vector<Color> colors;
    vector<vector<int>> levelOrderTraversal;
    vector<vector<int>> levelOrderTraversalSorted;
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

    /**
     * Calculates the level order traversal of the tree starting from the given root node.
     * The level order traversal is stored in the `levelOrderTraversal` and `levelOrderTraversalSorted` member variables.
     *
     * @param startingNode starting node of the graph.
     */
    void calculateLevelOrderTraversal(int startingNode) {
        queue<pair<int, int>> q;                             // node and depth
        vector<bool> visited(this->adj_list.size(), false);  // visited nodes

        q.push({startingNode, 0});
        visited[startingNode] = true;

        while (!q.empty()) {
            pair<int, int> front = q.front();
            int node = front.first;
            int depth = front.second;

            q.pop();

            if (depth >= (int)this->levelOrderTraversal.size()) {
                vector<int> v;
                this->levelOrderTraversal.push_back(v);
            }

            this->levelOrderTraversal[depth].push_back(node);

            for (auto nbr : adj_list[node]) {
                if (!visited[nbr]) {
                    q.push({nbr, depth + 1});
                    visited[nbr] = true;
                }
            }
        }
    }

    bool checkIfThisLevelIsPossibleToColorWithColorOne(int level_id, vector<bool> &levelsColoredWithColorOne) {
        // check if the one level up and one level down is
        // already colored with color 1, if not color this level with color 1
        if ((level_id - 1 >= 0 and not levelsColoredWithColorOne[level_id - 1]) and
            (level_id + 1 < (int)this->levelOrderTraversalSorted.size() and not levelsColoredWithColorOne[level_id + 1])) {
            return true;
        }

        // handle the outermost levels separately
        if (level_id == 0 and not levelsColoredWithColorOne[1]) {
            return true;
        } else if (level_id == (int)this->levelOrderTraversalSorted.size() - 1 and not levelsColoredWithColorOne[level_id - 1]) {
            return true;
        }

        return false;
    }

    /**
     * Maximizes the color of nodes in the graph.
     * The function sorts the level order traversal of the graph in descending order of node count per level.
     * Then, it assigns Color(1) to every other node in each level, starting from the first level.
     */
    void maximizeColorOne() {
        vector<bool> levelsColoredWithColorOne(this->levelOrderTraversal.size(), false);
        std::sort(
            this->levelOrderTraversalSorted.begin(),
            this->levelOrderTraversalSorted.end(),
            [](const vector<int> &a, const vector<int> &b) {
                return a.size() > b.size();
            });

        for (int level_id = 0; level_id < (int)this->levelOrderTraversalSorted.size(); level_id++) {
            // check if the one level up and one level down is
            // already colored with color 1, if not color this level with color 1
            if (checkIfThisLevelIsPossibleToColorWithColorOne(level_id, levelsColoredWithColorOne)) {
                levelsColoredWithColorOne[level_id] = true;
                auto level = this->levelOrderTraversalSorted[level_id];
                for (auto node : level) this->colors[node] = Color(1);
            }
            // else we don't color this level with color one and
            // move on to the next possible level
        }
    }

    /**
     * Calculates the approximate packing color of a given tree.
     *
     * This function calculates the approximate packing color of a given tree by performing a level order traversal
     * and coloring the nodes in a way that minimizes the number of unique colors used. The algorithm starts from the
     * last uncolored layer and iterates backwards, coloring each node with the smallest available color that does not
     * conflict with its neighbors. If a node cannot be colored with any available color, a new unique color is used.
     *
     * @param root A pointer to the root of the tree.
     * @return The number of uniquely used colors in the packing color.
     *
     * the coloring assingnment is stored in the colors vector
     */
    int approximatePackingColor(int rootNode) {
        calculateLevelOrderTraversal(rootNode);
        maximizeColorOne();

        int maxReusableColorUpperBound = this->maxNodes / 10;
        int uniquelyUsedColors = 0;

        for (int level = this->levelOrderTraversal.size() - 1; level >= 0; level--) {
            vector<int> thisLevel = levelOrderTraversal[level];
            // if any node in this layer is colored with
            // color 1 that means the whole layer is colored with color 1
            // so we can skip this layer
            if (this->colors[thisLevel[0]] == Color(1))
                continue;  // level already colored with color 1, move on

            for (auto candidate : thisLevel) {
                if (colors[candidate] != Color(0))
                    continue;  // node already colored, move on
                // we need to color this candidate.
                // for each node do a bfs to find if it is colorable with color = color
                int currentlyExploringColor = 1;

                set<int> colorsFoundWhileTravelling;

                while (currentlyExploringColor < maxNodes) {
                    // from color = 2 to color = MaxNodes
                    // check if it is possible to color with this node

                    // cout << "[CANDIDATE]: " << candidate << " currentlyExploringColor = " << currentlyExploringColor << endl;

                    if (colorsFoundWhileTravelling.count(currentlyExploringColor) == 0) {
                        colorsFoundWhileTravelling = travelForColor(Color(currentlyExploringColor), candidate);

                        // cout << "calling again for currentlyExploringColor = " << currentlyExploringColor << endl;

                        // if we don't find the current color then we color it with
                        // currentlyExploringColor and gtfo
                        if (colorsFoundWhileTravelling.count(currentlyExploringColor) == 0) {
                            // cout << "*************" << endl;
                            // for (auto i : colorsFoundWhileTravelling) { cout << i << " ";}
                            // cout << "\n*************" << endl;

                            colors[candidate] = currentlyExploringColor;
                            break;
                        }
                    }

                    // if it is found this means we found the currentlyExploringColor
                    // at a distance lower than the (int) currentlyExploringColor.
                    currentlyExploringColor++;

                    if (currentlyExploringColor > maxReusableColorUpperBound) {
                        uniquelyUsedColors++;
                        break;
                    }
                }
            }
        }

        return uniquelyUsedColors;  // colors used once
    }

    /**
     * @brief Finds the set of colors encountered while traveling a certain distance in the graph from a given node.
     *
     * This function performs a breadth-first search (BFS) starting from the given node and travels a distance equal to the color ID of the specified color.
     * It keeps track of the colors encountered during the traversal and returns them as a set.
     *
     * @param clr The color to be traveled to.
     * @param node The starting node for the traversal.
     * @return A set of color IDs encountered while traveling to the specified color.
     */
    set<int> travelForColor(Color clr, int __node) {
        // to color the node with Color clr, we travel to clr distance in the
        // graph by BFS
        int distance = 0;
        queue<pair<int, int>> q;
        q.push({__node, 0});

        int MAX_PERMISSIBLE_DISTANCE = clr.colorID;

        set<int> colorsFoundWhileVisiting;

        vector<bool> BFSVisited(this->maxNodes + 1, false);
        BFSVisited[__node] = true;

        while (not q.empty()) {
            pair<int, int> front = q.front();
            int node = front.first;
            distance = front.second;

            colorsFoundWhileVisiting.insert(colors[node].colorID);

            // cout << "[VISITING] NODE: " << node << " has color [COLOR]: " << colors[node] << endl;

            q.pop();

            for (auto nbr : adj_list[node]) {
                if (distance + 1 <= MAX_PERMISSIBLE_DISTANCE) {
                    if (not BFSVisited[nbr]) {
                        q.push({nbr, distance + 1});
                        BFSVisited[nbr] = true;
                    }
                }
            }
        }

        return colorsFoundWhileVisiting;
    }
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
void createGraphWhileLevelOrderTraversalOfEquivalentTree(Tree *root, Graph *g) {
    queue<Tree *> q;
    q.push(root);

    while (not q.empty()) {
        Tree *front = q.front();
        q.pop();

        for (Tree *child : front->children) {
            if (child) {
                q.push(child);
                g->add_edge(front->data, child->data);
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
    // edges are un-directed, thereby considered only once.
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());  // mt19937 is a standard mersenne_twister_engine
    std::uniform_real_distribution<double> urdist(0.0, 1.0);

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            // generate a random number between 0 and 1.
            double random_number = urdist(generator);

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

};  // namespace GraphServices

#endif  // GRAPHS
