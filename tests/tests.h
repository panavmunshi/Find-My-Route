#include "../libraries/parser.h"
#include "../libraries/search_algos.h"

namespace cust_lib {
    class test_cases {
        public:

            /* Checks the number of vertices present in the graph. */
            static bool test_vertices(Graph* obj);

            /** 
             * Runs bfs vs dijkstra.
             * This compares quite a few things, i.e.
             * 1) If bfs path length is lesser than or equal to dijkstra path length (condition imposed by bfs)
             * 2) If dijkstra total distance is lesser than or equal to bfs dist (condition imposed by dijkstra).
             */
            static bool test_dijkstra_v_bfs(Graph* obj);
            
            /**
             * Checks if the output by both a* and dijkstra is the same (both should be the same as they find the shortest path)
             */ 
            static bool test_dijkstra_v_a_star(Graph* obj);
    };
}