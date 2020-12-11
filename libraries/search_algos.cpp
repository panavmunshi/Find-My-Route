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