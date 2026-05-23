/*
Assignment 2 (DAA)
Knapsack problem using dynamic programming or branch and bound strategy.

*/

#include <bits/stdc++.h>
using namespace std;

// ====================== DYNAMIC PROGRAMMING ======================
class KnapsackDP
{
public:
    void solve(vector<double> &wt, vector<double> &val, double W)
    {
        int n = wt.size();
        vector<vector<double>> dp(n + 1, vector<double>(int(W) + 1, 0));

        // Build DP table
        for (int i = 1; i <= n; i++)
        {
            for (int w = 1; w <= int(W); w++)
            {
                if (wt[i - 1] <= w)
                {
                    dp[i][w] = max(val[i - 1] + dp[i - 1][int(w - wt[i - 1])], dp[i - 1][w]);
                }
                else
                {
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }

        // Display DP Table
        cout << "\nDP Table:\n";
        for (int i = 0; i <= n; i++)
        {
            for (int w = 0; w <= int(W); w++)
            {
                cout << setw(6) << dp[i][w];
            }
            cout << "\n";
        }

        cout << "\nMaximum Profit (DP): " << dp[n][int(W)] << "\n";
        cout << "Time Complexity: O(n * W)\n";
        cout << "Space Complexity: O(n * W)\n";
    }
};

// ====================== BRANCH AND BOUND ======================
class Item
{
public:
    double value, weight, ratio;
    Item(double v = 0, double w = 0) : value(v), weight(w)
    {
        ratio = (w == 0) ? 0 : v / w;
    }
};

class Node
{
public:
    int level;
    double profit, weight, bound;
    Node(int l = 0, double p = 0, double w = 0, double b = 0) 
    {
        level = l;
        profit = p;
        weight = w;
        bound = b;
    }
};

class KnapsackBB
{
private:
    // Compute upper bound for node
    double bound(Node u, int n, double W, vector<Item> &items)
    {
        if (u.weight >= W)
        {
            return 0;
        }

        double profitBound = u.profit;
        int j = u.level + 1;
        double totalWeight = u.weight;

        while (j < n && totalWeight + items[j].weight <= W)
        {
            totalWeight += items[j].weight;
            profitBound += items[j].value;
            j++;
        }

        if (j < n)
        {
            profitBound += (W - totalWeight) * items[j].ratio;
        }

        return profitBound;
    }

    static bool compareItems(const Item &a, const Item &b)
    {
        return a.ratio > b.ratio;
    }

public:
    void solve(vector<double> &wt, vector<double> &val, double W)
    {
        int n = wt.size();
        vector<Item> items;
        for (int i = 0; i < n; i++)
        {
            items.push_back(Item(val[i], wt[i]));
        }

        sort(items.begin(), items.end(), compareItems);

        queue<Node> Q;
        Node u, v;
        v.level = -1;
        v.profit = v.weight = 0;
        v.bound = bound(v, n, W, items);
        Q.push(v);

        double maxProfit = 0;

        cout << "\nBranch & Bound Node Exploration:\n";
        cout << left << setw(8) << "Level" << setw(12) << "Profit"
             << setw(12) << "Weight" << setw(12) << "Bound" << "\n";
        cout << "-------------------------------------------\n";

        while (!Q.empty())
        {
            v = Q.front();
            Q.pop();

            if (v.level == n - 1)
            {
                continue;
            }

            // Case 1: Include next item
            u.level = v.level + 1;
            u.weight = v.weight + items[u.level].weight;
            u.profit = v.profit + items[u.level].value;

            if (u.weight <= W && u.profit > maxProfit)
            {
                maxProfit = u.profit;
            }

            u.bound = bound(u, n, W, items);
            cout << left << setw(8) << u.level << setw(12) << u.profit
                 << setw(12) << u.weight << setw(12) << fixed << setprecision(2) << u.bound << "\n";

            if (u.bound > maxProfit)
            {
                Q.push(u);
            }

            // Case 2: Exclude next item
            u.weight = v.weight;
            u.profit = v.profit;
            u.bound = bound(u, n, W, items);
            cout << left << setw(8) << u.level << setw(12) << u.profit
                 << setw(12) << u.weight << setw(12) << fixed << setprecision(2) << u.bound << "\n";

            if (u.bound > maxProfit)
            {
                Q.push(u);
            }
        }

        cout << "\nMaximum Profit (Branch & Bound): " << maxProfit << "\n";
        cout << "Time Complexity: O(2^n) (worst)\n";
        cout << "Space Complexity: O(n)\n";
    }
};

// ====================== MAIN PROGRAM ======================
int main()
{
    int n, choice=0;
    double W;

    cout << "Enter number of items: ";
    cin >> n;

    vector<double> val(n), wt(n);
    cout << "Enter values of items:\n";
    for (int i = 0; i < n; i++)
    {
        cin >> val[i];
    }

    cout << "Enter weights of items:\n";
    for (int i = 0; i < n; i++)
    {
        cin >> wt[i];
    }

    cout << "Enter capacity of knapsack: ";
    cin >> W;

    KnapsackDP dpSolver;
    KnapsackBB bbSolver;

    while (choice != 3)
    {
        cout << "\nPress \n1. Knapsack using Dynamic Programming"
             << "\n2. Knapsack using Branch and Bound"
             << "\n3. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                dpSolver.solve(wt, val, W);
                break;

            case 2:
                bbSolver.solve(wt, val, W);
                break;

            case 3:
                cout << "Program Ended.\n";

            default:
                cout << "Invalid Choice! Try again.\n";
        }
    }

    return 0;
}

