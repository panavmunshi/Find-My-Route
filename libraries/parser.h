#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

namespace cust_lib {
    class Parser {
        public:
            Parser(string fileloc);
            void read_file();

        private:
            string fileloc;
            void parse_line(string* to_modify, string* line_to_parse, int* no_items);
    };
};