#include "libraries/Parser.h"

int main() {
    string file_loc = "";
    Graph* curr_graph = NULL;
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
        cout << "Enter '1': Shortest Flight route from Point A to Point B" << endl;
        cout << "Enter '2': Shortest Flight route from Point A to Point B with constraints" << endl;
        cout << "Enter '3': ~ To be filled for BFS ~" << endl;
        
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
            break;
        }

        case 2: {
            break;
        }

        case 3: {
            break;
        }
    }

    cout << "Successfully ending program" << endl;

    delete curr_graph;
    return 0;
}