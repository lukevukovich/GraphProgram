#include "graph.h"
#include <algorithm>
#include <chrono>
#include <unordered_set>

// Constructor
Graph::Graph(int vertices) {
    this->vertices = vertices;
    adjacencyList.resize(vertices);
}

// Add an edge
void Graph::addEdge(int u, int v) {
    adjacencyList[u].push_back(v);
    adjacencyList[v].push_back(u);
}

// Print the graph
void Graph::printGraph() const {
    for (int i = 0; i < vertices; i++) {
        std::cout << i << " -> ";
        for (int v : adjacencyList[i]) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
}

// Brute Force Maximum Independent Set
std::list<int> Graph::maxIndSetBruteForce() {
    std::list<int> maxSet;
    std::vector<int> currentSet;
    maxIndSetBruteForceHelper(0, currentSet, maxSet);
    return maxSet;
}

// Helper function for Brute Force Maximum Independent Set
void Graph::maxIndSetBruteForceHelper(int start, std::vector<int>& currentSet, std::list<int>& maxSet) {
    if (start == vertices) {
        // Check if currentSet is an independent set
        bool isIndependent = true;
        for (int i = 0; i < currentSet.size(); i++) {
            for (int j = i + 1; j < currentSet.size(); j++) {
                int u = currentSet[i];
                int v = currentSet[j];
                if (std::find(adjacencyList[u].begin(), adjacencyList[u].end(), v) != adjacencyList[u].end()) {
                    isIndependent = false;
                    break;
                }
            }
            if (!isIndependent) break;
        }

        // Update maxSet if currentSet is larger
        if (isIndependent && currentSet.size() > maxSet.size()) {
            maxSet.assign(currentSet.begin(), currentSet.end());
        }
        return;
    }

    // Include current vertex in the set
    currentSet.push_back(start);
    maxIndSetBruteForceHelper(start + 1, currentSet, maxSet);

    // Exclude current vertex from the set
    currentSet.pop_back();
    maxIndSetBruteForceHelper(start + 1, currentSet, maxSet);
}

// Greedy Approximation for Maximum Independent Set
std::list<int> Graph::maxIndSetGreedy() {
    std::list<int> independentSet;
    std::vector<bool> included(vertices, false);

    // Sort vertices by degree (ascending) for greedy selection
    std::vector<int> vertexOrder(vertices);
    for (int i = 0; i < vertices; i++) vertexOrder[i] = i;
    std::sort(vertexOrder.begin(), vertexOrder.end(),
              [this](int u, int v) { return adjacencyList[u].size() < adjacencyList[v].size(); });

    for (int u : vertexOrder) {
        if (!included[u]) {
            independentSet.push_back(u);
            included[u] = true;
            // Mark all neighbors as included to prevent conflicts
            for (int v : adjacencyList[u]) {
                included[v] = true;
            }
        }
    }

    return independentSet;
}

// Timing helper function
std::pair<std::list<int>, double> Graph::timeAlgorithm(const std::function<std::list<int>()>& algorithm) const {
    auto start = std::chrono::high_resolution_clock::now();
    std::list<int> result = algorithm();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return {result, duration.count()};
}
