#include <cstdlib>
#include <vector>
using namespace std;

/**
 *  GRAPH
 *  This graph implementation uses a matrix, with the distance included
 *  graph[u][v] = -1 Means that there is no edge from u to v.
 *  If there is an edge with distance x: graph[u][v] = x
 */
class Graph {
    public:
        Graph(int size, int min_dist, int max_dist, double density) {
            _size = size;
            _min_dist = min_dist;
            _max_dist = max_dist;
            _density = min(max(density, 0.0), 1.0) * 100; // Limit density to range [0,1]

            // initialize graph
            graph = new int*[_size];
            for (int i = 0; i < _size; ++i) {
                graph[i] = new int [_size];
            }
            // fill with numbers
            _generate_graph();
        }

        ~Graph(){
            for (int i = 0; i < _size; ++i){
                delete graph[i];
            }
            delete graph;
        }

        int V(void) const; // returns the number of vertices in the graph
        int E(void) const; // returns the number of edges in the graph
        bool adjacent(int x, int y) const; //tests whether there is an edge from node x to node y.
        vector<int> neighbors(int x) const;       // lists all nodes y such that there is an edge from x to y.
        void add(int x, int y, int dist = -1); // adds to G the edge from x to y, if it is not there.
        void del(int x, int y);            //removes the edge from x to y, if it is there
        int get_edge_value(int x, int y) const;  // returns the value associated to the edge (x,y).
        void set_edge_value(int x, int y, int v); // sets the value associated to the edge (x,y) to v.
        void print(void) const;

    private:
        int _size, _min_dist, _max_dist;
        double _density;
        int **graph;

        void _generate_graph() {
            int value;
            for (int i = 0; i < _size; ++i)
            {
                for (int j = i; j < _size; ++j) {
                    if (i == j) {
                        graph[i][j] = -1;  // No loops
                        continue;
                    }
                    if (_density > rand() % 101) {
                        value = _min_dist + rand() % (_max_dist - _min_dist + 1);  // Random distance in given range
                    } else {
                        value = -1;
                    }
                    // All edges are bi-directional
                    graph[i][j] = value;
                    graph[j][i] = value;
                }
            }
        }

};