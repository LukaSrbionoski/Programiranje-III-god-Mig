class Solution {
public:
    vector<int> parent, rank;

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (px == py) return;

        if (rank[px] < rank[py])
            parent[px] = py;
        else if (rank[px] > rank[py])
            parent[py] = px;
        else {
            parent[py] = px;
            rank[px]++;
        }
    }

    int closedIsland(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        int total = rows * cols;
        int dummy = total;

        parent.resize(total + 1);
        rank.resize(total + 1, 0);

        for (int i = 0; i <= total; i++)
            parent[i] = i;

        auto id = [&](int r, int c) {
            return r * cols + c;
        };

        int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == 0) {
                    int cur = id(i, j);

                    if (i == 0 || j == 0 || i == rows - 1 || j == cols - 1)
                        unite(cur, dummy);

                    for (auto& d : dirs) {
                        int ni = i + d[0];
                        int nj = j + d[1];
                        if (ni >= 0 && nj >= 0 && ni < rows && nj < cols
                            && grid[ni][nj] == 0) {
                            unite(cur, id(ni, nj));
                        }
                    }
                }
            }
        }

        int dummyRoot = find(dummy);
        unordered_set<int> closed;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == 0) {
                    int root = find(id(i, j));
                    if (root != dummyRoot)
                        closed.insert(root);
                }
            }
        }

        return closed.size();
    }
};
