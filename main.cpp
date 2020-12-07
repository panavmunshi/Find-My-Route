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
            cout << "INVALID FILE! Please input a valid string\n" << endl;
        } else {
            break;
        }
    }

    delete curr_graph;
    cout << "Successfully read file!" << endl;
    return 0;
}