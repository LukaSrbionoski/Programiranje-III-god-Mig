#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Edge {
    int src, dest, weight;
};

vector<int> bellmanFord(int n, int start, vector<Edge>& edges) {
    vector<int> distances(n, INT_MAX);
    distances[start] = 0;

    for (int i = 0; i < n - 1; i++) {
        for (auto& edge : edges) {
            if (distances[edge.src] != INT_MAX &&
                distances[edge.src] + edge.weight < distances[edge.dest]) {
                distances[edge.dest] = distances[edge.src] + edge.weight;
                }
        }
    }

    for (auto& edge : edges) {
        if (distances[edge.src] != INT_MAX &&
            distances[edge.src] + edge.weight < distances[edge.dest]) {
            cout << "Negative cycle detected!" << endl;
            return {};
            }
    }

    return distances;
}

int main() {
    int n = 5;
    vector<Edge> edges = {
        {0, 1, -1},
        {0, 2,  4},
        {1, 2,  3},
        {1, 3,  2},
        {1, 4,  2},
        {3, 2,  5},
        {3, 1,  1},
        {4, 3, -3}
    };

    vector<int> result = bellmanFord(n, 0, edges);

    if (!result.empty()) {
        cout << "Distances from node 0:" << endl;
        for (int i = 0; i < n; i++)
            cout << "Node " << i << ": " << result[i] << endl;
    }

    return 0;
}