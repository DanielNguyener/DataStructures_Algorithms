#include <iostream>
#include <vector>
#include <list>
#include <climits>
#include <queue>
#include <unordered_set>
using namespace std;

class Graph {
    private:
        int n;  // number of vertices
        typedef pair<int, int> Edge;
        vector<list<Edge>> v;       // first element = neighboring vertex, and second element is the weight between the two vertices
        
    public:
        // constructor
        Graph(int size = 2) {
            n = size;
            v.resize(n);
        }

        void addEdge(int x, int y, int w) {

            // instantiate Edge objects
            Edge edge1(y, w);
            Edge edge2(x, w);

            // add to adjacency list
            v[x].push_back(edge1);
            v[y].push_back(edge2);
        }

        void print() {
            for(int i = 0; i < n; i++) {
                cout << "Node " << i << " is connected to: ";
                for (pair<int,int> j : v[i]) {
                    if(j.first != -1){
                        cout << j.first << " : "<< j.second<<", ";
                    }
                }
                cout << endl;
            }
        }

        vector<pair<int, int>> dijkstra(int startNode) {
            
            vector<pair<int, int>> p(n);

            // initialize vector p 
            for (int i = 0; i < n; i++) {
                // initialize distances as infinite and previous vertex as -1
                p[i] = {INT_MAX, -1};   
            } 

            // start node initialized to 0
            p[startNode] = {0, startNode}; // distance from startNode to itself is 0

            // min heap
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; 

            // declare first edge and push to pq
            Edge e(0, startNode);
            pq.push(e);
            
            while (!pq.empty()) {
                // var u = second in pair i.e. the previous vertex 
                // top element will always be min element in heap
                int u = pq.top().second;
                pq.pop();

                for (const Edge& e : v[u]) {
                    
                    int v = e.first;
                    int weight = e.second;
 
                    // if the distance to v vertex is greater than distance of u vertex + weight, set v distance to sum
                    if (p[v].first > p[u].first + weight) {
                    p[v].first = p[u].first + weight;
                    p[v].second = u;
                    pq.push({p[v].first, v});
                    }
                }
            }

        return p;

        }


        string printShortestPath(int startNode, int endNode) {
            
            vector<pair<int, int>> vec = dijkstra(startNode);

            // Debug: Print distances and previous vertices
            //for (int i = 0; i < distances.size(); ++i) {
            //    cout << "Distance to vertex " << i << ": " << distances[i].first << ", Previous vertex: " << distances[i].second << endl;
            //}

            // vertex not reachable
            if (vec[endNode].first == INT_MAX || vec[endNode].second == -1) {
                return ""; 
            }

            // create string
            string path = to_string(endNode);

            // previous node
            int parent = vec[endNode].second;
            while (parent != startNode) {
                path = to_string(parent) + " " + path;
                parent = vec[parent].second;
            }

            // output format
            path = to_string(startNode) + " " + path + " ";
            return path;
        }
};



