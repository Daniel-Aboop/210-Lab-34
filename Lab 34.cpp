// COMSC-210 | Lab 34| Daniel Santisteban
// IDE used: VS Code
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
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

        // Add edges
        for (auto &edge : edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;
            adjList[src].push_back({dest, weight});
            adjList[dest].push_back({src, weight}); // undirected
        }
    }

    void printNetwork() {
        for (int i = 0; i < adjList.size(); i++) {
            cout << stationNames[i] << " connects to: ";
            for (Pair v : adjList[i])
                cout << "(" << stationNames[v.first] << ", " << v.second << " km) ";
            cout << endl;
        }
    }

    void BFS(int start) {
        vector<bool> visited(SIZE, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);

        cout << "BFS from " << stationNames[start] << ": ";
        while (!q.empty()) {
            int node = q.front(); q.pop();
            cout << stationNames[node] << " ";

            for (auto &neighbor : adjList[node]) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    q.push(neighbor.first);
                }
            }
        }
        cout << endl;
    }

    void DFS(int start) {
        vector<bool> visited(SIZE, false);
        stack<int> s;
        s.push(start);

        cout << "DFS from " << stationNames[start] << ": ";
        while (!s.empty()) {
            int node = s.top(); s.pop();
            if (!visited[node]) {
                visited[node] = true;
                cout << stationNames[node] << " ";
                for (auto &neighbor : adjList[node]) {
                    if (!visited[neighbor.first])
                        s.push(neighbor.first);
                }
            }
        }
        cout << endl;
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


    return 0;
}