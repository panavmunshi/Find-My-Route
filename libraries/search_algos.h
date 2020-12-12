#pragma once
#include "graph.h"
#include <vector>
#include <queue>
#include <stack>

namespace cust_lib {
    class search_algos {
        public:
            vector<Vertex> search(Graph* search_graph, Vertex source, Vertex destination, bool isDijkstra);
            vector<Vertex> BFS(Graph* search_graph, Vertex source, Vertex dest);
        private:
            int calc_heuristic(Graph* graph, Vertex A, Vertex B);
            struct search_p_queue {
                typedef std::pair<int, Vertex> node_elem;
                
                std::priority_queue<node_elem, std::vector<node_elem>, std::greater<node_elem>> node_queue;

                inline bool empty() const {
                    return node_queue.empty();
                }

                inline void put(Vertex item, int priority) {
                    node_queue.emplace(priority, item);
                }

                Vertex get() {
                    Vertex toReturn = node_queue.top().second;
                    node_queue.pop();
                    return toReturn;
                }
            };
    };
}
