// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Group CHONG                    Environment : ubuntu:bionic               //
//  Date ......: 2021/11/15                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <string>

#include "graph.hpp"
#include "edge.hpp"
#include "utilities.hpp"

using std::string;
using std::unordered_map;
using std::vector;

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
bool vecEqual(vector<string> &a, vector<string> &b) {
  if (a.size() != b.size())
    return false;
  for (size_t i = 0; i < a.size(); i++) {
    if (a[i] != b[i])
      return false;
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Graph Construction", "[construction]") {
  SECTION("default constructor") { Graph<string, double> g; }

  SECTION("initialization constructor") {
    unordered_map<string, vector<Edge<string, double>>> adj;
    adj["v1"] =
        vector<Edge<string, double>>({Edge<string, double>("v1", "v2", 1.0)});
    adj["v2"] =
        vector<Edge<string, double>>({Edge<string, double>("v2", "v1", 1.0)});
    Graph<string, double> g(adj);
    unordered_map<string, vector<Edge<string, double>>> adj_ = g.GetAdj();
    REQUIRE(adj_["v1"][0].dest_ == "v2");
    REQUIRE(adj_["v2"][0].dest_ == "v1");
  }
}

TEST_CASE("Map Construction", "[map]") {
  SECTION("map size") {
    char file_name[] = "data/data_collect/edges.csv";
    std::unordered_map<string, vector<Edge<string, double>>> adj =
        get_map(file_name);
    REQUIRE(adj.size() == (size_t)711);
  }
  SECTION("building vector size") {
    char file_name[] = "data/data_collect/edges.csv";
    std::unordered_map<string, vector<Edge<string, double>>> adj =
        get_map(file_name);
    REQUIRE(adj["Davenport Hall"].size() == 632);
    REQUIRE(
        adj["College of Fine and Applied Arts Performing Arts Annex"].size() ==
        651);
    REQUIRE(adj["McKinley Health Center"].size() == 643);
  }
  SECTION("directed edges") {
    char file_name[] = "data/data_collect/edges.csv";
    std::unordered_map<string, vector<Edge<string, double>>> adj =
        get_map(file_name);
    REQUIRE(
        edge_vec_contains(adj["Davenport Hall"], "Urbana Closet Space LLC"));
    REQUIRE(
        edge_vec_contains(adj["Urbana Closet Space LLC"], "Davenport Hall"));

    REQUIRE(edge_vec_contains(adj["McKinley Health Center"],
                              "Public Safety Building"));
    REQUIRE(edge_vec_contains(adj["McKinley Health Center"],
                              "Digital Computer Laboratory"));
    REQUIRE(
        edge_vec_contains(adj["McKinley Health Center"], "909 W Oregon St"));
    REQUIRE(edge_vec_contains(adj["McKinley Health Center"],
                              "631 E Green St 703/709 S Wright St"));
    REQUIRE(edge_vec_contains(adj["Public Safety Building"],
                              "McKinley Health Center"));
    REQUIRE(edge_vec_contains(adj["Digital Computer Laboratory"],
                              "McKinley Health Center"));
    REQUIRE(
        edge_vec_contains(adj["909 W Oregon St"], "McKinley Health Center"));
    REQUIRE(edge_vec_contains(adj["631 E Green St 703/709 S Wright St"],
                              "McKinley Health Center"));

    REQUIRE(edge_vec_contains(
        adj["College of Fine and Applied Arts Performing Arts Annex"],
        "EBI Site Office"));
    REQUIRE(edge_vec_contains(
        adj["College of Fine and Applied Arts Performing Arts Annex"],
        "1203 W Oregon St Urbana - Grounds Shed"));
    REQUIRE(edge_vec_contains(
        adj["College of Fine and Applied Arts Performing Arts Annex"],
        "YAHOO Building"));
    REQUIRE(edge_vec_contains(
        adj["EBI Site Office"],
        "College of Fine and Applied Arts Performing Arts Annex"));
    REQUIRE(edge_vec_contains(
        adj["1203 W Oregon St Urbana - Grounds Shed"],
        "College of Fine and Applied Arts Performing Arts Annex"));
    REQUIRE(edge_vec_contains(
        adj["YAHOO Building"],
        "College of Fine and Applied Arts Performing Arts Annex"));
  }
  SECTION("edge weight") {
    char file_name[] = "data/data_collect/edges.csv";
    std::unordered_map<string, vector<Edge<string, double>>> adj =
        get_map(file_name);
    Graph<string, double> g(adj);
    REQUIRE(g.GetEdgeWeight(
                "College of Fine and Applied Arts Performing Arts Annex",
                "Davenport Hall") == 2.2);
    REQUIRE(g.GetEdgeWeight("McKinley Health Center", "Astronomy Building") ==
            1.0);
    REQUIRE(g.GetEdgeWeight("Electrical Engineering Storage Building",
                            "Armory") == 2.7);
    REQUIRE(g.GetEdgeWeight("Technology Plaza", "Gym Annex") == 0.6);
    REQUIRE(g.GetEdgeWeight("Cruse Farm Pump Station",
                            "Foellinger Auditorium") == 3.0);
  }
}

TEST_CASE("Vertex tests", "[vertex]") {
  SECTION("existence") {
    Graph<string, double> g;
    REQUIRE_FALSE(g.IfVertexExist("v1"));
  }

  SECTION("insertion vertex") {
    unordered_map<string, vector<Edge<string, double>>> adj;
    adj["v1"] =
        vector<Edge<string, double>>({Edge<string, double>("v1", "v2", 1.0)});
    adj["v2"] =
        vector<Edge<string, double>>({Edge<string, double>("v2", "v1", 1.0)});
    Graph<string, double> g(adj);
    REQUIRE(g.IfVertexExist("v1"));
    g.InsertVertex("v3");
    REQUIRE(g.IfVertexExist("v3"));
  }

  SECTION("deletion vertex") {
    unordered_map<string, vector<Edge<string, double>>> adj;
    adj["v1"] =
        vector<Edge<string, double>>({Edge<string, double>("v1", "v2", 1.0)});
    adj["v2"] =
        vector<Edge<string, double>>({Edge<string, double>("v2", "v1", 1.0)});
    Graph<string, double> g(adj);
    g.DeleteVertex("v1");
    REQUIRE_FALSE(g.IfVertexExist("v1"));
    REQUIRE(g.IfVertexExist("v2"));
    REQUIRE_THROWS(g.DeleteVertex("v1"));
  }

  SECTION("get vertex") {
    unordered_map<string, vector<Edge<string, double>>> adj;
    adj["v1"] =
        vector<Edge<string, double>>({Edge<string, double>("v1", "v2", 1.0)});
    adj["v2"] =
        vector<Edge<string, double>>({Edge<string, double>("v2", "v1", 1.0)});
    Graph<string, double> g(adj);
    vector<string> res = g.GetAdjVertices("v1");
    REQUIRE(res.size() == 1);
    REQUIRE(res[0] == "v2");
  }
}

TEST_CASE("Edge tests", "[edge]") {
  SECTION("existence") {
    Graph<string, double> g;
    REQUIRE_FALSE(g.IfEdgeExist("v1", "v2"));
  }

  SECTION("insertion edge") {
    unordered_map<string, vector<Edge<string, double>>> adj;
    adj["v1"] =
        vector<Edge<string, double>>({Edge<string, double>("v1", "v2", 1.0)});
    adj["v2"] =
        vector<Edge<string, double>>({Edge<string, double>("v2", "v1", 1.0)});
    Graph<string, double> g(adj);
    g.InsertEdge("v1", "v3", 1.1);
    REQUIRE(g.IfEdgeExist("v1", "v3"));
    REQUIRE(g.GetEdgeWeight("v1", "v3") == 1.1);
    REQUIRE_THROWS(g.GetEdgeWeight("v2", "v3"));
    REQUIRE_THROWS(g.InsertEdge("v1", "v2", 1.0));
  }

  SECTION("deletion edge") {
    unordered_map<string, vector<Edge<string, double>>> adj;
    adj["v1"] =
        vector<Edge<string, double>>({Edge<string, double>("v1", "v2", 1.0)});
    adj["v2"] =
        vector<Edge<string, double>>({Edge<string, double>("v2", "v1", 1.0)});
    Graph<string, double> g(adj);
    g.DeleteEdge("v1", "v2");
    REQUIRE_FALSE(g.IfEdgeExist("v1", "v2"));
    REQUIRE(g.IfEdgeExist("v2", "v1"));
    REQUIRE_THROWS(g.GetEdgeWeight("v1", "v2"));
    REQUIRE_THROWS(g.DeleteEdge("v1", "v2"));
  }

  SECTION("update edge") {
    unordered_map<string, vector<Edge<string, double>>> adj;
    adj["v1"] =
        vector<Edge<string, double>>({Edge<string, double>("v1", "v2", 1.0)});
    adj["v2"] =
        vector<Edge<string, double>>({Edge<string, double>("v2", "v1", 1.0)});
    Graph<string, double> g(adj);
    g.UpdateEdge("v1", "v2", 1.2);
    REQUIRE(g.GetEdgeWeight("v1", "v2") == 1.2);
    REQUIRE_THROWS(g.GetEdgeWeight("v1", "v3"));
  }

  SECTION("get edge") {
    unordered_map<string, vector<Edge<string, double>>> adj;
    adj["v1"] =
        vector<Edge<string, double>>({Edge<string, double>("v1", "v2", 1.0)});
    adj["v2"] =
        vector<Edge<string, double>>({Edge<string, double>("v2", "v1", 1.0)});
    Graph<string, double> g(adj);
    vector<Edge<string, double>> res = g.GetAdjEdges("v1");
    REQUIRE(res.size() == 1);
    REQUIRE(res[0].dest_ == "v2");
    REQUIRE(res[0].weight_ == 1.0);
  }
}

TEST_CASE("test all", "[edge][vertex]") {
  SECTION("complex graph") {
    unordered_map<string, vector<Edge<string, double>>> adj;
    adj["v1"] =
        vector<Edge<string, double>>({Edge<string, double>("v1", "v2", 1.0)});
    adj["v2"] =
        vector<Edge<string, double>>({Edge<string, double>("v2", "v1", 1.0)});
    adj["v3"] = vector<Edge<string, double>>();
    adj["v4"] = vector<Edge<string, double>>();
    adj["v5"] = vector<Edge<string, double>>();
    Graph<string, double> g(adj);
    g.InsertEdge("v1", "v3", 1.1);
    g.InsertEdge("v2", "v3", 1.2);
    g.InsertEdge("v3", "v4", 1.3);
    g.InsertEdge("v2", "v4", 1.4);
    g.InsertEdge("v1", "v4", 1.5);
    g.InsertEdge("v2", "v5", 2.0);
    REQUIRE(g.IfVertexExist("v4"));
    REQUIRE(g.IfEdgeExist("v3", "v4"));
    g.UpdateEdge("v2", "v3", 2.0);
    REQUIRE(g.GetEdgeWeight("v2", "v3") == 2.0);
    REQUIRE(g.GetAdjVertices("v2").size() == 4);
    REQUIRE(g.GetAdjEdges("v2").size() == 4);
  }
}

TEST_CASE("shortest path", "[shortest path]") {
  SECTION("simple test") {
    unordered_map<string, vector<Edge<string, int>>> adj;
    adj["A"] = vector<Edge<string, int>>(
        {Edge<string, int>("A", "B", 6), Edge<string, int>("A", "D", 1)});
    adj["B"] = vector<Edge<string, int>>(
        {Edge<string, int>("B", "D", 2), Edge<string, int>("B", "E", 2),
         Edge<string, int>("B", "A", 6), Edge<string, int>("B", "C", 5)});
    adj["D"] = vector<Edge<string, int>>({Edge<string, int>("D", "A", 1),
                                          Edge<string, int>("D", "B", 2),
                                          Edge<string, int>("D", "E", 1)});
    adj["E"] = vector<Edge<string, int>>({Edge<string, int>("E", "B", 2),
                                          Edge<string, int>("E", "D", 1),
                                          Edge<string, int>("E", "C", 5)});
    adj["C"] = vector<Edge<string, int>>({
        Edge<string, int>("C", "B", 5),
        Edge<string, int>("C", "E", 5),
    });

    Graph<string, int> g(adj);
    vector<string> res = g.shortestPath("A", "D");
    vector<string> expected = {"A", "D"};
    REQUIRE(vecEqual(res, expected));

    res = g.shortestPath("A", "B");
    expected = {"A", "D", "B"};
    REQUIRE(vecEqual(res, expected));

    res = g.shortestPath("A", "C");
    expected = {"A", "D", "E", "C"};
    REQUIRE(vecEqual(res, expected));
  }
}
TEST_CASE("shortest path2", "[shortest path2]") {
  SECTION("simple test2") {
    unordered_map<string, vector<Edge<string, int>>> adj;
    adj["A"] = vector<Edge<string, int>>({Edge<string, int>("A", "B", 4),
                                          Edge<string, int>("A", "C", 1),
                                          Edge<string, int>("A", "D", 3)});
    adj["B"] = vector<Edge<string, int>>(
        {Edge<string, int>("B", "C", 2), Edge<string, int>("B", "A", 4)});
    adj["C"] = vector<Edge<string, int>>({Edge<string, int>("C", "D", 1),
                                          Edge<string, int>("C", "A", 1),
                                          Edge<string, int>("C", "B", 2)});
    adj["D"] = vector<Edge<string, int>>(
        {Edge<string, int>("D", "A", 3), Edge<string, int>("D", "C", 1)});

    Graph<string, int> g(adj);
    vector<string> res = g.shortestPath("A", "C");
    vector<string> expected = {"A", "C"};
    REQUIRE(vecEqual(res, expected));

    res = g.shortestPath("A", "B");
    expected = {"A", "C", "B"};
    REQUIRE(vecEqual(res, expected));

    res = g.shortestPath("A", "D");
    expected = {"A", "C", "D"};
    REQUIRE(vecEqual(res, expected));
  }
}

TEST_CASE("shortest path4", "[shortest path4]") {
  SECTION("complex test4") {
    unordered_map<string, vector<Edge<string, int>>> adj;
    adj["A"] = vector<Edge<string, int>>(
        {Edge<string, int>("A", "B", 3), Edge<string, int>("A", "C", 1)});
    adj["B"] = vector<Edge<string, int>>(
        {Edge<string, int>("B", "C", 7), Edge<string, int>("B", "D", 5),
         Edge<string, int>("B", "E", 1), Edge<string, int>("B", "A", 3)});
    adj["C"] = vector<Edge<string, int>>({Edge<string, int>("C", "D", 2),
                                          Edge<string, int>("C", "A", 1),
                                          Edge<string, int>("C", "B", 7)});
    adj["D"] = vector<Edge<string, int>>({Edge<string, int>("D", "E", 7),
                                          Edge<string, int>("D", "C", 2),
                                          Edge<string, int>("D", "B", 5)});
    adj["E"] = vector<Edge<string, int>>(
        {Edge<string, int>("E", "B", 1), Edge<string, int>("E", "D", 7)});

    Graph<string, int> g(adj);
    vector<string> res = g.shortestPath("A", "C");
    vector<string> expected = {"A", "C"};
    REQUIRE(vecEqual(res, expected));

    res = g.shortestPath("A", "B");
    expected = {"A", "B"};
    REQUIRE(vecEqual(res, expected));

    res = g.shortestPath("A", "D");
    expected = {"A", "C", "D"};
    REQUIRE(vecEqual(res, expected));

    res = g.shortestPath("A", "E");
    expected = {"A", "B", "E"};
    REQUIRE(vecEqual(res, expected));
  }
}

TEST_CASE("shortest path5", "[shortest path5]") {
  SECTION("complex test5") {
    unordered_map<string, vector<Edge<string, int>>> adj;
    adj["A"] = vector<Edge<string, int>>({Edge<string, int>("A", "B", 2),
                                          Edge<string, int>("A", "D", 7),
                                          Edge<string, int>("A", "C", 5)});
    adj["B"] = vector<Edge<string, int>>({Edge<string, int>("B", "D", 9),
                                          Edge<string, int>("B", "E", 1),
                                          Edge<string, int>("B", "A", 2)});
    adj["C"] = vector<Edge<string, int>>(
        {Edge<string, int>("C", "D", 3), Edge<string, int>("C", "A", 5),
         Edge<string, int>("C", "G", 2), Edge<string, int>("C", "H", 7)});
    adj["D"] = vector<Edge<string, int>>(
        {Edge<string, int>("D", "E", 10), Edge<string, int>("D", "C", 3),
         Edge<string, int>("D", "B", 9), Edge<string, int>("D", "A", 7),
         Edge<string, int>("D", "G", 5)});
    adj["E"] = vector<Edge<string, int>>(
        {Edge<string, int>("E", "B", 1), Edge<string, int>("E", "D", 10),
         Edge<string, int>("E", "G", 4), Edge<string, int>("E", "F", 2)});
    adj["F"] = vector<Edge<string, int>>({Edge<string, int>("F", "E", 2),
                                          Edge<string, int>("F", "G", 4),
                                          Edge<string, int>("F", "H", 6)});
    adj["G"] = vector<Edge<string, int>>(
        {Edge<string, int>("G", "E", 4), Edge<string, int>("G", "D", 5),
         Edge<string, int>("G", "C", 2), Edge<string, int>("G", "F", 4),
         Edge<string, int>("G", "H", 8)});
    adj["H"] = vector<Edge<string, int>>({Edge<string, int>("H", "C", 7),
                                          Edge<string, int>("H", "F", 6),
                                          Edge<string, int>("H", "G", 8)});

    Graph<string, int> g(adj);
    vector<string> res = g.shortestPath("A", "B");
    vector<string> expected = {"A", "B"};
    REQUIRE(vecEqual(res, expected));

    res = g.shortestPath("A", "D");
    expected = {"A", "D"};
    REQUIRE(vecEqual(res, expected));

    res = g.shortestPath("A", "C");
    expected = {"A", "C"};
    REQUIRE(vecEqual(res, expected));

    res = g.shortestPath("A", "E");
    expected = {"A", "B", "E"};
    REQUIRE(vecEqual(res, expected));

    res = g.shortestPath("A", "G");
    expected = {"A", "B", "E", "G"};
    REQUIRE(vecEqual(res, expected));

    res = g.shortestPath("A", "F");
    expected = {"A", "B", "E", "F"};
    REQUIRE(vecEqual(res, expected));

    res = g.shortestPath("A", "H");
    expected = {"A", "B", "E", "F", "H"};
    REQUIRE(vecEqual(res, expected));
  }
}

TEST_CASE("shortest_path3", "[shortest_path3]") {
  SECTION("complex test_3") {
    unordered_map<string, vector<Edge<string, int>>> adj;
    adj["a"] = vector<Edge<string, int>>({Edge<string, int>("a", "b", 9),
                                          Edge<string, int>("a", "c", 4),
                                          Edge<string, int>("a", "d", 7)});
    adj["b"] = vector<Edge<string, int>>(
        {Edge<string, int>("b", "e", 11), Edge<string, int>("b", "a", 9)});
    adj["c"] = vector<Edge<string, int>>({Edge<string, int>("c", "e", 17),
                                          Edge<string, int>("c", "f", 12),
                                          Edge<string, int>("c", "a", 4)});
    adj["d"] = vector<Edge<string, int>>(
        {Edge<string, int>("d", "f", 14), Edge<string, int>("d", "a", 7)});
    adj["e"] = vector<Edge<string, int>>({Edge<string, int>("e", "z", 5),
                                          Edge<string, int>("e", "c", 17),
                                          Edge<string, int>("e", "b", 11)});
    adj["f"] = vector<Edge<string, int>>({Edge<string, int>("f", "z", 9),
                                          Edge<string, int>("f", "c", 12),
                                          Edge<string, int>("f", "d", 14)});
    adj["z"] = vector<Edge<string, int>>(
        {Edge<string, int>("z", "e", 5), Edge<string, int>("z", "f", 9)});

    Graph<string, int> g(adj);
    vector<string> res = g.shortestPath("a", "b");
    vector<string> expected = {"a", "b"};
    REQUIRE(vecEqual(res, expected));

    res = g.shortestPath("a", "c");
    expected = {"a", "c"};
    REQUIRE(vecEqual(res, expected));

    res = g.shortestPath("a", "d");
    expected = {"a", "d"};
    REQUIRE(vecEqual(res, expected));

    res = g.shortestPath("a", "f");
    expected = {"a", "c", "f"};
    REQUIRE(vecEqual(res, expected));

    res = g.shortestPath("a", "z");
    expected = {"a", "c", "f", "z"};
    REQUIRE(vecEqual(res, expected));
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////