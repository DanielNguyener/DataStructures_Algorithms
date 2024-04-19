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

            vector<pair<int, int>> p;
            priority_queue<Edge, vector<Edge>, greater<Edge>> pq; //min-heap to find shortest path.

            //vector<int> distance(n, INT_MAX); //initialize a vector that stores distances

            pq.push(Edge(0, startNode)); //push the start node to the min-heap.

            //distance[startNode] = 0; //distance to start node is 0.
            p[startNode].first = 0;
            while(!pq.empty()){

                //extract the first vertex's distance
                int current_w = pq.top().second; //second() will give weight
                pq.pop();

                //iterate through the neighbors of the vertex
                list<Edge>::iterator i;
                for(i = v[current_w].begin(); i != v[current_w].end(); i++){ //while there are neighbors,
                    
                    //get vertex and weight of neighbor
                    int neighbor = (*i).first;
                    int n_weight = (*i).second;

                    //if distance to neighbor is greater than distance to current vertex
                    if(p[neighbor].first > p[current_w].first + n_weight){
                        //if(distance[neighbor] > distance[current_w] + n_weight){
                        //then update
                        //distance[neighbor] = distance[current_w] + n_weight;
                        p[neighbor].first = p[current_w].first + n_weight;
                        p[neighbor].second = current_w; //update the previous vertex to the current vertex.

                        pq.push(Edge(p[neighbor].first, neighbor)); //push the neighbor to the min-heap (REMEMBER DISTANCE FIRST)
                    }
                }
            }
            

            return p;
        }

        string printShortestPath(int startNode, int endNode) {
           return "  ";
        }
};



