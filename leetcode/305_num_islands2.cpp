#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "common_function.h"

using namespace std;

class UnionFind {
public:
    UnionFind(int N) {
        count = 0;
        for (int i = 0; i < N; ++i) {
            parent.push_back(-1);
            rank.push_back(0);
        }
    }

    bool isValid(int i) const {
        return parent[i] >= 0;
    }

    void setParent(int i) {
        if (parent[i] == -1) {
            parent[i] = i;
            ++count;
        }
    }

    int find(int i) { // path compression
        if (parent[i] != i) parent[i] = find(parent[i]);
        return parent[i];
    }

    void Union(int x, int y) { // union with rank
        int rootx = find(x);
        int rooty = find(y);
        if (rootx != rooty) {
            if (rank[rootx] > rank[rooty]) parent[rooty] = rootx;
            else if (rank[rootx] < rank[rooty]) parent[rootx] = rooty;
            else {
                parent[rooty] = rootx; rank[rootx] += 1;
            }
            --count;
        }
    }

    int getCount() const {
        return count;
    }

private:
    vector<int> parent;
    vector<int> rank;
    int count; // # of connected components
};

class SolutionNumIslands2UnionSet {
public:
    vector<int> numIslands2(int m, int n, vector<pair<int, int> >& positions) {
        vector<int> ans;
        UnionFind uf (m * n);

        for (auto& pos : positions) {
            int r = pos.first;
            int c = pos.second;
            // check pos's nei***ors to see if they are in the existing islands or not
            vector<int> overlap; // how many existing islands overlap with 'pos'
            if (r - 1 >= 0 && uf.isValid((r - 1) * n + c)) overlap.push_back((r - 1) * n + c);
            if (r + 1 < m && uf.isValid((r + 1) * n + c)) overlap.push_back((r + 1) * n + c);
            if (c - 1 >= 0 && uf.isValid(r * n + c - 1)) overlap.push_back(r * n + c - 1);
            if (c + 1 < n && uf.isValid(r * n + c + 1)) overlap.push_back(r * n + c + 1);

            int index = r * n + c;
            uf.setParent(index);
            for (auto i : overlap) uf.Union(i, index);
            ans.push_back(uf.getCount());
        }

        return ans;
    }
};

class SolutionNumIslands2Hash {
public:
    vector<int> numIslands2(int m, int n, vector<pair<int, int>>& positions) {
        vector<int> ans;
        unordered_map<int, int> land2id; // land index : island ID
        int num_islands = 0;
        int island_id = 0;
        for (auto pos : positions) {
            int r = pos.first;
            int c = pos.second;
            // check pos's nei***ors to see if they are in the existing islands or not
            unordered_set<int> overlap; // how many existing islands overlap with 'pos'
            if (r - 1 >= 0 && land2id.count((r - 1) * n + c)) overlap.insert(land2id[(r-1) * n + c]);
            if (r + 1 < m && land2id.count((r + 1) * n + c)) overlap.insert(land2id[(r+1) * n + c]);
            if (c - 1 >= 0 && land2id.count(r * n + c - 1)) overlap.insert(land2id[r * n + c - 1]);
            if (c + 1 < n && land2id.count(r * n + c + 1)) overlap.insert(land2id[r * n + c + 1]);

            // no overlap
            if (overlap.empty()) {
                if (!land2id.count(r * n + c)) {
                    ++num_islands;
                }
                land2id[r * n + c] = island_id++;       // new island
            } else if (overlap.size() == 1) {           // one overlap, just append
                auto it = overlap.begin();
                land2id[r * n + c] = *it;
            } else {                                    // more than 1 overlaps, merge
                auto it = overlap.begin();
                int root_id = *it;
                for (auto& kv : land2id) { // update island id
                    if (overlap.count(kv.second)) kv.second = root_id;
                }
                land2id[r * n + c] = root_id;
                num_islands -= (overlap.size() - 1);
            }

            ans.push_back(num_islands);
        }

        return ans;
    }
};

class Solution {
private:
    void dfs(vector<vector<char>>& grid, int r, int c, vector<vector<bool>>& visited) {
        int nr = grid.size();
        int nc = grid[0].size();

        if (r < 0 || c < 0 || r >= nr || c >= nc || grid[r][c] == '0' || visited[r][c]) return;

        visited[r][c] = true;
        dfs(grid, r - 1, c, visited);
        dfs(grid, r + 1, c, visited);
        dfs(grid, r, c - 1, visited);
        dfs(grid, r, c + 1, visited);
    }

    int numIslands(vector<vector<char>>& grid) {
        int nr = grid.size();
        int nc = grid[0].size();

        vector<vector<bool> > visited (nr, vector<bool>(nc, false));
        int num_islands = 0;
        for (int r = 0; r < nr; ++r) {
            for (int c = 0; c < nc; ++c) {
                if (grid[r][c] == '1' && !visited[r][c]) {
                    ++num_islands;
                    dfs(grid, r, c, visited);
                }
            }
        }

        return num_islands;
    }

public:
    vector<int> numIslands2(int m, int n, vector<pair<int, int>>& positions) {
        vector<int> ans;
        vector<vector<char> > grid (m, vector<char>(n, '0'));
        for (auto pos : positions) {
            grid[pos.first][pos.second] = '1';
            ans.push_back(numIslands(grid));
        }

        return ans;
    }
};

void TestNumIslands2() {
    int m = 3, n = 3;
    vector<pair<int, int> > positions = { { 0, 0 }, { 0, 1 }, { 1, 2 }, { 1, 2 } };
    SolutionNumIslands2UnionSet so_union;
    SolutionNumIslands2Hash so_hash;
    Solution so;
    vector<int> land_count_list1;
    vector<int> land_count_list2;
    vector<int> land_count_list3;
    {
        TimerClock tc(true);
        land_count_list3 = so.numIslands2(m, n, positions);
    }
    {
        TimerClock tc(true);
        land_count_list1 = so_union.numIslands2(m, n, positions);
    }
    {
        TimerClock tc(true);
        land_count_list2 = so_hash.numIslands2(m, n, positions);
    }
    Print1DVector<int>(land_count_list1);
    Print1DVector<int>(land_count_list2);
    Print1DVector<int>(land_count_list3);
}

int main() {
    TestNumIslands2();

    return 0;
}
