#pragma once

#include <iostream>
#include <set>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "graph.h"
using namespace std;

#define SUPRESS

const string invalid_string = "invalid";
const string valid_string = "valid";

namespace cust_lib {
    class Parser {
        public:
            Parser(string fileloc);
            Graph* read_file();

        private:
            string fileloc;
            string parse_line(string* to_modify, string& line_to_parse, int* no_items);
    };
};