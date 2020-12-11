#pragma once
#include <string>
#include <iostream>

class edge_struct {
    public:
        int dist;
        int dept_time;
        int arr_time;
        std::string flight_data;

        edge_struct(int d, int dt, int at, std::string fd) : dist(d), dept_time(dt), arr_time(at), flight_data(fd) {}
        edge_struct(): dist(0), dept_time(0), arr_time(0), flight_data("") {}

        edge_struct(const edge_struct& other) {
            dist = other.dist;
            dept_time = other.dept_time;
            arr_time = other.arr_time;
            flight_data = other.flight_data;
        }

        edge_struct& operator=(const edge_struct& other) {
            dist = other.dist;
            dept_time = other.dept_time;
            arr_time = other.arr_time;
            flight_data = other.flight_data;
            
            return *this;
        }

        bool operator!=(const edge_struct& other) const {
            return dist != other.dist || dept_time != other.dept_time || arr_time != other.arr_time || flight_data != other.flight_data;
        }

        bool operator<(const edge_struct& other) const {
            return dist < other.dist;
        }

        friend std::ostream& operator<<(std::ostream& out, const edge_struct& edge_val) {
            out << "Dist: " << edge_val.dist << " Dept_Time: " << edge_val.dept_time << " Arr_Time: " << edge_val.arr_time << " Flight Data: " << edge_val.flight_data;
            return out;
        }
};