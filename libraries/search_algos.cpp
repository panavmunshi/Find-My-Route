#include "search_algos.h"

using namespace cust_lib;
using namespace std;

vector<Vertex> search_algos::search(Graph* search_graph, Vertex source, Vertex destination, bool isDijkstra) {
    search_p_queue frontier;
    frontier.put(source, 0);

    std::unordered_map<Vertex, Vertex> parentToChildMap;
    std::unordered_map<Vertex, int> vertexToCost;
    std::vector<Vertex> toReturn;

    parentToChildMap[source] = "NULL";
    vertexToCost[source] = 0;

    while (!frontier.empty()) {
        Vertex curr = frontier.get();
        if (curr == destination) {
            break;
        } else {
            for (Vertex next : search_graph->getAdjacent(curr)) {
                int new_cost = vertexToCost[curr] + search_graph->getEdgeWeight(curr, next);
                if (vertexToCost.find(next) == vertexToCost.end() || new_cost < vertexToCost[next]) {
                    vertexToCost[next] = new_cost;
                    int priority = (isDijkstra) ? new_cost : new_cost + calc_heuristic(search_graph, source, destination);
                    frontier.put(next, priority);
                    parentToChildMap[next] = curr;
                }
            }
        }
    }

    std::stack<Vertex> reversal_stack;
    Vertex current = destination;

    while (current != "NULL") {
        reversal_stack.push(current);
        if (parentToChildMap.find(current) == parentToChildMap.end()) {
            return vector<Vertex>();
        }
        current = parentToChildMap[current];
    }

    while (!reversal_stack.empty()) {
        toReturn.push_back(reversal_stack.top());
        reversal_stack.pop();
    }
    return toReturn;
}

int search_algos::calc_heuristic(Graph* graph, Vertex A, Vertex B) {
    return graph->get_edge_count(A, B);
}

vector<Vertex> search_algos::BFS(Graph* search_obj, Vertex source, Vertex dest)
{
    unordered_map<Vertex, bool> isVisited;
    unordered_map<Vertex, Vertex> came_from;
    vector<Vertex> vertex_list = search_obj->getVertices();
    vector<Vertex> toReturn;

    for (Vertex v : vertex_list) {
        isVisited[v] = false;
    }

    queue<Vertex> queue; // for BFS
 
    isVisited[source] = true;
    came_from[source] = "NONE";

    queue.push(source); //enqueue node

    while(queue.empty() == false){
        Vertex curr = queue.front();
        queue.pop(); // 
        cout << "Node right now: " << curr << endl;
        if (curr == dest) {
            break;
        }

        vector<Vertex> adjacent_list = search_obj->getAdjacent(curr);
        for (Vertex q : adjacent_list) {
            if (!isVisited[q]) {
                cout << "Neighbour " << q << endl;
                isVisited[q] = true;
                came_from[q] = curr;
                queue.push(q);
            }
        }
    }

    std::stack<Vertex> reversal_stack;
    Vertex current = dest;

    while (current != "NONE") {
        reversal_stack.push(current);
        if (came_from.find(current) == came_from.end()) {
            return vector<Vertex>();
        }
        current = came_from[current];
    }

    while (!reversal_stack.empty()) {
        toReturn.push_back(reversal_stack.top());
        reversal_stack.pop();
    }
    return toReturn;
}

vector<Vertex> search_algos::landmark_search(Graph* search_graph, Vertex source, Vertex landmark, Vertex destination) {
    vector<Vertex> toReturn;
    vector<Vertex> a_to_b = search(search_graph, source, landmark, false);
    if (a_to_b.empty()) {
        return toReturn;
    }

    vector<Vertex> b_to_c = search(search_graph, landmark, destination, false);
    if (b_to_c.empty()) {
        return toReturn;
    }

    toReturn.push_back(source);
    for (Vertex v : a_to_b) {
        if (v != source && v != landmark) {
            toReturn.push_back(v);
        }
    }

    toReturn.push_back(landmark);
    for (Vertex q : b_to_c) {
        if (q != landmark && q != destination) {
            toReturn.push_back(q);
        }
    }

    toReturn.push_back(destination);
    return toReturn;
}