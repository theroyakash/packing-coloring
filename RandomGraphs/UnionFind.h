#if !defined(UF)
#define UF

#include <iostream>
#include <vector>
#include <string.h>
#include <climits>
#include <set>
#include <map>
#include <queue>
#include <stack>

class DisjointSet {
public:
    std::vector<int> parent, size;
    DisjointSet(int n) {
        parent.resize(n + 1);
        size.resize(n + 1);

        for (int i = 1; i <= n; i++) {
            parent[i] = i; size[i] = 1;
        }
    }

    int Find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = Find(parent[x]);
    }

    bool Union(int x, int y) {
        x = Find(x); y = Find(y);
        if (x == y) return false;

        if (size[x] > size[y]) std::swap(x, y);
        parent[x] = y;
        size[y] += size[x];

        return true;
    }
};

#endif // UF