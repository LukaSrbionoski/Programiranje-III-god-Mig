#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

vector<pair<int,int>> prim(vector<vector<pair<int,int>>>& graph, int n) {
    vector<int> key(n, INT_MAX);
    vector<int> parent(n, -1);
    vector<bool> inMST(n, false);
    
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    
    key[0] = 0;
    pq.push({0, 0});
    
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        
        if (inMST[u]) continue;
        inMST[u] = true;
        
        for (auto& [v, weight] : graph[u]) {
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }
    
    vector<pair<int,int>> mst;
    for (int i = 1; i < n; i++)
        mst.push_back({parent[i], i});
    
    return mst;
}

int main() {
    int n = 5;
    vector<vector<pair<int,int>>> graph(n);

    graph[0].push_back({1, 2});
    graph[0].push_back({3, 6});
    graph[1].push_back({0, 2});
    graph[1].push_back({2, 3});
    graph[1].push_back({3, 8});
    graph[1].push_back({4, 5});
    graph[2].push_back({1, 3});
    graph[2].push_back({4, 7});
    graph[3].push_back({0, 6});
    graph[3].push_back({1, 8});
    graph[3].push_back({4, 9});
    graph[4].push_back({1, 5});
    graph[4].push_back({2, 7});
    graph[4].push_back({3, 9});

    vector<pair<int,int>> mst = prim(graph, n);

    int totalWeight = 0;
    cout << "Edges in MST:" << endl;
    for (auto& [u, v] : mst) {
        for (auto& [neighbor, weight] : graph[u]) {
            if (neighbor == v) {
                cout << u << " -- " << v << " == " << weight << endl;
                totalWeight += weight;
                break;
            }
        }
    }
    cout << "Total MST weight: " << totalWeight << endl;

    return 0;
}