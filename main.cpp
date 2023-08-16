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
#include <string.h>
#include <vector>

using namespace std;

/**
 * Undirected unwieghted acyclic graphs are trees
 */
class Graph {
public:
    vector<vector<int>> adj_list;

    Graph(int n) {
        for (int i = 0; i <= n; i++) {
            vector<int> v;
            adj_list.push_back(v);
        }
    }

    void add_edge(int from, int to) {
        adj_list[from].push_back(to);
        adj_list[to].push_back(from);
    }

    friend std::ostream &operator<<(std::ostream &, Graph &);

    void packingColoringSubroutine() {

    }
};

std::ostream &operator<<(std::ostream &stream, Graph &g) {
    vector<vector<int>> adj_list = g.adj_list;
    int nodes = adj_list.size();
    for (int i = 1; i < nodes; i++) {
        stream << i << " -> ";
        for (int j: adj_list[i]) {
            stream << j << " ";
        }

        stream << "\n";
    }

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

    cout << g << endl;

    return 0;
}