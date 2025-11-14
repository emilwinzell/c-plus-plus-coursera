#include <iostream>
#include <vector>
#include <set>
#include <map>
#include "Graph.h"

const int MAX_ITER = 10000;

/*
* Priority Queue Element
*
* Element of the priority queue.
*
*/
template <typename T>
class PQueueElement{
    public:
        PQueueElement(const T &value, int priority, PQueueElement<T>* next_element = nullptr, PQueueElement<T>* prev_element = nullptr)
            : elem(value), prio(priority), next(next_element), prev(prev_element) {}

        void chgPrio(int new_prio) {prio = new_prio;}
        PQueueElement<T> *getNext(void) {return next;}
        PQueueElement<T> *getPrev(void) {return prev;}
        int getPrio(void) {return prio;}
        T getValue(void) { return elem; }
        void setPred(T value) { predecessor = value; };
        T getPred(void) { return predecessor; };

        bool setNext(PQueueElement<T> *new_next);
        bool setPrev(PQueueElement<T> *new_prev);
        

    private:
        T elem;
        int prio;
        PQueueElement<T> *next;
        PQueueElement<T> *prev;
        T predecessor;
};

// Set link to next element in queue.
template <typename T>
bool PQueueElement<T>::setNext(PQueueElement<T> *new_next)
{
    // Next in queue must have a higher priority number
    if (new_next == nullptr || new_next->getPrio() >= prio)
    {
        next = new_next;
        return true;
    }
    else
    {
        return false;
    }
}

// Set link to previous element in queue.
template <typename T>
bool PQueueElement<T>::setPrev(PQueueElement<T> *new_prev)
{
    // Prev in queue must have a lower priority number
    if (new_prev == nullptr || new_prev->getPrio() <= prio)
    {
        prev = new_prev;
        return true;
    }
    else
    {
        return false;
    }
}

/* ----- PRIORITY QUEUE --------
*
* Queue were elements are ordered based on priority, from lowest to highest
*
*/
template <typename T>
class PriorityQueue{
    public:
        PriorityQueue(){
            _size = 0;
            _cursor = nullptr;
            _top = nullptr;
        }
        int size(void) { return _size; }
        PQueueElement<T> *top(void) { return _top; };

        void insert(PQueueElement<T>* queue_element);
        PQueueElement<T> *pop(void);
        void chgPriority(PQueueElement<T> *queue_element, int new_prio);
        PQueueElement<T> *contains(T value);
        void print(void);

    private:
        int _size;
        PQueueElement<T> *_cursor;
        PQueueElement<T> *_top;
};

/**
* Insert an element in the queue. Element will be placed based on its priority.
*
* @param queue_element Pointer to the element.
*/
template <typename T>
void PriorityQueue<T>::insert(PQueueElement<T> *queue_element)
{
    if (_size == 0)
    {
        _top = queue_element;
        _cursor = queue_element;
        _size = 1;
        return;
    }
    int index = 0;
    int this_prio = queue_element->getPrio();
    _cursor = _top; // Point at top of queue
    PQueueElement<T> *_prev_cursor = nullptr;
    while (_cursor != nullptr)
    {   
        if (index >= _size) {
            cout << "Warning: Queue longer than size";
            break;
        }
        if (_cursor->getPrio() <= this_prio)
        {
            _prev_cursor = _cursor;
            _cursor = _cursor->getNext(); // Next element in queue
            index++;
        }
        else
            break;
    }

    bool res;
    res = queue_element->setPrev(_prev_cursor);
    if (!res)
    {
        cout << "Failed to insert element" << endl;
        return;
    }
    res = queue_element->setNext(_cursor);
    if (!res)
    {
        cout << "Failed to insert element" << endl;
        return;
    }
    if (_prev_cursor == nullptr)
    {
        _top = queue_element; // New top element of queue
    }
    else
    {
        _prev_cursor->setNext(queue_element);
    }
    if (_cursor != nullptr)
    {
        _cursor->setPrev(queue_element);
    }
    _size++;
}

/**
* Pop the top element from the queue and return its pointer.
*
* @return Pointer to the element, nullptr if queue is empty.
*/
template <typename T>
PQueueElement<T> *PriorityQueue<T>::pop()
{   
    if (_size == 0) {
        return nullptr;
    }
    _cursor = _top;
    _top = _cursor->getNext(); // the next in queue is now the top
    if (_top != nullptr) {
        _top->setPrev(nullptr);
    }
    --_size;
    _cursor->setNext(nullptr);  // Unlink the popped element
    _cursor->setPrev(nullptr);
    return _cursor;
}


/**
* Check if the queue holds an element with given value.
*
* @param value The value.
* @return Pointer to the element, nullptr if not found.
*/
template <typename T>
PQueueElement<T> *PriorityQueue<T>::contains(T value)
{
    if (_size == 0){
        return nullptr;
    }
    int index = 0;
    _cursor = _top;
    while (_cursor != nullptr)
    {
        if (index >= _size) {
            cout << "Warning: Queue longer than size";
            break;
        }
        if (_cursor->getValue() == value) {
            break;
        }
        _cursor = _cursor->getNext(); // Next element in queue
        index++;
    }
    return _cursor;
}

/**
* Change the priority of a element in the queue
*
* @param queue_element Pointer to the queue element. 
* @param new_prio The new priority number.
*/
template <typename T>
void PriorityQueue<T>::chgPriority(PQueueElement<T> *queue_element, int new_prio)
{   
    if (queue_element == nullptr or _size == 0)
        return;
    if (_size == 1) {
        queue_element->chgPrio(new_prio);
        return;
    }
    PQueueElement<T> *mod;
    mod = queue_element->getPrev();
    if (mod != nullptr)
        mod->setNext(queue_element->getNext());
    else
        _top = queue_element->getNext();  // We have modified the top element

    mod = queue_element->getNext();
    if (mod != nullptr)
        mod->setPrev(queue_element->getPrev());

    queue_element->setPrev(nullptr);
    queue_element->setNext(nullptr);
    queue_element->chgPrio(new_prio);
    insert(queue_element);
}

/**
* Iterate through the queue and print the contents of the elements.
*/
template <typename T>
void PriorityQueue<T>::print(void)
{
    _cursor = _top; // Point at top of queue
    int index = 0;
    std::cout << "top -> ";
    while (_cursor != nullptr)
    {
        if (index >= _size){
            cout << "Warning: Queue longer than size";
            break;
        }  
        std::cout << "[ " << _cursor->getValue() << " | " << _cursor->getPrio() << " ] -> ";
        _cursor = _cursor->getNext(); // Next element in queue
        index++;
    }
    std::cout << std::endl;
}


/*
* SHORTEST PATH
* Calculate the shortest path in any given graph.
*
* @param graph Address of the target graph.
*/
class ShortestPath{
    public:
        ShortestPath(const Graph& graph):_gr(graph){}
        vector<int> path(int u, int w);
        int path_size(int u, int w);

    private:
        const Graph& _gr;  // The graph.
        PriorityQueue<int> open_set; // Open set of vertices to visit
        set<int> closed_set; // Closed set of visited vertices.
        map<int, int> path_map; // Holds visited vertices and their preceeding verticle.

        void _add_to_open_set(int val, int current_cost) {
            vector<int> ngb = _gr.neighbors(val);
            PQueueElement<int> *elem;
            int new_cost;
            for (int n : ngb){
                if (closed_set.find(n) != closed_set.end())
                    continue; // Already in closed set
                new_cost = current_cost + _gr.get_edge_value(val, n);

                // If an element with value n present, update the priority
                elem = open_set.contains(n);
                if (elem == nullptr) {
                    elem = new PQueueElement<int>{n, new_cost};
                    open_set.insert(elem);
                } else {
                    if (new_cost < elem->getPrio())
                        open_set.chgPriority(elem, new_cost);
                }
                elem->setPred(val);  // Keep track of visitied verticies
            }
        };

        vector<int> _backtrack_path(int start, int stop){
            vector<int> path = {stop};
            int this_elem = stop;
            for (int i = 0; i < _gr.V(); ++i){
                path.insert(path.begin(), path_map[this_elem]);
                this_elem = path_map[this_elem];
                if (this_elem == start)
                    break;
            }
            return path;
        };
};

/**
* Calculate the shortest path in the graph.
*
* @param start The value of the starting point in the graph. 
* @param stop The value of the stopping point.
* @return Vector holding the values of the vertices on the shortest path.
*/
vector<int> ShortestPath::path(int start, int stop) {
    path_size(start, stop);
    return _backtrack_path(start, stop);
}


/**
* Calculate the length for the shortest path in the graph
*
* @param start The value of the starting point in the graph. 
* @param stop The value of the stopping point.
* @return The total length of the shortest path from start to stop.
*/
int ShortestPath::path_size(int start, int stop) {
    if (start == stop) {
        return 0;
    }
    closed_set = {start};
    PQueueElement<int> *elem;
    int val;
    int psize;

    // Create queue elements and and to priority queue
    _add_to_open_set(start, 0);

    for (int iter = 0; iter < MAX_ITER; ++iter)
    {
        //cout << "iter " << iter << ", open set is: " << endl;
        //open_set.print();
        elem = open_set.pop(); // Pop next element
        if (elem == nullptr) {
            return -1;  // No path found
        }
        val = elem->getValue();
        if (closed_set.find(val) != closed_set.end()){
            // Element already in closed set
            delete elem;
            continue;
        }
        path_map[val] = elem->getPred(); // Store taken path
        closed_set.insert(val);                 // Add to closed set
        _add_to_open_set(val, elem->getPrio()); // Add new neighbors
        if (closed_set.find(stop) == closed_set.end())  // Continue until stop is in the closed set
            delete elem;  // Make sure popped elements are deleted from memory
        else
            break;
    }
    psize = elem->getPrio();
    delete elem;
    return psize;
}