/*
Design and implement Parallel Breadth First Search and Depth First Search
using OpenMP on an Undirected Graph.
Measure performance of sequential and parallel algorithms.
*/

#include <bits/stdc++.h>
#include <omp.h>

using namespace std;

class Graph
{
    int v;
    vector<vector<int>> adj;

private:

    void dfsUtil(int node, vector<int>& visited)
    {
        visited[node] = 1;

        // cout << node << " ";     //..... to print DFS

        for (auto nbr : adj[node])
        {
            if (!visited[nbr])
            {
                visited[nbr] = 1;
                dfsUtil(nbr, visited);
            }
        }
    }

    void dfsUtilParallel(int node, vector<int>& visited)
    {
        for (auto nbr : adj[node])
        {
            if (!visited[nbr])
            {
                bool spawn_task = false;

                #pragma omp critical
                {
                    if (!visited[nbr])
                    {
                        visited[nbr] = 1;
                        spawn_task = true;
                    }
                }

                if (spawn_task)
                {
                    #pragma omp task shared(visited)
                    dfsUtilParallel(nbr, visited);
                }
            }
        }

        #pragma omp taskwait
    }

    void bfsUtil(int node, vector<int>& visited)
    {
        queue<int> q;

        q.push(node);
        visited[node] = 1;

        while (!q.empty())
        {
            int front = q.front();
            q.pop();

            // cout << front << " ";    //.... to print BFS

            for (auto nbr : adj[front])
            {
                if (!visited[nbr])
                {
                    visited[nbr] = 1;
                    q.push(nbr);
                }
            }
        }
    }

    void bfsUtilParallel(int node, vector<int>& visited)
    {
        vector<int> current;
        current.push_back(node);

        visited[node] = 1;

        while (!current.empty())
        {
            vector<int> next;

            #pragma omp parallel for
            for (int i = 0; i < current.size(); i++)
            {
                int node = current[i];

                for (int nbr : adj[node])
                {
                    if (!visited[nbr])
                    {
                        #pragma omp critical
                        {
                            if (!visited[nbr])
                            {
                                visited[nbr] = 1;
                                next.push_back(nbr);
                            }
                        }
                    }
                }
            }

            current = next;
        }
    }

public:

    Graph(int vertices)
    {
        v = vertices;
        adj.resize(v);
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void printGraph()
    {
        cout << "\nAdjacency List:\n";

        for (int i = 0; i < v; i++)
        {
            cout << i << " -> ";

            for (auto nbr : adj[i])
            {
                cout << nbr << " ";
            }

            cout << endl;
        }
    }

    void dfs(int node)
    {
        vector<int> visited(v, 0);

        dfsUtil(node, visited);

        cout << endl;
    }

    void dfsParallel(int node)
    {
        vector<int> visited(v, 0);
        visited[node] = 1;

        #pragma omp parallel
        {
            #pragma omp single
            {
                #pragma omp task shared(visited)
                dfsUtilParallel(node, visited);
            }
        }
    }

    void bfs(int node)
    {
        vector<int> visited(v, 0);

        bfsUtil(node, visited);

        cout << endl;
    }

    void bfsParallel(int node)
    {
        vector<int> visited(v, 0);
        bfsUtilParallel(node, visited);
    }
};

int main()
{
    // Printing DFS BFS for small graph
    // Graph smallGraph(7);

    // smallGraph.addEdge(0, 1);
    // smallGraph.addEdge(0, 2);
    // smallGraph.addEdge(1, 3);
    // smallGraph.addEdge(1, 4);
    // smallGraph.addEdge(2, 5);
    // smallGraph.addEdge(2, 6);

    // cout << "GRAPH\n";

    // smallGraph.printGraph();
    // cout << "\nDFS Traversal: ";
    // smallGraph.dfs(0);
    // cout << "\nBFS Traversal: ";
    // smallGraph.bfs(0);

    int V = 20000;

    Graph largeGraph(V);

    srand(42);

    // Each vertex connected to random 5 nodes
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < 150; j++)
        {
            int nbr = rand() % V;

            if (nbr != i)
            {
                largeGraph.addEdge(i, nbr);
            }
        }
    }

    cout << "\nGraph Traversals\n";

    double start, end;

    // Sequential DFS
    start = omp_get_wtime();
    largeGraph.dfs(0);
    end = omp_get_wtime();

    double seqDFS = end - start;

    // Parallel DFS
    start = omp_get_wtime();
    largeGraph.dfsParallel(0);
    end = omp_get_wtime();

    double parDFS = end - start;

    // Sequential BFS
    start = omp_get_wtime();
    largeGraph.bfs(0);
    end = omp_get_wtime();

    double seqBFS = end - start;

    // Parallel BFS
    start = omp_get_wtime();
    largeGraph.bfsParallel(0);
    end = omp_get_wtime();

    double parBFS = end - start;

    cout << "\n--- DFS Performance ---\n";
    cout << "Sequential DFS Time : " << seqDFS << " sec\n";
    cout << "Parallel DFS Time : " << parDFS << " sec\n";
    cout << "Speedup : " << seqDFS / parDFS << endl;

    cout << "\n--- BFS Performance ---\n";
    cout << "Sequential BFS Time : " << seqBFS << " sec\n";
    cout << "Parallel BFS Time : " << parBFS << " sec\n";
    cout << "Speedup : " << seqBFS / parBFS << endl;

    return 0;
}
