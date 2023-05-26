#include <iostream>
#include <queue>
#include <vector>
#include <omp.h>

using namespace std;

class Graph {
    int V; // number of vertices
    vector<int>* adj; // adjacency list
public:
    Graph(int V);
    void addEdge(int v, int w);
    void bfs(int start);
};

// Constructor to initialize a graph with V vertices
Graph::Graph(int V) {
    this->V = V;
    adj = new vector<int>[V];
}

// Function to add an edge between vertices v and w
void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v);
}

// Breadth First Search algorithm
void Graph::bfs(int start) {
    // Mark all the vertices as not visited
    bool* visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;

    // Create a queue for BFS
    queue<int> q;

    // Mark the current node as visited and enqueue it
    visited[start] = true;
    q.push(start);

    while(!q.empty()) {
        // Dequeue a vertex from queue and print it
        int s;
        #pragma omp critical
        {
            s = q.front();
            q.pop();
        }

        cout << s << " ";

        // Get all adjacent vertices of the dequeued vertex s.
        // If an adjacent has not been visited, then mark it visited and enqueue it
        #pragma omp parallel for
        for(int i = 0; i < adj[s].size(); i++) {
            int v = adj[s][i];
            if(!visited[v]) {
                #pragma omp critical
                {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }

    delete[] visited;
}

int main(){
    int numVertices, numEdges;
    cout << "Enter the number of vertices in the graph: ";
    cin >> numVertices;

    Graph g(numVertices); // create a graph with numVertices vertices

    cout << "Enter the number of edges in the graph: ";
    cin >> numEdges;

    cout << "Enter the edges in the format 'v w':\n";
    for (int i = 0; i < numEdges; i++) {
        int v, w;
        cin >> v >> w;
        g.addEdge(v, w);
    }

    int startVertex;
    cout << "Enter the starting vertex for traversal: ";
    cin >> startVertex;

    // Call BFS and display complete traversal route
    cout << "BFS Traversal: ";
    g.bfs(startVertex);
    cout << endl;

    return 0;
}
