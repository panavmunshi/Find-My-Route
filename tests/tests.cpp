#include "tests.h"
using namespace cust_lib;
using namespace std::chrono;

bool test_cases::test_vertices(Graph* search_obj) {
    /* Number of Vertices in dataset/1987.csv. Calculated in excel. */
    int num_vertices = 238;
    vector<Vertex> vertices = search_obj->getVertices();
    return vertices.size() == num_vertices;
}

bool test_cases::test_dijksta_v_bfs(Graph* search_obj) {
    search_algos obj;

    vector<Vertex> first_d = obj.search(search_obj, "CMI", "ATL", true);
    vector<Vertex> first_b = obj.BFS(search_obj, "CMI", "ATL");

    vector<Vertex> second_d = obj.search(search_obj, "CMI", "TEX", true);
    vector<Vertex> second_b = obj.search(search_obj, "CMI", "TEX", true);

    bool edge_com_f = first_b.size() <= first_d.size();
    bool edge_com_s = second_b.size() <= second_d.size();

    int b_dist_f = 0, b_dist_s = 0, d_dist_f = 0, d_dist_s = 0;

    for (size_t i = 1; i < first_d.size(); i++) {
        d_dist_f += search_obj->getEdgeWeight(first_d[i - 1], first_d[i]);
    }

    for (size_t i = 1; i < second_d.size(); i++) {
        d_dist_s += search_obj->getEdgeWeight(second_d[i - 1], second_d[i]);
    }

    for (size_t i = 1; i < first_b.size(); i++) {
        b_dist_f += search_obj->getEdgeWeight(first_b[i - 1], first_b[i]);
    }

    for (size_t i = 1; i < second_b.size(); i++) {
        b_dist_s += search_obj->getEdgeWeight(second_b[i - 1], second_b[i]);
    }

    bool dist_comp_f = d_dist_f <= b_dist_f;
    bool dist_comp_s = d_dist_s <= b_dist_s;

    return edge_com_f && edge_com_s && dist_comp_f && dist_comp_f;
}

int main() {
    string loc = "dataset/1987.csv";
    Parser curr_parser(loc);
    Graph* search_obj = curr_parser.read_file();
    
    cout << "Testing test_vertices.." << endl;
    bool test_v = test_cases::test_vertices(search_obj);

    if (test_v) {
        cout << "Passed test_vertices" << endl;
    } else {
        cout << "Failed test_vertices" << endl;
    }

    cout << "Testing test_dijksta_v_bfs.." << endl;
    bool test_d = test_cases::test_dijksta_v_bfs(search_obj);

    cout << endl;
    if (test_d) {
        cout << "Passed test_dijksta_v_bfs" << endl;
    } else {
        cout << "Failed test_dijksta_v_bfs" << endl;
    }

    delete search_obj;
    return 0;
}