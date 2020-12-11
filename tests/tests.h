#include "../libraries/parser.h"
#include "../libraries/search_algos.h"

namespace cust_lib {
    class test_cases {
        public:
            static void test_graph(Graph* obj);
            static void test_heuristic(Graph* obj);
            static void test_vertex(Graph* obj);
            static void print_graph(Graph* obj);
            static void test_a_star(Graph* obj);
    };
}