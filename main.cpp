/**
****************************************************************
* @file:	main.cpp [tree generation]
* @author:	@theroyakash
* @contact:	hey@theroyakash.com
* @date:	13/08/2023 18:14:27 Sunday
* @brief:	Tree Generation and transformation into a graph object
****************************************************************
**/

#include <iostream>
#include <queue>
#include <set>
#include <string.h>
#include <vector>

using namespace std;

class Color {
public:
    int colorID;

    Color(int colorID) {
        this->colorID = colorID;
    }

    friend std::ostream &operator<<(std::ostream &, Color &);
};

std::ostream &operator<<(std::ostream &stream, Color &c) {
    stream << c.colorID;
    return stream;
}

// Tree Definition
class Tree {
public:
    int data;
    Tree *left, *middle, *right;

    Tree(int d) {
        data = d;
        left = nullptr;
        middle = nullptr;
        right = nullptr;
    }
};

Tree *createTreeFromVector(vector<int> v) {
    if (v.size() == 0)
        return nullptr;

    int root = v[0];
    Tree *treeRoot = new Tree(root);

    queue<Tree *> q;
    q.push(treeRoot);
    int i = 1;

    while (not q.empty()) {
        Tree *thisNode = q.front();
        q.pop();

        thisNode->left = new Tree(v[i++]);
        q.push(thisNode->left);
        if (i >= v.size())
            break;

        thisNode->middle = new Tree(v[i++]);
        q.push(thisNode->middle);
        if (i >= v.size())
            break;

        thisNode->right = new Tree(v[i++]);
        q.push(thisNode->right);
        if (i >= v.size())
            break;
    }

    return treeRoot;
}

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

        bool visited[this->maxNodes + 1];

        while (not q.empty()) {
            pair<int, int> front = q.front();
            int node = front.first;
            distance = front.second;
            // cout << "[VISITING] NODE: " << node << endl;

            q.pop();

            for (auto nbr : adj_list[node]) {
                colorsFoundWhileVisiting.insert(colors[nbr].colorID);

                if (distance + 1 <= MAX_PERMISSIBLE_DISTANCE) {
                    if (not visited[nbr]) {
                        q.push({nbr, distance + 1});
                        visited[nbr] = true;
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

void inOrder(Tree *root) {
    if (root) {
        inOrder(root->left);
        cout << root->data << "\n";
        inOrder(root->middle);
        inOrder(root->right);
    }
}

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
        char a[1000];
        cin.getline(a, 1000);

        // String TOKENIZER to get all the numbers and convert them into integers
        // then push it into the vector
        char *ans = strtok(a, " ");
        while (ans != NULL) {
            v.push_back(stoi(ans));
            ans = strtok(NULL, " ");
        }
    }

    Tree *tree = createTreeFromVector(v);
    Graph g(maxNodeID);

    createGraphWhileLevelOrderTraversal(tree, g);

    // given the tree structure do approximatePackingColor on graph g.
    int maxColor = g.approximatePackingColor(tree);
    vector<Color> colors = g.colors;

    for (int i = 0; i < colors.size(); i++) {
        cout << "[NODE]: " << i << " color -> " << colors[i] << endl;
    }

    cout << g << endl;

    // cout << maxColor << endl;

    return 0;
}