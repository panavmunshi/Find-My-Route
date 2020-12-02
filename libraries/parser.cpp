#include "parser.h"

cust_lib::Parser::Parser(string currfile) {
    fileloc = currfile;
}

void cust_lib::Parser::read_file() {
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
        string data_arr[35];
        string curr_line = "";

        while (std::getline(file_obj, curr_line)) {
            int no_of_items = 0;
            curr_line+= ",";
            
            parse_line(data_arr, &curr_line, &no_of_items);

            /* Use data to create graph. */
        }
    }
}

void cust_lib::Parser::parse_line(string* to_modify, string* line_to_parse, int* no_items) {
    size_t start_pos = 0, next_pos = 0;
    while ((next_pos = line_to_parse->find(",", start_pos)) != string::npos) {
        to_modify[(*no_items)++] =  line_to_parse->substr(start_pos, next_pos);
        start_pos = next_pos + 1;
    }
}