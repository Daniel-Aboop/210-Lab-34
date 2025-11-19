// COMSC-210 | Lab 34| Daniel Santisteban
// IDE used: VS Code
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
const int SIZE=11;
struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;  // Creates an alias 'Pair' for the pair<int,int> data type
                              // so below we can use vector<Pair> rather than vector<pair<int, int>>
class Graph {
public:
    // a vector of vectors of Pairs to represent an adjacency list
    vector<vector<Pair>> adjList;
    // constructor
    Graph(vector<Edge> const &edges) {
        // resize the vector to hold SIZE elements of type vector<Edge>
        adjList.resize(SIZE);
        // add edges to the directed graph
        for (auto &edge: edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;
            adjList[src].push_back(make_pair(dest, weight));
            adjList[dest].push_back(make_pair(src, weight));
        }
    }
    void printGraph() {
        for (int i = 0; i < adjList.size(); i++) {
            cout<<i<<"-->";
            for (Pair v: adjList[i])
                cout << "("<< v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }
    void BFS(int start){
        vector<bool> visited(SIZE, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);

        cout << "BFS starting from node " << start << ": "<<endl;
        while (!q.empty()) {
            int node = q.front(); q.pop();
            cout << node << " ";

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

        cout << "DFS starting from node " << start << ": "<<endl;
        while (!s.empty()) {
            int node = s.top(); s.pop();
            if (!visited[node]) {
                visited[node] = true;
                cout << node << " ";
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
      vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        {0,1,12},{0,2,8},{0,3,21},{2,3,6},{2,6,2},{5,6,6},{4,5,9},{2,4,4},{2,5,5}
    };
    // Creates graph
    Graph graph(edges);
    graph.printGraph();
    graph.DFS(0);
    graph.BFS(0);


    return 0;
}