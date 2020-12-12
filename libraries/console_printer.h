#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include "graph.h"

using namespace std;

string gen_arrow(size_t space, size_t arrow_size) {
    stringstream ss;
    ss << string(space, ' ') << string(arrow_size - 1, '-') << '>' << string(space, ' ');
    return ss.str();
}

void print_formatted(Graph* graph, vector<Vertex>& toPrint) {
    if (toPrint.size() <= 1) {
        cout << "Path between the choice of your airports doesn't exist. " << endl;
        return;
    }
    
    size_t largest_len = 0;
    vector<vector<string>> print_data;
    print_data.push_back(vector<string>());

    for (Vertex v : toPrint) {
        print_data[0].push_back(v);
    }

    for (size_t idx = 1; idx < toPrint.size(); idx++) {
        Edge flight_edge = graph->getEdge(toPrint[idx - 1], toPrint[idx]);
        size_t num_flights = flight_edge.flight_details.size();
        bool is_less = false;
        if (print_data.size() - 1 < num_flights) {
            int delta = num_flights - (print_data.size() - 1);
            while (delta-- > 0) {
                print_data.push_back(vector<string>());
            }
        } else if (print_data.size() - 1 > num_flights) {
            is_less = true;
        }

        auto it = flight_edge.flight_details.begin();
        for (size_t i = 0; i < num_flights; i++) {
            stringstream dept, arr;
            dept << setfill('0') << setw(4) << it->second.first;
            arr << setfill('0') << setw(4) << it->second.second;

            string flight_detail = it->first + " -> Dep: " + dept.str() + "hrs" + " - Arr: " + arr.str() + "hrs";
            size_t flight_len = flight_detail.length();
            largest_len = flight_len > largest_len ? flight_len : largest_len;
            ++it;
            print_data[i + 1].push_back(flight_detail);
        }

        if (is_less) {
            for (size_t i = num_flights; i < print_data.size() - 1; i++) {
                print_data[i + 1].push_back("");
            }
        }
    }

    for (size_t prt = 0; prt < print_data.size(); prt++) {
        if (prt == 0) {
            vector<string>& airports = print_data[0];
            for (size_t idx = 0; idx < airports.size() - 1; idx++) {
                cout << airports[idx] << gen_arrow(3, largest_len);
            }
            cout << airports[airports.size() - 1] << endl;
        } else {
            vector<string>& flight_det = print_data[prt];
            cout << setfill(' ') << setw(5 + largest_len);
            for (size_t idx = 0; idx < flight_det.size() - 1; idx++) {
                cout << flight_det[idx] << setfill(' ') << setw(9 + largest_len);
            }
            cout << flight_det[flight_det.size() - 1];
            cout << endl;
        }
    }
}