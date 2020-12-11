#pragma once
#include "graph.h"
#include "vector"

namespace cust_lib {
    class search_algos {
        public:
            static vector<Edge> a_star_search(Graph* search_graph, Vertex source, Vertex destination);
        private:
            static vector<Edge> reconstruct_path(Vertex came_from, Vertex current);
    };
}
