#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

vector<int> dijkstra(vector<vector<pair<int,int>>>& graph, int start, int n) {
    vector<int> distances(n, INT_MAX);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    distances[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int curr_dist = pq.top().first;
        int curr_node = pq.top().second;
        pq.pop();

        if (curr_dist > distances[curr_node])
            continue;

        for (auto& [neighbor, weight] : graph[curr_node]) {
            int new_dist = distances[curr_node] + weight;
            if (new_dist < distances[neighbor]) {
                distances[neighbor] = new_dist;
                pq.push({new_dist, neighbor});
            }
        }
    }

    return distances;
}

int main() {
    int n = 4;
    vector<vector<pair<int,int>>> graph(n);

    graph[0].push_back({1, 1});
    graph[0].push_back({2, 4});
    graph[1].push_back({0, 1});
    graph[1].push_back({2, 2});
    graph[1].push_back({3, 5});
    graph[2].push_back({0, 4});
    graph[2].push_back({1, 2});
    graph[2].push_back({3, 1});
    graph[3].push_back({1, 5});
    graph[3].push_back({2, 1});

    vector<int> result = dijkstra(graph, 0, n);

    for (int i = 0; i < n; i++)
        cout << "Distance from node 0 to node " << i << ": " << result[i] << endl;

    return 0;
}