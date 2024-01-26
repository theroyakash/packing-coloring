#if !defined(TREE_TESTS)
#define TREE_TESTS

#include <cassert>
#include <iostream>
#include "../tree.h"
#include "test_utils.h"

void test_buildLevelOrderTraversalStructureWithTreeReference() {
    TestAssertService::setUp("buildLevelOrderTraversalStructureWithTreeReference");

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

    TestAssertService::assertEqual((int)result.size(), 3, "size");
    TestAssertService::assertEqual((int)result[0].size(), 1, "individual level");
    TestAssertService::assertEqual(result[0][0]->data, 1, "node value at [0][0]");
    TestAssertService::assertEqual((int)result[1].size(), 2, "size at level 1");
    TestAssertService::assertEqual(result[1][0]->data, 2, "node value at [1][0]");
    TestAssertService::assertEqual(result[1][1]->data, 3, "node value at [1][1]");
    TestAssertService::assertEqual((int)result[2].size(), 3, "size at level 2");
    TestAssertService::assertEqual(result[2][0]->data, 4, "node value at [2][0]");
    TestAssertService::assertEqual(result[2][1]->data, 5, "node value at [2][1]");
    TestAssertService::assertEqual(result[2][2]->data, 6, "node value at [2][2]");


    TestAssertService::cleanUp("buildLevelOrderTraversalStructureWithTreeReference");
}

#endif // TREE_TESTS
