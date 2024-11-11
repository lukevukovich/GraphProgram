#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <list>
#include <functional>

class Graph {
public:
    Graph(int vertices);
    void addEdge(int u, int v);
    void printGraph() const;
    std::list<int> maxIndSetBruteForce();
    std::list<int> maxIndSetGreedy();
    std::pair<std::list<int>, double> timeAlgorithm(const std::function<std::list<int>()>& algorithm) const;

private:
    void maxIndSetBruteForceHelper(int start, std::vector<int>& currentSet, std::list<int>& maxSet);
    int vertices;
    std::vector<std::list<int>> adjacencyList;
};

#endif // GRAPH_H
