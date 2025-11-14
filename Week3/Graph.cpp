
#include <iostream>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include "Graph.h"

using namespace std;

// Get the number of vertices in the graph
int Graph::V(void) const {
    return _size;
}

// Get the number of edges in the graph
int Graph::E(void) const {
    int num_edges = 0;
    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            if (graph[i][j] >= 0) ++num_edges;
        }
    }
    return num_edges;
}

/**
 * Check if there exists an edge between given vertices
 * 
 * @param x Verticle
 * @param y Verticle
 * @return True or False if edge exists
 */
bool Graph::adjacent(int x, int y) const {
    if ((x >= _size) || (y >= _size)){
        cout << "Values outside of size";
        return 0;
    }
    return graph[x][y] >= 0;
}

/**
 * Get the neighbors of given verticle
 * 
 * @param x Verticle
 * @return Vector with verticles that can be reached from x
 */
vector<int> Graph::neighbors(int x) const {
    vector<int> ngb;
    if (x >= _size){
        cout << "Values outside of size";
        return ngb;
    }

    for (int j = 0; j < _size; ++j) {
        if ((graph[x][j] > 0) && (x != j)) {
            ngb.push_back(j);
        }
    }
    return ngb;
}

// Add an edge from x to y if it doesn't exist
void Graph::add(int x, int y, int dist) {
    if ((x >= _size) || (y >= _size)) {
        cout << "Values outside of size";
        return;
    }

    if (graph[x][y] >= 0) return;

    if (dist < 0) {
        dist = _min_dist + rand() % (_max_dist - _min_dist + 1); // Random distance in given range
    }

    set_edge_value(x, y, min(max(dist, _min_dist), _max_dist));
    return;
}

// Remove the edge from x to y
void Graph::del(int x, int y) {
    if ((x >= _size) || (y >= _size)){
        cout << "Values outside of size";
        return;
    }

    graph[x][y] = -1;
    return;
}

// Get the distance (edge value) from x to y.
int Graph::get_edge_value(int x, int y) const {
    if ((x >= _size) || (y >= _size)){
        cout << "Values outside of size";
        return -1;
    }
    return graph[x][y];
}

// Set the edge value from x to y.
void Graph::set_edge_value(int x, int y, int v) {
    if ((x >= _size) || (y >= _size)){
        cout << "Values outside of size";
        return;
    }

    graph[x][y] = v;
    return;
}

// Print graph matrix
void Graph::print(void) const {
    cout << "Graph:\n";

    for (int i = 0; i < _size; ++i){
        cout << i << " | ";
        for (int j = 0; j < _size; ++j){
            cout << setw(4) << graph[i][j];
            if (j < _size - 1) {
                cout << ", ";
            } else {
                cout << endl;
            }
        }
    }
}