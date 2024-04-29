#include <iostream>
#include <vector>
#include <list>
#include <climits>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Graph {
    private:
        unordered_map<int, unordered_map<int, int>> adjList;

    public:
        Graph() {};

        bool contains_vertex(int u) {

            if (adjList.find(u) != adjList.end()) {
                return true;
            }
            return false;
        }

        bool contains_edge(int u, int v) {

            if (adjList.find(u) != adjList.end()) {
                if (adjList[u].find(v) != adjList[u].end()) {
                    return true;
                }
            }
            return false;
        }

        void addVertex(int u) {
            adjList[u] = unordered_map<int, int>();
        }

        void addEdge(int u, int v, int w) {
            adjList[u][v] = w;
            adjList[v][u] = w;
        }

        void removeEdge(int u, int v) {
            adjList[u].erase(v);
            adjList[v].erase(u);
        }

        void removeVertex(int id) {
            adjList.erase(id);
            for (auto& entry : adjList) {
                entry.second.erase(id);
            }
        }

        int numVertices() {
            return adjList.size();
        }

        int getEdgeWeight(int u, int v) {
            if (contains_edge(u, v)) {
                return adjList[u][v];
            }
            return -1;
        }

        vector<pair<int, int>> primMST() {

            // Create a priority queue to store edges used for finding minimum weight
            priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

            // Create a bool vector to store visited vertices
            vector<bool> visited(numVertices() + 1, false);

            // Choose a starting vertex
            int startVertex = adjList.begin()->first;

            // Mark the starting vertex as visited
            visited[startVertex] = true;

            // Add all edges connected to the starting vertex to the priority queue
            for (auto& edge : adjList[startVertex]) {
                int vertex = edge.first;
                int weight = edge.second;
                pq.push({weight, {startVertex, vertex}});
            }

            // Create a vector to store the minimum spanning tree
            vector<pair<int, int>> p;

            // Repeat until all vertices are visited or the priority queue is empty
            while (!pq.empty()) {
                // Get the edge with the minimum weight from the priority queue
                pair<int, pair<int, int>> minEdge = pq.top();
                pq.pop();

                int weight = minEdge.first;
                int u = minEdge.second.first;
                int v = minEdge.second.second;

                // If the edge connects two unvisited vertices, add it to the minimum spanning tree
                if (!visited[u] || !visited[v]) {
                    p.push_back({u, v});

                    // Mark the vertices as visited
                    visited[u] = true;
                    visited[v] = true;


                    // add edges connnected to u to priority queue
                    for (auto& edge : adjList[u]) {
                        int vertex = edge.first;
                        int weight = edge.second;
                        if (!visited[vertex]) {
                            pq.push({weight, {u, vertex}});
                        }
                    }
                    
                    //add edges connected to v to priority queue
                    for (auto& edge : adjList[v]) {
                        int vertex = edge.first;
                        int weight = edge.second;
                        if (!visited[vertex]) {
                            pq.push({weight, {v, vertex}});
                        }
                    }
                }
            }

            return p; //return minimum spanning tree
        }
};