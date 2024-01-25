#ifndef TREE_H
#define TREE_H

#include <chrono>
#include <iostream>
#include <queue>
#include <random>
#include <set>
#include <string.h>
#include <vector>

using namespace std;

/**
 * @class Tree
 * @brief Represents a tree data structure.
 *
 * The Tree class represents a tree data structure, where each node contains an integer value and a vector of child nodes.
 * It provides methods to manipulate and traverse the tree.
 */
class Tree {
public:
    int data; /**< The integer value stored in the node. */
    std::vector<Tree*> children; /**< The vector of child nodes. */

    /**
     * @brief Constructs a Tree object with the given integer value.
     * @param d The integer value to be stored in the node.
     */
    Tree(int d) {
        data = d;
    }
};

namespace TreeServices {
/**
 * Builds a level order traversal structure with tree references.
 * 
 * This function takes a root node of a tree and performs a level order traversal
 * to build a structure that represents the tree in a level-wise manner. Each level
 * contains a vector of Tree pointers representing the nodes at that level.
 * 
 * @param root The root node of the tree.
 * @return A vector of vectors, where each inner vector represents a level of the tree with each member a reference to the node.
 */
vector<vector<Tree *>> buildLevelOrderTraversalStructureWithTreeReference(Tree *root) {
    
    vector<vector<Tree *>> levelOrderTraversal;
    // do level order traversal (keep track of depth when doing so)
    queue<pair<Tree *, int>> q;
    q.push({root, 1});

    while (not q.empty()) {
        auto front = q.front();

        Tree *front_root = front.first;
        int depth = front.second;

        q.pop();

        if (depth > levelOrderTraversal.size()) {
            vector<Tree *> level = {front_root};
            levelOrderTraversal.push_back(level);
        } else if (depth == levelOrderTraversal.size()) {
            levelOrderTraversal[depth - 1].push_back(front_root);
        }

        for (Tree* child : front_root->children) {
            q.push({child, depth + 1});
        }
    }

    return levelOrderTraversal;
}
}; // namespace TreeServices

#endif // TREE_H