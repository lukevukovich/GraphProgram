#include <iostream>
#include <iomanip>
#include "graph.h"

/*
CMSC-3140-001
Analysis of Algorithms
Graph Program
Luke Vukovich, Jonathan Buckel, Seth Morgan
*/

int main() {
    // Constants
    int numVertices = 10;
    int precision = 50;

    // Create a graph with n vertices
    Graph g(numVertices);

    // Adding edges to create a connected graph
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.addEdge(5, 6);
    g.addEdge(6, 7);
    g.addEdge(7, 8);
    g.addEdge(8, 9);
    g.addEdge(0, 9);
    g.addEdge(1, 4);
    g.addEdge(2, 5);

    // Print the adjacency list of the graph
    std::cout << "Graph adjacency list:" << std::endl;
    g.printGraph();

    // Brute force solution and timing
    std::pair<std::list<int>, double> bruteForceResult = g.timeAlgorithm([&]() { return g.maxIndSetBruteForce(); });
    std::list<int> bruteForceSolution = bruteForceResult.first;
    double bruteForceTime = bruteForceResult.second;

    std::cout << "\nBrute force solution (size " << bruteForceSolution.size() << "): ";
    for (int vertex : bruteForceSolution) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;
    std::cout << "Brute force solution took: "
              << std::fixed << std::setprecision(precision) << bruteForceTime << " seconds" << std::endl;

    // Greedy solution and timing
    std::pair<std::list<int>, double> greedyResult = g.timeAlgorithm([&]() { return g.maxIndSetGreedy(); });
    std::list<int> greedySolution = greedyResult.first;
    double greedyTime = greedyResult.second;

    std::cout << "\nGreedy solution (size " << greedySolution.size() << "): ";
    for (int vertex : greedySolution) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;
    std::cout << "Greedy solution took: "
              << std::fixed << std::setprecision(precision) << greedyTime << " seconds" << std::endl;

    return 0;
}
