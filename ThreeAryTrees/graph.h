#if !defined(GRAPHS)
#define GRAPHS

#include "color.h"
#include "tree.h"
#include <iostream>
#include <queue>
#include <set>
#include <string.h>
#include <vector>

using namespace std;

/**
 * Undirected unwieghted acyclic graphs are trees
 */
class Graph {
public:
    vector<vector<int>> adj_list;
    vector<Color> colors;
    vector<vector<int>> levelOrderTraversal;
    int maxNodes;

    Graph(int n) {
        maxNodes = n;

        for (int i = 0; i <= n; i++) {
            vector<int> v;
            adj_list.push_back(v);
        }

        colors = vector<Color>(n + 1, Color(0));
    }

    void add_edge(int from, int to) {
        adj_list[from].push_back(to);
        adj_list[to].push_back(from);
    }

    friend std::ostream &operator<<(std::ostream &, Graph &);

    void buildLevelOrderTraversalStructure(Tree *root) {
        // do level order traversal (keep track of depth when doing so)
        queue<pair<Tree *, int>> q;
        q.push({root, 1});

        while (not q.empty()) {
            auto front = q.front();

            Tree *front_root = front.first;
            int depth = front.second;

            q.pop();

            if (depth > levelOrderTraversal.size()) {
                vector<int> level = {front_root->data};
                levelOrderTraversal.push_back(level);
            } else if (depth == levelOrderTraversal.size()) {
                levelOrderTraversal[depth - 1].push_back(front_root->data);
            }

            if (front_root->left)
                q.push({front_root->left, depth + 1});
            if (front_root->middle)
                q.push({front_root->middle, depth + 1});
            if (front_root->right)
                q.push({front_root->right, depth + 1});
        }
    }

    void packingColorOddLayersWithColorOne(Tree *root) {
        buildLevelOrderTraversalStructure(root);

        int levels = levelOrderTraversal.size();
        for (int i = 0; i < levels; i++) {
            int levelID = i + 1;
            if (levelID % 2 != 0) {
                for (auto candidate : levelOrderTraversal[levelID - 1]) {
                    colors[candidate] = Color(1);
                }
            }
        }
    }

    int approximatePackingColor(Tree *root) {
        // color each odd-layered node with 1
        packingColorOddLayersWithColorOne(root);

        // start from the last uncolored level
        int lastUncoloredLevel = -1;
        for (int i = levelOrderTraversal.size() - 1; i >= 0; i--) {
            if (colors[levelOrderTraversal[i][0]].colorID == 0) {
                lastUncoloredLevel = i;
                break;
            }
        }

        for (int level = lastUncoloredLevel; level >= 0; level -= 2) {
            vector<int> thisLevel = levelOrderTraversal[level];
            for (auto candidate : thisLevel) {
                if (colors[candidate].colorID != 0)
                    continue;
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
                }
            }
        }

        return -1;
    }

    set<int> travelForColor(Color clr, int node) {
        // to color the node with Color clr, we travel to clr distance in the
        // graph by BFS
        int distance = 0;
        queue<pair<int, int>> q;
        q.push({node, 0});

        int MAX_PERMISSIBLE_DISTANCE = clr.colorID;

        set<int> colorsFoundWhileVisiting;

        vector<bool> BFSVisited(this->maxNodes + 1, false);
        BFSVisited[node] = true;

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
void createGraphWhileLevelOrderTraversal(Tree *root, Graph &g) {
    queue<Tree *> q;
    q.push(root);

    while (not q.empty()) {
        Tree *front = q.front();
        q.pop();

        if (front->left) {
            q.push(front->left);
            g.add_edge(front->data, (front->left)->data);
        }

        if (front->middle) {
            q.push(front->middle);
            g.add_edge(front->data, (front->middle)->data);
        }

        if (front->right) {
            q.push(front->right);
            g.add_edge(front->data, (front->right)->data);
        }
    }
}
}; // namespace GraphServices

#endif // GRAPHS
