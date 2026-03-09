#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int src, dest, weight;
};

struct DisjointSet {
    vector<int> parent, rank;
    
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }
    
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
    
    void unite(int x, int y) {
        int px = find(x), py = find(y);
        if (rank[px] < rank[py]) swap(px, py);
        parent[py] = px;
        if (rank[px] == rank[py]) rank[px]++;
    }
};

vector<Edge> kruskal(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), [](Edge& a, Edge& b) {
        return a.weight < b.weight;
    });
    
    DisjointSet ds(n);
    vector<Edge> mst;
    
    for (auto& edge : edges) {
        if (ds.find(edge.src) != ds.find(edge.dest)) {
            mst.push_back(edge);
            ds.unite(edge.src, edge.dest);
        }
        if (mst.size() == n - 1) break;
    }
    
    return mst;
}

int main() {
    int n = 4;
    vector<Edge> edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };
    
    vector<Edge> mst = kruskal(n, edges);
    
    int totalWeight = 0;
    cout << "Edges in MST:" << endl;
    for (auto& edge : mst) {
        cout << edge.src << " -- " << edge.dest << " == " << edge.weight << endl;
        totalWeight += edge.weight;
    }
    cout << "Total MST weight: " << totalWeight << endl;
    
    return 0;
}