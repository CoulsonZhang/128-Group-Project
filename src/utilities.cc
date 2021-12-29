#include "utilities.hpp"

bool edge_vec_contains(std::vector<Edge<string, double>> vec, string key) {
  for (size_t i = 0; i < vec.size(); i++) {
    const char *dest = vec[i].dest_.c_str();
    const char *k = key.c_str();
    if (!strcmp(dest, k)) {
      // dest already exist
      return true;
    }
  }
  return false;
}
std::vector<std::string> get_substrs(std::string s) {
  std::vector<std::string> vec;
  std::stringstream s_stream(s);
  while (s_stream.good()) {
    std::string substr;
    getline(s_stream, substr, ',');
    vec.push_back(substr);
  }
  return vec;
}

std::unordered_map<std::string, std::vector<Edge<string, double>>>
get_map(char *file_name) {
  std::ifstream ifs(file_name);
  std::unordered_map<std::string, std::vector<Edge<string, double>>> adj;
  for (std::string line; std::getline(ifs, line); line = "") {
    std::vector<std::string> vec;
    // fetch each line until eof
    vec = get_substrs(line);
    // get start building, end building, and weight
    std::string start = vec[0];
    std::string end = vec[1];
    if (end == "") {
      continue;
    }
    double weight = std::stod(vec[2]);
    // create edge e for current step -- undirected graph
    Edge<string, double> e_1(start, end, weight);
    Edge<string, double> e_2(end, start, weight);
    // push back edge e to the edge vector of start building.
    if (!edge_vec_contains(adj[start], end)) {
      // endbuilding DNE
      adj[start].push_back(e_1);
    }
    if (!edge_vec_contains(adj[end], start)) {
      // building DNE
      adj[end].push_back(e_2);
    }
  }
  //   std::cout << "map_size: " << adj.size() << std::endl;
  //   std::cout << "edge_vec: " << adj["McKinley Health Center"].size() <<
  //   std::endl;
  return adj;
}

void get_path_buildings(std::vector<string> buildings) {
  std::ofstream output("generate_map/path.txt", std::ofstream::out);
  if (output.is_open()) {
    for (size_t i = 0; i < buildings.size(); i++) {
      if (i < buildings.size() - 1) {
        // not the last building -- add a new line
        output << buildings[i] << "\n";
      } else {
        output << buildings[i];
      }
    }
  } else {
    std::cout << "Fail to Open File" << std::endl;
  }
  return;
}