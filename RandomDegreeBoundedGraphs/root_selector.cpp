#ifndef ROOT_SELECTOR_CPP
#define ROOT_SELECTOR_CPP

#include <vector>

#include "graph.hpp"

using namespace std;

/**
 * Selects the root of a tree using the Tree Center Root Selection Scheme.
 *
 * @param g The graph representing the tree.
 * @return id of the selected root node.
 * (we choose any random one (equally likely) when two centers are possible)
 */
namespace RootSelector {
int treeCenterRootSelectionScheme(Graph &g) {
    std::vector<int> degree(g.maxNodes + 1, 0);

    for (auto edge : g.edges) {
        degree[edge.first]++; degree[edge.second]++;
    }

    // where degree[i] is 1, we identify them as leaf nodes
    // we will remove these leaf nodes and their edges from the graph
    // and update the degree of the nodes connected to the leaf nodes

    queue<int> q;

    for (int i = 0; i <= g.maxNodes; ++i) {
        if (degree[i] == 1) {
            q.push(i);
        }
    }

    while (q.size() > 2) {
        int front = q.front();
        q.pop();
        --degree[front];

        for (auto nbr : g.adj_list[front]) {
            --degree[nbr];
            if (degree[nbr] == 1 or degree[nbr] == 0) {
                q.push(nbr);
            }
        }
    }

    return q.size() ? q.front() : 1;
}
};  // namespace RootSelector

#endif