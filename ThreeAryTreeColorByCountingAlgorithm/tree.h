#if !defined(TREES)
#define TREES

#include <chrono>
#include <iostream>
#include <queue>
#include <set>
#include <string.h>
#include <vector>
#include <random>

using namespace std;

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

namespace TreeServices {
void inOrderTraversalOnAThreeAryTree(Tree *root) {
    if (root) {
        inOrderTraversalOnAThreeAryTree(root->left);
        cout << root->data << "\n";
        inOrderTraversalOnAThreeAryTree(root->middle);
        inOrderTraversalOnAThreeAryTree(root->right);
    }
}

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

vector<vector<int>> buildLevelOrderTraversalStructure(Tree *root) {
    vector<vector<int>> levelOrderTraversal;
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

    return levelOrderTraversal;
}

vector<vector<Tree*>> buildLevelOrderTraversalStructureWithTreeReference(Tree *root) {
    vector<vector<Tree*>> levelOrderTraversal;
    // do level order traversal (keep track of depth when doing so)
    queue<pair<Tree *, int>> q;
    q.push({root, 1});

    while (not q.empty()) {
        auto front = q.front();

        Tree *front_root = front.first;
        int depth = front.second;

        q.pop();

        if (depth > levelOrderTraversal.size()) {
            vector<Tree*> level = {front_root};
            levelOrderTraversal.push_back(level);
        } else if (depth == levelOrderTraversal.size()) {
            levelOrderTraversal[depth - 1].push_back(front_root);
        }

        if (front_root->left)
            q.push({front_root->left, depth + 1});
        if (front_root->middle)
            q.push({front_root->middle, depth + 1});
        if (front_root->right)
            q.push({front_root->right, depth + 1});
    }

    return levelOrderTraversal;
}

int randomizedTreePruningRuntime(Tree* root) {

    int totalRemovedNodes = 0;

    const int prob_lower_bound = 1;
    const int prob_upper_bound = 99;
    
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());

    std::uniform_int_distribution<int> uniform_int_distribution(prob_lower_bound, prob_upper_bound);

    vector<vector<Tree*>> levelOrder = buildLevelOrderTraversalStructureWithTreeReference(root);
    int totalLayers = levelOrder.size();

    for (int layerID = totalLayers - 1; layerID > 0; layerID--) {
        vector<Tree*> layer = levelOrder[layerID];

        long long int prob = 1;
        int damping = 1;

        for (auto& node : layer) {
            prob = (1 << damping);
            int randomInt = uniform_int_distribution(generator);

            if (randomInt < (100 / prob)) {
                // if the probability is 1/2, 1/4, 1/8, ...
                // remove the node's right and left children
                if (node -> left) {
                    totalRemovedNodes++;
                    node->left = nullptr;
                }

                if (node -> right) {
                    totalRemovedNodes++;
                    node->right = nullptr;
                }

                if (node -> middle) {
                    totalRemovedNodes++;
                    node->middle = nullptr;
                }
            }

            if (layerID & 1) damping++;
        }
    }

    return totalRemovedNodes;
}
}; // namespace TreeServices

#endif // TREES