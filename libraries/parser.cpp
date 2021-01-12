#include "parser.h"
#include <exception>

cust_lib::Parser::Parser(string currfile) {
    /* Store the file's location internally. */
    fileloc = currfile;
}

Graph* cust_lib::Parser::read_file() {
    /* Initialize the filestream object using the filelocation. */
    ifstream file_obj;
    file_obj.open(fileloc);

    /**
     * Line details:
     * 
     * Year,Month,DayofMonth,DayOfWeek,DepTime,CRSDepTime,ArrTime,CRSArrTime,UniqueCarrier,
     * FlightNum,TailNum,ActualElapsedTime,CRSElapsedTime,AirTime,ArrDelay,DepDelay,Origin,
     * Dest,Distance,TaxiIn,TaxiOut,Cancelled,CancellationCode,Diverted,CarrierDelay,WeatherDelay,
     * NASDelay,SecurityDelay,LateAircraftDelay
     * 
     * No. of items: 29
     */ 

    /* If the file is open, proceed. Otherwise, return NULL. */
    if (file_obj.is_open()) {
        /*Proceed to parse file. More space for good measure :) */
        string data_arr[35], curr_line = "", prev_flight = "";
        std::set<string> vertex_set;

        /* Get rid of the first line. */
        std::getline(file_obj, curr_line);
        
        /* Initialize the graph that is to be returned. It is weighted and directed. */
        Graph* toReturn = new Graph(true, true);
        int line_no = 0;

        /* If the graph was successfully allocated, proceed. Otherwise, return NULL. */
        if (toReturn != NULL) {
            /* Continue to parse the line as long as we can. */
            while (std::getline(file_obj, curr_line)) {
                int no_of_items = 0;
                curr_line += ",";
                
                /* If the line isn't parsed correctly, handle it. */
                if (parse_line(data_arr, curr_line, &no_of_items) == invalid_string) {
                    /* If line is invalid, try to parse the next line. */
                    continue;
                }

                /**
                 * Use data to create graph.
                 * We need four values to construct an edge and two values to construct the vertices.
                 * idx 16, 17: Ori, Dest Airports.
                 * idx 18: Distance. 
                 * idx 5: CRS Dept Time
                 * idx 7: CRS Arr Time
                 * idx 8+9: flight_details
                 */
                
                /* Insert vertices only when they aren't previously present. */
                if (vertex_set.find(data_arr[16]) == vertex_set.end()) {
                    vertex_set.insert(data_arr[16]);
                    toReturn->insertVertex(data_arr[16]);
                }

                if (vertex_set.find(data_arr[17]) == vertex_set.end()) {
                    vertex_set.insert(data_arr[17]);
                    toReturn->insertVertex(data_arr[17]);
                }

                /* The CSV file has fields which are marked NA. This may result in an exception. Catch the exception to prevent the program from crashing. */
                try {
                    if (!toReturn->edgeExists(data_arr[16], data_arr[17])) {
                        int dist = stoi(data_arr[18]), arr = stoi(data_arr[7]), dept = stoi(data_arr[5]);
                        toReturn->insertEdge(data_arr[16], data_arr[17], dist);
                        toReturn->insertDetails(data_arr[16], data_arr[17], data_arr[8] + data_arr[9], arr, dept);
                    } else {
                        int arr = stoi(data_arr[7]), dept = stoi(data_arr[5]);
                        toReturn->insertDetails(data_arr[16], data_arr[17], data_arr[8] + data_arr[9], arr, dept);
                        prev_flight = data_arr[8] + data_arr[9];
                    }

                } catch(exception& e) {
                    /* If DEBUG is defined, print out the exception's error. */
                    #ifdef DEBUG
                        cout << e.what() << " Line no. " << line_no << endl;
                    #endif
                }
                
                /* Increment line. This is helpful while debugging. */
                line_no++;
            }
        }

        /* Return when completely parsed. */
        return toReturn;
    } else {
        return NULL;
    }
}

string cust_lib::Parser::parse_line(string* to_modify, string& line_to_parse, int* no_items) {
    size_t start_pos = 0, next_pos = 0;

    /* Parse for every string token seperated by a comma. */
    while ((next_pos = line_to_parse.find(",", start_pos)) != string::npos) {
        to_modify[(*no_items)++] =  line_to_parse.substr(start_pos, next_pos - start_pos); 
        start_pos = next_pos + 1;
    }

    /* If the number of items is less than 29, this means that one value was missing in between. This is fatal and we should inform the function. */
    if (*no_items < 29) {
        return invalid_string;
    } else {
        return valid_string;
    }
}