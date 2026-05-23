/*
Assignment 2 (DAA)
Write a program to implement Huffman Encoding using a greedy strategy.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
using namespace std;

// ---------------------------------------------------
// Class representing a tree node in the Huffman Tree
// ---------------------------------------------------
class Node
{
public:
    string ch;
    int freq;
    Node *left;
    Node *right;

    Node(string c, int f)
    {
        ch = c;
        freq = f;
        left = right = NULL;
    }
};

// -------------------------------------------------------------------
// Custom comparator for the priority queue (min-heap)
// Ensures that nodes with smaller frequencies have higher priority
// -------------------------------------------------------------------
class Compare
{
public:
    bool operator()(Node *a, Node *b)
    {
        return a->freq > b->freq;
    }
};

class Huffman
{
public:
    Node *root;

    Huffman()
    {
        root = NULL;
    }

    void buildFromString(const string &text)
    {
        map<char, int> freq;

        // Count frequency of each character
        cout << "\nStep 1: Counting character frequencies\n";
        for (char c : text)
        {
            freq[c]++;
        }

        for (auto it : freq)
        {
            cout << "Character: '" << it.first << "' -> Frequency: " << it.second << endl;
        }

        priority_queue<Node*, vector<Node*>, Compare> minHeap;

        // Create leaf nodes and push into min heap
        cout << "\nStep 2: Creating Min-Heap (Leaf Nodes)\n";
        for (auto it = freq.begin(); it != freq.end(); ++it)
        {
            Node *node = new Node(string(1, it->first), it->second);
            minHeap.push(node);
            cout << "Inserted Node -> Character: '" << it->first << "', Frequency: " << it->second << endl;
        }

        // Build Huffman Tree
        cout << "\nStep 3: Building Huffman Tree\n";
        int step = 1;
        while (minHeap.size() > 1)
        {
            Node *left = minHeap.top();
            minHeap.pop();

            Node *right = minHeap.top();
            minHeap.pop();

            string combinedName = left->ch + right->ch;
            Node *top = new Node(combinedName, left->freq + right->freq);
            top->left = left;
            top->right = right;

            cout << "Combine " << step++ << ": ("
                 << left->ch << ", " << left->freq
                 << ") + ("
                 << right->ch << ", " << right->freq
                 << ") -> (" << top->ch << ", " << top->freq << ")\n";

            minHeap.push(top);
        }

        root = minHeap.top();
        cout << "\nHuffman Tree successfully built!\n";
    }

    void printCodes(Node *node, string code)
    {
        if (!node)
        {
            return;
        }

        // Leaf node => print its code
        if (!node->left && !node->right)
        {
            cout << node->ch << " : " << code << endl;
            return;
        }

        printCodes(node->left, code + "0");
        printCodes(node->right, code + "1");
    }

    void display()
    {
        cout << "\nHuffman Codes:\n";
        printCodes(root, "");
    }
};

int main()
{
    string text;

    cout << "Enter a string: ";
    getline(cin, text);

    Huffman h;
    h.buildFromString(text);
    h.display();

    return 0;
}
