#pragma once

#include <iostream>
#include <set>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "graph.h"
using namespace std;

/* Define some constant strings for parse_line function. */
const string invalid_string = "invalid";
const string valid_string = "valid";

namespace cust_lib {
    /**
     * This class is responsible for parsing the CSV file.
     */
    class Parser {
        public:
            /**
             * Constructs the parser object using the fileloc.
             */
            Parser(string fileloc);

            /**
             * This function reads the CSV file and returns a Graph object containing the parsed data.
             * 
             * @return : Graph object.
             */ 
            Graph* read_file();

        private:
            /* Stores the location of the dataset. */
            string fileloc;

            /**
             * This is a helper function which helps parse a specific line into the data that is used to build the graph.
             * 
             * @param to_modify: pointer to an array of fixed size. Every comma seperated token is filled into this array. 
             * @param line_to_parse: Reference to the string that is to be parsed. 
             * @param no_items: Pointer to an integer in which the number of tokens found is stored. 
             * 
             * @return : invalid_string if the line was invalid. valid_string otherwise. 
             */ 
            string parse_line(string* to_modify, string& line_to_parse, int* no_items);
    };
};