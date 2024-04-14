#if !defined(UF)
#define UF

#include <string.h>

#include <climits>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

/**
 * @class DisjointSet
 * @brief A class that implements the Disjoint Set data structure.
 */
class DisjointSet {
public:
    std::vector<int> parent, size;

    /**
     * @brief Constructs a DisjointSet object with the specified number of elements.
     * @param n The number of elements in the DisjointSet.
     */
    DisjointSet(int n) {
        parent.resize(n + 1);
        size.resize(n + 1);

        for (int i = 1; i <= n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    /**
     * @brief Finds the representative element of the set that contains the given element.
     * @param x The element to find the representative of.
     * @return The representative element of the set that contains x.
     */
    int Find(int x) {
        if (parent[x] == x)
            return x;
        return parent[x] = Find(parent[x]);
    }

    /**
     * @brief Unites the sets that contain the given elements.
     * @param x The first element.
     * @param y The second element.
     * @return True if the sets were successfully united, false if they were already in the same set.
     */
    bool Union(int x, int y) {
        x = Find(x);
        y = Find(y);
        if (x == y)
            return false;

        if (size[x] > size[y])
            std::swap(x, y);
        parent[x] = y;
        size[y] += size[x];

        return true;
    }
};

#endif  // UF