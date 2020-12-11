#include "tests.h"
using namespace cust_lib;

void test_cases::test_graph() {
    string loc = "dataset/1987.csv";

    Parser curr_parser(loc);
    Graph* test_obj = curr_parser.read_file();


    /* Run test cases. */
    vector<Vertex> adjacent_nodes = test_obj->getAdjacent("SAV");

    for (const Vertex& vert : adjacent_nodes) {
        cout << vert << endl;
    }
}

void test_cases::test_heuristic() {
    string loc = "dataset/1987.csv";

    Parser curr_parser(loc);
    Graph* test_obj = curr_parser.read_file();

    vector<Vertex> vertice_list = test_obj->getVertices();

    for (Vertex v : vertice_list) {
        int return_val = test_obj->get_edge_count("SAV", v);

        if (return_val != INT_MAX) {
            //cout << "From: " << v << " To: " << "SAV" << " Edges: " << return_val << endl;
            cout << v << endl;
            
        }
    }

}

void test_cases::test_vertex() {
    string loc = "dataset/1987.csv";

    Parser curr_parser(loc);
    Graph* test_obj = curr_parser.read_file();

    vector<Vertex> vertice_list = test_obj->getVertices();

    for (Vertex v : vertice_list) {
        cout << v << endl;
    }

}

void test_cases::print_graph() {
    string loc = "dataset/1987.csv";

    Parser curr_parser(loc);
    Graph* test_obj = curr_parser.read_file();

    test_obj->print();
}

int main() {
    printf("Testing Vertices. \n");
    test_cases::test_vertex();

    printf("Testing heuristics. \n");
    test_cases::test_heuristic();
    //test_cases::test_graph();
    //test_cases::print_graph();

    return 0;
}