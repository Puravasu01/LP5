#include <iostream>
#include <stack>
#include <vector>
#include <omp.h>

using namespace std;

class Graph {
    int V; // number of vertices
    vector<int>* adj; // adjacency list
public:
    Graph(int V);
    void addEdge(int v, int w);
    void dfs(int start);
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

// Depth First Search algorithm
void Graph::dfs(int start) {
    // Create a stack for DFS
    stack<int> s;

    // Push the current source node
    s.push(start);

    while(!s.empty()) {
        // Pop a vertex from stack and print it
        int v;
        #pragma omp critical
        {
            v = s.top();
            s.pop();
        }

        if (!adj[v].empty()) {
            // Print if not visited and mark as visited
            static bool* visited = new bool[V];
            if(!visited[v]) {
                #pragma omp critical
                {
                    visited[v] = true;
                    cout << v << " ";
                }
            }

            // Get all adjacent vertices of the popped vertex v.
            // If an adjacent has not been visited, then push it to the stack in reverse order
            #pragma omp parallel for
            for(int i = adj[v].size() - 1; i >= 0; i--) {
                int u = adj[v][i];
                if(!visited[u]) {
                    #pragma omp critical
                    {
                        s.push(u);
                    }
                }
            }
        }
    }
}

int main() {
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

    // Call DFS and display complete traversal route
    cout << "DFS Traversal: ";
    g.dfs(startVertex);
    cout << endl;

    return 0;
}