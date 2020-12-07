#include "parser.h"

cust_lib::Parser::Parser(string currfile) {
    fileloc = currfile;
}

Graph* cust_lib::Parser::read_file() {
    ifstream file_obj;
    file_obj.open(fileloc);
    /**
     * Line details:
     * Year,Month,DayofMonth,DayOfWeek,DepTime,CRSDepTime,ArrTime,CRSArrTime,UniqueCarrier,FlightNum,TailNum,ActualElapsedTime,CRSElapsedTime,AirTime,ArrDelay,DepDelay,Origin,Dest,Distance,TaxiIn,TaxiOut,Cancelled,CancellationCode,Diverted,CarrierDelay,WeatherDelay,NASDelay,SecurityDelay,LateAircraftDelay
     * No. of items: 29
     */ 
    if (file_obj.is_open()) {
        // Proceed to parse file.
        // More space for good measure :)
        string data_arr[35], curr_line = "", prev_source = "", prev_dest = "", prev_flight = "";
        std::set<string> vertex_set;

        Graph* toReturn = new Graph(true, true);
        if (toReturn != NULL) {
            while (std::getline(file_obj, curr_line)) {
                int no_of_items = 0;
                curr_line+= ",";
                parse_line(data_arr, &curr_line, &no_of_items);

                /**
                 * Use data to create graph.
                 * We need four values to construct an edge and two values to construct the vertices.
                 * idx 16, 17: Ori, Dest Airports.
                 * idx 18: Distance. 
                 * idx 5: CRS Dept Time
                 * idx 7: CRS Arr Time
                 * idx 8+9: flight_details
                 */
                
                if (vertex_set.find(data_arr[16]) == vertex_set.end()) {
                    vertex_set.insert(data_arr[16]);
                    toReturn->insertVertex(data_arr[16]);
                }

                if (vertex_set.find(data_arr[17]) == vertex_set.end()) {
                    vertex_set.insert(data_arr[17]);
                    toReturn->insertVertex(data_arr[17]);
                }

                if (prev_source == data_arr[16] && prev_dest == data_arr[17]) {
                    string flight_details = data_arr[8] + data_arr[9];
                    if (!(prev_flight == flight_details)) {
                        toReturn->insertEdge(data_arr[16], data_arr[17]);
                        /* Need to fix this as the graph dt doesn't support multiple edges between vertices. */
                        toReturn->setEdgeWeight(data_arr[16], data_arr[17], Edge_Weight(std::stoi(data_arr[18]), std::stoi(data_arr[5]), std::stoi(data_arr[7]), flight_details));
                        prev_flight = flight_details;
                    }
                } else {
                    prev_source = data_arr[16];
                    prev_dest = data_arr[17];
                    prev_flight = data_arr[8] + data_arr[9];

                    toReturn->insertEdge(data_arr[16], data_arr[17]);
                    toReturn->setEdgeWeight(data_arr[16], data_arr[17], Edge_Weight(std::stoi(data_arr[18]), std::stoi(data_arr[5]), std::stoi(data_arr[7]), prev_flight));
                }
            }
        }
        return toReturn;
    } else {
        return NULL;
    }
}

void cust_lib::Parser::parse_line(string* to_modify, string* line_to_parse, int* no_items) {
    size_t start_pos = 0, next_pos = 0;
    while ((next_pos = line_to_parse->find(",", start_pos)) != string::npos) {
        to_modify[(*no_items)++] =  line_to_parse->substr(start_pos, next_pos);
        start_pos = next_pos + 1;
    }
}