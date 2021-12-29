#include "edge.hpp"
#include "graph.hpp"
#include "utilities.hpp"

// int main(int argc, char* argv[]) {

int main() {
  char file_name[] = "/home/vagrant/src/final/data/data_collect/edges.csv";
  std::unordered_map<std::string, std::vector<Edge<string, double>>> adj =
      get_map(file_name);
  std::cout << adj.size();

  Graph<string, double> graph(adj);
  vector<string> path = graph.shortestPath("Davenport Hall", "Altgeld Hall");

  get_path_buildings(path);
  return 0;
}