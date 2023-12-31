#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
#include <iostream>
#include "data_structs.hpp"
#include "types.hpp"

using namespace std;

/*
    Solves the "shortest path" problem using Dijkstra's algorithm.
    Time complexity is O(n log n), where n is the number of nodes in the graph
    since we use a priority queue.

    @param graph: the graph to solve
    @param start: the starting node
    @return: a vector containing the shortest path from the starting node to each
             node
*/
vector<int> dijkstra(const Graph &graph, int init)
{
    const int n = graph.adj_list.size();
    if (init >= n)
    {
        throw out_of_range("Start node is out of the range of the graph nodes.");
    }
    // No negative weights allowed
    for (const auto &edges : graph.adj_list)
    {
        for (const auto &edge : edges)
        {
            if (edge.second < 0)
            {
                throw invalid_argument("Graph contains negative edge weight, which is not allowed for Dijkstra's algorithm.");
            }
        }
    }
    vector<int> d(n, INT_MAX);      // shortest distances
    vector<bool> visited(n, false); // visited nodes
    MinHeap mh;                     // auto reheapifies since it's a priority queue alias

    d[init] = 0;        // Distance to itself is 0
    mh.push({init, 0}); //  {nodeID, distance}

    while (!mh.empty())
    {
        int a = mh.top().first; // Current node is smallest in the heap (root)
        mh.pop();

        if (!visited[a])
        {
            // Check all neighbors of the current node 'a'
            for (const auto &neighbor : graph.adj_list[a])
            {
                int v = neighbor.first;       // Neighbor node ID
                int weight = neighbor.second; // Weight of the edge to the neighbor

                // If the neighbor node hasn't been visited and the new distance is shorter, update it
                int greedyDistance = d[a] + weight;
                if (d[v] > greedyDistance)
                {
                    d[v] = d[a] + weight;
                    mh.push({v, d[v]});
                }
            }
            visited[a] = true;
        }
    }
    return d;
}

/*
    Computes the shortest path distances from each node to every other node
    in the graph using Dijkstra's algorithm.

    Results in O(n^2 log n) time complexity, since we run Dijkstra's algorithm
    n times, where n is the number of nodes in the graph.

    @param graph: the graph to run the algorithm on
    @return: a 2D vector where the element at [i][j] represents the shortest
             distance from node i to node j
*/
vector<vector<int>> dijkstraAll(const Graph &graph)
{
    const int n = graph.adj_list.size();
    vector<vector<int>> allDistances(n, vector<int>(n, INT_MAX)); // 2D vector to store distances

    // Run Dijkstra's algorithm for each node as the start node
    for (int init = 0; init < n; ++init)
    {
        allDistances[init] = dijkstra(graph, init);
    }

    return allDistances;
}

/*
    Prints the shortest path distances between each pair of nodes as calculated
    by Dijkstra's algorithm.

    @param allDistances: a 2D vector containing the shortest distances between
                          all pairs of nodes, as returned by dijkstraAll()
*/
void printDijkstraAll(const vector<vector<int>> &allDistances)
{
    cout << "\nDijkstra:\n";
    for (int i = 0; i < allDistances.size(); ++i)
    {
        for (int j = 0; j < allDistances[i].size(); ++j)
        {
            if (i != j)
            { // Avoid printing distance from a node to itself
                if (allDistances[i][j] == INT_MAX)
                {
                    cout << "node " << i + 1 << " to node " << j + 1 << " : "
                         << "∞\n";
                }
                else
                {

                    cout << "node " << i + 1 << " to node " << j + 1 << " : " << allDistances[i][j] << "\n";
                }
            }
        }
    }
}

#endif