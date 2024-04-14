#include "./tests/test_tree.h"
#include "./tests/test_workingset.h"

int main() {
    test_buildLevelOrderTraversalStructureWithTreeReference();

    // working set tests
    test_workingset(); test_single_member_workingset();
    return 0;
}