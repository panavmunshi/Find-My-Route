#pragma once

#include <iostream>
#include <set>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "graph.h"
using namespace std;

namespace cust_lib {
    class Parser {
        public:
            Parser(string fileloc);
            Graph* read_file();

        private:
            string fileloc;
            void parse_line(string* to_modify, string* line_to_parse, int* no_items);
    };
};