// COMSC-210 | Lab 34| Daniel Santisteban
// IDE used: VS Code
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <limits>
#include <algorithm>
using namespace std;
const int SIZE=13;
struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;  // Creates an alias 'Pair' for the pair<int,int> data type
                              // so below we can use vector<Pair> rather than vector<pair<int, int>>
class Graph {
public:
    vector<vector<Pair>> adjList;
    vector<string> stationNames;

    Graph(vector<Edge> const &edges) {
        adjList.resize(SIZE);

        // Assign station names
        stationNames = {
            "Central", "North", "East", "West", "South", "Airport",
            "Harbor", "Uptown", "Downtown", "Suburb", "TechPark",
            "Museum", "Stadium"
        };

        for (auto &edge : edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;
            adjList[src].push_back({dest, weight});
            adjList[dest].push_back({src, weight}); // undirected
        }
    }

    void printNetwork() {
        cout << "Train Network Topology:\n================================\n";
        for (int i = 0; i < adjList.size(); i++) {
            cout << "Station " << i << " (" << stationNames[i] << ") connects to:\n";
            for (Pair v : adjList[i]) {
                cout << "  → Station " << v.first << " (" << stationNames[v.first] << ") - Distance: " 
                     << v.second << " km\n";
            }
        }
        cout << endl;
    }

    void DFS(int start) {
        vector<bool> visited(SIZE, false);
        stack<int> s;
        s.push(start);

        cout << "Network Trace (DFS) from Station " << start << " (" 
             << stationNames[start] << "):\n";
        cout << "Purpose: Exploring possible routes through the network\n";
        cout << "=======================================\n";

        while (!s.empty()) {
            int node = s.top(); s.pop();
            if (!visited[node]) {
                visited[node] = true;
                cout << "Inspecting Station " << node << " (" << stationNames[node] << ")\n";
                for (auto &neighbor : adjList[node]) {
                    if (!visited[neighbor.first]) {
                        cout << "  → Potential travel to Station " << neighbor.first
                             << " (" << stationNames[neighbor.first] << ") - Distance: "
                             << neighbor.second << " km\n";
                        s.push(neighbor.first);
                    }
                }
            }
        }
        cout << endl;
    }

    void BFS(int start) {
        vector<bool> visited(SIZE, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);

        cout << "Layer-by-Layer Network Inspection (BFS) from Station " 
             << start << " (" << stationNames[start] << "):\n";
        cout << "Purpose: Analyzing stations by distance from start\n";
        cout << "=======================================\n";

        while (!q.empty()) {
            int node = q.front(); q.pop();
            cout << "Checking Station " << node << " (" << stationNames[node] << ")\n";
            for (auto &neighbor : adjList[node]) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    cout << "  → Next reachable station: " << neighbor.first
                         << " (" << stationNames[neighbor.first] << ") - Distance: "
                         << neighbor.second << " km\n";
                    q.push(neighbor.first);
                }
            }
        }
        cout << endl;
    }
    void shortestPath(int start, int end) {
        vector<int> dist(SIZE, numeric_limits<int>::max());
        vector<int> prev(SIZE, -1);
        dist[start] = 0;

        // Min-heap priority queue: {distance, node}
        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            int u = pq.top().second;
            int d = pq.top().first;
            pq.pop();

            if (d > dist[u]) continue;

            for (auto &neighbor : adjList[u]) {
                int v = neighbor.first;
                int w = neighbor.second;
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    prev[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        // Reconstruct path
        vector<int> path;
        for (int at = end; at != -1; at = prev[at])
            path.push_back(at);
        reverse(path.begin(), path.end());

        cout << "Shortest path from " << stationNames[start] << " to " 
             << stationNames[end] << ":\n";
        for (size_t i = 0; i < path.size(); i++) {
            cout << stationNames[path[i]];
            if (i != path.size()-1) cout << " → ";
        }
        cout << "\nTotal distance: " << dist[end] << " km\n\n";
    }
};
int main() {
        // number -> goes to number ( has value)
      vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        {0,3,21},{2,3,6},{2,6,2},{5,6,6},{4,5,9},{2,4,4},{2,5,5},
        {6,7,7},{7,8,10},{8,9,5},{9,10,12},{10,11,3},{11,12,8},{5,8,6},{4,9,4},{3,12,9}
    };
    // Creates graph
    Graph graph(edges);
    graph.printNetwork();
    graph.DFS(0);
    graph.BFS(0);
    graph.shortestPath(0,12);

    return 0;
}