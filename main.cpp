#include "libraries/Parser.h"
#include "libraries/search_algos.h"

int main() {
    string file_loc = "";
    Graph* curr_graph = NULL;
    cust_lib::search_algos search_obj;

    while (true) {
        cout << "Enter the location of the dataset, or type 'default' for default dataset(dataset/1987.csv): ";
        cin >> file_loc;
        if (file_loc == "default") {
            file_loc = "dataset/1987.csv";
        }
        cust_lib::Parser m_parser(file_loc);

        if((curr_graph = m_parser.read_file()) == NULL) {
            cout << "INVALID FILE LOCATION! Please input a valid string\n" << endl;
        } else {
            break;
        }
    }

    cout << "Successfully read file! (Errors printed to console if any)" << endl;
    cout << "\n/***********************************************/\n" << endl;

    int opt_code = 0;
    string args;
    while (true) {
        cout << "Please choose one of the following: " << endl;
        cout << "Enter '1': Shortest Flight route from Point A to Point B. (Using Dijkstra's Algorithm)" << endl;
        cout << "Enter '2': Shortest Flight route from Point A to Point B through Point C. (Using Landmark Path and A* search)" << endl;
        cout << "Enter '3': To find a path from Point A to Point B (Using BFS - may not be the shortest). " << endl;
        
        cin >> args;
        try {
            opt_code = std::stoi(args);
            if (opt_code > 3 || opt_code < 1) {
                cout << "Error: Invalid opt_code.  Please choose between option 1 to 3. \n" << endl;
                continue;
            } else {
                break;
            }
        } catch(exception& e) {
            cout << "Error: Invalid input. Please enter a number. \n" << endl;
        }
    }

    switch (opt_code) {
        case 1: {
            Vertex source, destination;
            while (true) {
                cout << "Please enter the source airport: ";
                cin >> source;
                cout << endl;

                if (!curr_graph->vertexExists(source)) {
                    cout << "INVALID AIRPORT! Try again!. " << endl;
                    continue;
                }

                cout << "Please enter the destination airport: ";
                cin >> destination;
                cout << endl;

                if (!curr_graph->vertexExists(destination)) {
                    cout << "INVALID AIRPORT! Try again!. " << endl;
                    continue;
                }

                break;
            }

            vector<Vertex> shortest_path = search_obj.search(curr_graph, source, destination, true);
            break;
        }

        case 2: {
            Vertex source, destination, landmark;
            while (true) {
                cout << "Please enter the source airport: ";
                cin >> source;
                cout << endl;

                if (!curr_graph->vertexExists(source)) {
                    cout << "INVALID AIRPORT! Try again!. " << endl;
                    continue;
                }

                cout << "Please enter the landmark airport: ";
                cin >> source;
                cout << endl;

                if (!curr_graph->vertexExists(landmark)) {
                    cout << "INVALID AIRPORT! Try again!. " << endl;
                    continue;
                }

                cout << "Please enter the destination airport: ";
                cin >> destination;
                cout << endl;

                if (!curr_graph->vertexExists(destination)) {
                    cout << "INVALID AIRPORT! Try again!. " << endl;
                    continue;
                }

                break;
            }

            vector<Vertex> landmark_path = search_obj.landmark_search(curr_graph, source, landmark, destination);
            break;
        }

        case 3: {
            Vertex source, destination;
            while (true) {
                cout << "Please enter the source airport: ";
                cin >> source;
                cout << endl;

                if (!curr_graph->vertexExists(source)) {
                    cout << "INVALID AIRPORT! Try again!. " << endl;
                    continue;
                }

                cout << "Please enter the destination airport: ";
                cin >> destination;
                cout << endl;

                if (!curr_graph->vertexExists(destination)) {
                    cout << "INVALID AIRPORT! Try again!. " << endl;
                    continue;
                }

                break;
            }

            vector<Vertex> bfs_path = search_obj.BFS(curr_graph, source, destination);
            break;
        }
    }

    cout << "Successfully ending program" << endl;

    delete curr_graph;
    return 0;
}