#include "tests.h"
using namespace cust_lib;

void test_cases::test_graph(Graph* test_obj) {
    /* Run test cases. */
    vector<Vertex> adjacent_nodes = test_obj->getAdjacent("SAV");

    for (const Vertex& vert : adjacent_nodes) {
        cout << vert << endl;
    }
}

void test_cases::test_heuristic(Graph* test_obj) {
    vector<Vertex> vertice_list = test_obj->getVertices();

    for (Vertex v : vertice_list) {
        int return_val = test_obj->get_edge_count("SFO", v);

        if (return_val != INT_MAX) {
            cout << "From: " << v << " To: " << "SFO" << " Edges: " << return_val << endl;
            //cout << v << endl;
            
        }
    }

}

void test_cases::test_vertex(Graph* test_obj) {
    vector<Vertex> vertice_list = test_obj->getVertices();

    for (Vertex v : vertice_list) {
        cout << v << endl;
    }

}

void test_cases::print_graph(Graph* test_obj) {
    test_obj->print();
}

void test_cases::test_a_star(Graph* test_obj) {
    search_algos search_obj;

    vector<Vertex> result = search_obj.search(test_obj, "PIH", "ATW", false);

    for (Vertex v : result) {
        cout << v << " -> ";
    }
    cout << endl;
}

int main() {
    string loc = "dataset/1987.csv";

    Parser curr_parser(loc);
    Graph* search_obj = curr_parser.read_file();

    /*printf("Testing Vertices. \n");
    test_cases::test_vertex();*/

    /*printf("Testing heuristics. \n");
    test_cases::test_heuristic();*/
    //test_cases::test_graph();
    //test_cases::print_graph();

    printf("Testing A star\n");
    test_cases::test_a_star(search_obj);

    /*printf("Testing heuristics. \n");
    test_cases::test_heuristic(search_obj);*/

    delete search_obj;
    return 0;
}