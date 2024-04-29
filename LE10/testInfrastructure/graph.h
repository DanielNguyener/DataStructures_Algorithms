#include <iostream>
#include <vector>
#include <list>
#include <climits>
#include <queue>
#include <unordered_set>
using namespace std;

class Graph {
    private:
        int n; //number of vertices
        typedef pair<int, int> Edge; //neighbor, weight, add Edges to list, v
        vector<list<Edge>> v; //adjacency list, gives neighbor, weight for [vertex]
        
    public:
        Graph(int size = 2) {
            n = size;
            v.resize(n);
        }

        void addEdge(int x, int y, int w) { //vertex x and vertex y, have weight w.

            v[x].push_back(Edge(y, w)); //add edge x's weight to y, to vector v.
            v[y].push_back(Edge(x, w)); //add edge y's weight to x, to vector v.
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

            // return a vector pair
            // index of vector is destination
            // the first element is distance******
            // the second element is the previous vertext along shortest path, between start and destination

            // this provides the shortest distance from start, to all destinations. 

            vector<pair<int, int>> p(n);

            for(int i = 0; i < n; i++){
                p[i] = {INT_MAX, -1};
            }

            p[startNode] = {0, startNode}; //initialize the start node to 0.
            
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; 

            Edge edge(0, startNode); //initialize the start node to 0.
            pq.push(edge);


            while(!pq.empty()){

                //extract the first vertex's distance
                int current_w = pq.top().second; //second() will give weight
                pq.pop();

                //iterate through the neighbors of the vertex
                
                for(const Edge& edge : v[current_w]){ //while there are neighbors,
                    
                    //get vertex and weight of neighbor
                    int v = edge.first;
                    int n_weight = edge.second;

                    if(p[v].first > p[current_w].first + n_weight){
                        

                        p[v].first = p[current_w].first + n_weight;
                        p[v].second = current_w; //update the previous vertex to the current vertex.

                        pq.push({p[v].first, v}); //push the neighbor to the min-heap (REMEMBER DISTANCE FIRST)
                    }
                }
            }
            

            return p;
        }

        string printShortestPath(int startNode, int endNode) {
            
            //get vector of shortest paths from startNode
            vector<pair<int, int>> vector = dijkstra(startNode);

            // If there is no path from startNode to endNode, return an empty string
            if (vector[endNode].second == -1 || vector[endNode].first == INT_MAX) {
                return ""; 
            }

            // Construct the path string starting from endNode
            string path = to_string(endNode);

            /// Traverse through the path from endNode to startNode
            int parent = vector[endNode].second;

            while (parent != startNode) {

                // add the parent node to the string
                path = to_string(parent) + " " + path;

                // Update parent to its previous vertex along the shortest path
                parent = vector[parent].second;
            }

            // add the startNode to the string
            path = to_string(startNode) + " " + path + " ";
            return path;
        }
};



