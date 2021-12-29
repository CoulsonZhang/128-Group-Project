#include "graph.hpp"
#include <string.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

using std::string;
using std::unordered_map;
using std::vector;

// bool start_exist(std::vector<Edge<string, double>> vec, string key);
bool edge_vec_contains(std::vector<Edge<string, double>> vec, string key);
std::vector<std::string> get_substrs(std::string s);
std::unordered_map<std::string, std::vector<Edge<string, double>>>
get_map(char *file_name);
void get_path_buildings(std::vector<string> buildings);
