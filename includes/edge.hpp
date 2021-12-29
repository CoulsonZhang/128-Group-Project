/**
 * header and implementation file for the template Edge class
 * @file includes/edge.hpp
 */

#ifndef EDGE_HPP
#define EDGE_HPP

template <typename T, typename V> class Edge {
public:
  T src_;
  T dest_;
  V weight_;

  /*
   * default constructor
   */
  Edge() {
    // intentionally left blank
  }

  /*
   * initialize for edge
   */
  Edge(const T &src, const T &dest, const V &weight) {
    src_ = src;
    dest_ = dest;
    weight_ = weight;
  }
};
#endif
