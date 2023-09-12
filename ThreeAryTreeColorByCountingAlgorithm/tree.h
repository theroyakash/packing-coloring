#if !defined(TREES)
#define TREES

#include <chrono>
#include <iostream>
#include <queue>
#include <set>
#include <string.h>
#include <vector>

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
void inOrder(Tree *root) {
    if (root) {
        inOrder(root->left);
        cout << root->data << "\n";
        inOrder(root->middle);
        inOrder(root->right);
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
}; // namespace TreeServices

#endif // TREES