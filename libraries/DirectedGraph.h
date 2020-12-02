#pragma once

#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

typedef string Vertex;
typedef struct graph_edge {
    graph_edge(int d, int dt, int at, string fd) : dist(d), dept_time(dt), arr_time(at), flight_data(fd) { }
    int dist;
    int dept_time;
    int arr_time;
    string flight_data;
} Edge;

namespace cust_lib {
    class DirectedGraph {
        public:
            bool adjacent (Vertex source, Vertex dest);
            vector<Vertex> neighbours(Vertex source);
            void add_vertex(Vertex toAdd);
            void remove_vertex(Vertex toRemove);
            void add_edge(Vertex source, Vertex dest, Edge* edge);
            vector<Edge*> get_edges(Vertex source, Vertex dest);
        private:
            /* To-Do. */
    };
};