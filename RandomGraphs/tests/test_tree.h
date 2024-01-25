#if !defined(TREE_TESTS)
#define TREE_TESTS

#include <cassert>
#include <iostream>
#include "../tree.h"

void printGreenOK(string fn_name) {
    std::cout << fn_name << " " << "\033[32m[ ok ]\033[0m" << std::endl;
}

void test_buildLevelOrderTraversalStructureWithTreeReference() {
    // Create a sample tree
    Tree* root = new Tree(1);
    root->children.push_back(new Tree(2));
    root->children.push_back(new Tree(3));
    root->children[0]->children.push_back(new Tree(4));
    root->children[0]->children.push_back(new Tree(5));
    root->children[1]->children.push_back(new Tree(6));

    // Call the function
    vector<vector<Tree*>> result = TreeServices::buildLevelOrderTraversalStructureWithTreeReference(root);

    // Verify the result

    assert(result.size() == 1);
    assert(result[0].size() == 1);
    assert(result[0][0]->data == 1);
    assert(result[1].size() == 2);
    assert(result[1][0]->data == 2);
    assert(result[1][1]->data == 3);
    assert(result[2].size() == 3);
    assert(result[2][0]->data == 4);
    assert(result[2][1]->data == 5);
    assert(result[2][2]->data == 6);

    printGreenOK("buildLevelOrderTraversalStructureWithTreeReference");
}

#endif // TREE_TESTS
