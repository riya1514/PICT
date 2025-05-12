#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define INF 9999

class SelectionSort
{
public:
    SelectionSort()
    {
        cout << "\n--------------------------\n";
        cout<<"Selection Sort Algorithm\n";
        cout << "--------------------------\n";
        cout << "\nEnter number of elements: ";
        int n;
        cin >> n;
        vector<int> arr(n);
        cout << "\nEnter elements:\n";
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }

        sort(arr);

        cout << "\nSorted array: ";
        for (int i = 0; i < n; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    void sort(vector<int> &arr)
    {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++)
        {
            int minIndex = i;
            for (int j = i + 1; j < n; j++)
            {
                if (arr[j] < arr[minIndex])
                {
                    minIndex = j;
                }
            }
            swap(arr[i], arr[minIndex]);
        }
    }
};

class Graph
{
public:
    vector<vector<int>> graph;
    int n, isDirected, isWeighted;

    Graph()
    {
        n = isDirected = isWeighted = 0;
    }

    void init_graph()
    {
        cout << "\n--------------------------\n";
        cout << "Graph Creation and Display \n";
        cout << "--------------------------\n";
        cout << "\nEnter number of vertices: ";
        int x;
        cin >> x;
        n = x;
        cout << "\nIs the graph directed? (1 for yes, 0 for no): ";
        cin >> isDirected;
        cout << "\nIs the graph weighted? (1 for yes, 0 for no): ";
        cin >> isWeighted;

        graph.resize(n, vector<int>(n, 0));
    }

    bool is_empty()
    {
        if (n == 0)
        {
            return true;
        }
        return false;
    }

    void printGraph()
    {
        cout << "\nAdjacency Matrix:\n";
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << graph[i][j] << " ";
            }
            cout << endl;
        }
    }

    void readGraphByEdge()
    {
        cout << endl;
        int u, v, w;
        while (true)
        {
            cout << "Enter edge (u v w) or -1 to stop: ";
            cin >> u;
            if (u == -1)
            {
                break;
            }
            cin >> v >> w;
            graph[u][v] = isWeighted ? w : 1;
            if (!isDirected)
            {
                graph[v][u] = isWeighted ? w : 1;
            }
        }
    }

    void prims()
    {
        cout << "\n----------------------------------------\n";
        cout << "Prims Algorithm (Minimum Spanning Tree)\n";
        cout << "------------------------------------------\n";
        vector<vector<int>> cost(n, vector<int>(n));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cost[i][j] = (graph[i][j] == 0) ? INF : graph[i][j];
            }
        }

        vector<int> visited(n, 0), dist(n), from(n);
        for (int i = 0; i < n; i++)
        {
            dist[i] = cost[0][i];
            from[i] = 0;
        }

        visited[0] = 1;
        dist[0] = 0;
        int minCost = 0;

        cout << endl;
        for (int count = 1; count < n; count++)
        {
            int minDist = INF, v = -1;

            for (int i = 0; i < n; i++)
            {
                if (!visited[i] && dist[i] < minDist)
                {
                    minDist = dist[i];
                    v = i;
                }
            }

            if (v == -1)
            {
                break;
            }

            int u = from[v];
            visited[v] = 1;
            cout << "Edge: " << u << " - " << v << " Weight: " << cost[u][v] << endl;
            minCost += cost[u][v];

            for (int i = 0; i < n; i++)
            {
                if (!visited[i] && cost[v][i] < dist[i])
                {
                    dist[i] = cost[v][i];
                    from[i] = v;
                }
            }
        }

        cout << "\nMinimum Cost of MST: " << minCost << endl;
    }

    void dijkstras()
    {
        cout << "\n-------------------------------------\n";
        cout << "Dijkstras Algorithms (Shortest Path)\n";
        cout << "---------------------------------------\n";
        vector<vector<int>> cost(n, vector<int>(n));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cost[i][j] = (graph[i][j] == 0) ? INF : graph[i][j];
            }
        }

        vector<int> visited(n, 0), dist(n), from(n, -1);
        int src = 0;

        for (int i = 0; i < n; i++)
        {
            dist[i] = cost[src][i];
            if (cost[src][i] != INF)
            {
                from[i] = src;
            }
        }

        visited[src] = 1;
        dist[src] = 0;

        for (int count = 1; count < n; count++)
        {
            int minDist = INF, v = -1;

            for (int i = 0; i < n; i++)
            {
                if (!visited[i] && dist[i] < minDist)
                {
                    minDist = dist[i];
                    v = i;
                }
            }

            if (v == -1)
            {
                break;
            }

            visited[v] = 1;

            for (int i = 0; i < n; i++)
            {
                if (!visited[i] && dist[i] > dist[v] + cost[v][i])
                {
                    dist[i] = dist[v] + cost[v][i];
                    from[i] = v;
                }
            }
        }

        cout << "\nShortest paths from source vertex 0:\n";
        for (int i = 0; i < n; i++)
        {
            if (dist[i] == INF)
            {
                cout << "To " << i << ": No path\n";
                continue;
            }

            cout << "To " << i << " (Cost: " << dist[i] << "): ";
            vector<int> path;
            for (int j = i; j != -1; j = from[j])
            {
                path.push_back(j);
            }
            reverse(path.begin(), path.end());
            for (int j : path)
            {
                cout << j << (j == i ? "\n" : " -> ");
            }
        }
    }
};

int main()
{
    Graph g;

    while (true)
    {
        cout << "\n===== CHOICES =====\n";
        cout << "1. Selection Sort\n";
        cout << "2. Create Graph & Display Adjacency Matrix\n";
        cout << "3. Apply Prim's Algorithm\n";
        cout << "4. Apply Dijkstra's Algorithm\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            SelectionSort();
            break;

        case 2:
            g.init_graph();
            g.readGraphByEdge();
            g.printGraph();
            break;

        case 3:
            if (!g.is_empty())
                g.prims();
            else
                cout << "\nPlease create a graph first (Option 2).\n";
            break;

        case 4:
            if (!g.is_empty())
                g.dijkstras();
            else
                cout << "\nPlease create a graph first (Option 2).\n";
            break;

        case 5:
            cout << "\nExiting program.\n";
            return 0;

        default:
            cout << "\nInvalid choice. Try again.\n";
        }
    }

    return 0;
}
