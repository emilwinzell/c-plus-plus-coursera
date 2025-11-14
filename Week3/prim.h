#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include "Graph.h"

class TreeNode
{
public:
    int data;
    TreeNode *firstChild = nullptr;
    TreeNode *nextSibling = nullptr;

    TreeNode(int data)
    {
        this->data = data;
    }
};

struct queueElem {
    int origin;
    int target;
    int priority;
};

struct cmp {
    bool operator()(const queueElem &e1, const queueElem &e2) const { return e1.priority > e2.priority; }
};

/*
* SHORTEST PATH
* Calculate the shortest path in any given graph.
*
* @param graph Address of the target graph.
*/
class PrimsMST
{
public:
    PrimsMST(const Graph &graph) : _gr(graph) {}

    void find_mst(int start_node);

private:

    const Graph &_gr;            // The graph.
    std::priority_queue<queueElem, std::vector<queueElem>, cmp> unexplored; // Set of all vertices to visit
    set<int> explored;         // Empty set of visited vertices.

};

void PrimsMST::find_mst(int start_node) {
    cout << "Calculating MST from node " << start_node << std::endl;
    int size = _gr.V();
    if ((start_node < 0) || (start_node >= size)) {
        return;
    }
    int total_cost = 0;
    vector<queueElem> tree;
    queueElem current_edge;
    unexplored.push(queueElem{-1, start_node, 0}); // Add start node with 0 cost

    while (!unexplored.empty()) {
        // Get next edge in priority
        current_edge = unexplored.top();
        unexplored.pop();
        if (explored.find(current_edge.target) != explored.end())
            continue; // Already explored

        // Add all unexplored neighbors
        vector<int> ngb = _gr.neighbors(current_edge.target);
        for (int n : ngb) {
            if (explored.find(n) != explored.end())
                continue; // Already explored

            queueElem new_element{
                current_edge.target, n,
                _gr.get_edge_value(current_edge.target, n)
            };
            unexplored.push(new_element);
        }

        // Add edge
        tree.push_back(current_edge);
        if ((current_edge.origin >= 0) && (current_edge.target >= 0))
            total_cost += _gr.get_edge_value(current_edge.origin, current_edge.target);
        explored.insert(current_edge.target);
    }

    cout << "EDGES: (-1 = start)" << std::endl;
    for (queueElem edge : tree) {
        if (edge.origin >= 0)
            cout << edge.origin << " -> " << edge.target << " Cost: " << _gr.get_edge_value(edge.origin, edge.target) << std::endl;
    }

    cout << "TOTAL COST: " << total_cost << std::endl;
}