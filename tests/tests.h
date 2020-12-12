#include "../libraries/parser.h"
#include "../libraries/search_algos.h"
#include <chrono>
#include <algorithm>

namespace cust_lib {
    class test_cases {
        public:

            /* Checks the number of vertices present in the graph. */
            static bool test_vertices(Graph* obj);

            /* Runs bfs vs dijkstra. */
            static bool test_dijksta_v_bfs(Graph* obj);
    };
}