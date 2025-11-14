#include <iostream>
#include <vector>
#include <ctime>
#include "djikstra.h"

// Set the example graph from lecture
void set_example_graph(Graph * gr){
    int new_gr[9][9] = {
        {-1,  4,  3, -1,  7, -1, -1, -1, -1},
        {4,  -1, -1,  1, -1, -1, -1, -1, -1},
        {3,  -1, -1, -1,  4, -1, -1, -1, -1},
        {-1,  1, -1, -1,  3,  1, -1, -1, -1},
        {7,  -1,  4, -1, -1,  1,  5, -1,  3},
        {-1, -1, -1,  1,  1, -1, -1,  2,  4},
        {-1, -1, -1, -1,  5, -1, -1, -1,  5},
        {-1, -1, -1, -1, -1,  2, -1, -1,  3},
        {-1, -1, -1, -1,  3,  4,  5,  3, -1}
    };
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            gr->set_edge_value(i, j, new_gr[i][j]);
        }
    }
}

// test the priority queue
void test_queue(void) {
    PQueueElement<int> elem0{0, 5};
    PQueueElement<int> elem1{1, 3};
    PQueueElement<int> elem2{2, 2};

    PriorityQueue<int> pq;
    pq.insert(&elem0);
    pq.print();
    pq.insert(&elem1);
    pq.print();
    pq.insert(&elem2);
    pq.print();
    pq.chgPriority(&elem2, 8);
    pq.print();
    pq.chgPriority(&elem2, 1);
    pq.print();
    pq.chgPriority(&elem1, 9);
    pq.print();
}

// Test find one path
void test_find_path(Graph gr) {
    gr.print();

    ShortestPath sp{gr};
    vector<int> res = sp.path(0, 8);
    for (int i : res)
        std::cout << i << " -> ";
    std::cout << endl;
}

int main() {
    srand(time(0));
    const int graph_size = 50;
    Graph gr{graph_size, 1, 10, 0.2};

    // Some tests..
    // set_example_graph(&gr);
    // test_queue();
    // test_find_path(gr);

    // Calculate avg path for all 50 vertices of generated graph
    ShortestPath sp{gr};
    double avg_path = 0.0;
    cout << "Choose a starting verticle, from 0 to " << graph_size << ": ";
    int start;
    cin >> start;
    int this_path;
    cout << "Shortest path length from -> to" << endl;
    for (int i = 0; i < graph_size; ++i)
    {
        this_path = sp.path_size(start, i);
        avg_path += static_cast<double>(this_path) / (graph_size - 1);
        cout << start << " -> " << i << " : " << this_path << endl;
    }
    cout << "Average path length " << avg_path << endl;
}