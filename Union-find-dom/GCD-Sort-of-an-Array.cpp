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

    bool gcdSort(vector<int>& nums) {
        int n = nums.size();
        parent.resize(n);
        rank.resize(n, 0);

        for (int i = 0; i < n; i++)
            parent[i] = i;

        unordered_map<int, int> primeOwner;

        for (int i = 0; i < n; i++) {
            int x = nums[i];

            for (int p = 2; p * p <= x; p++) {
                if (x % p == 0) {
                    if (primeOwner.count(p))
                        unite(i, primeOwner[p]);
                    else
                        primeOwner[p] = i;

                    while (x % p == 0) x /= p;
                }
            }
            if (x > 1) {
                if (primeOwner.count(x))
                    unite(i, primeOwner[x]);
                else
                    primeOwner[x] = i;
            }
        }

        vector<int> sortedNums = nums;
        sort(sortedNums.begin(), sortedNums.end());

        unordered_map<int, vector<int>> valueIndices;
        for (int i = 0; i < n; i++)
            valueIndices[sortedNums[i]].push_back(i);

        for (int i = 0; i < n; i++) {
            int targetIndex = valueIndices[nums[i]].back();
            valueIndices[nums[i]].pop_back();

            if (find(i) != find(targetIndex))
                return false;
        }

        return true;
    }
};
