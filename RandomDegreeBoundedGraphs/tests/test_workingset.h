#if !defined(WorkingSetTests)
#define WorkingSetTests

#include "test_utils.h"
#include "../workingset.hpp"


void test_workingset() {
    std::string fn_name = "Working Set";
    TestAssertService::setUp(fn_name);

    WorkingSet ws = WorkingSet();
    ws.add(1);
    ws.add(2);
    ws.add(3);
    ws.add(4);
    ws.add(5);

    int random = ws.getRandom();
    TestAssertService::assertEqual(random >= 1 && random <= 5, true, "random number");
    TestAssertService::assertEqual(ws.getSize(), 5, "size");

    TestAssertService::cleanUp(fn_name);
}

void test_single_member_workingset() {
    std::string fn_name = "Working Set with Single Member";
    TestAssertService::setUp(fn_name);

    WorkingSet ws = WorkingSet();
    ws.add(122);

    int random = ws.getRandom();
    TestAssertService::assertEqual(random, 122, "random number");
    TestAssertService::assertEqual(ws.getSize(), 1, "size");

    TestAssertService::cleanUp(fn_name);
}

#endif // WorkingSetTests
