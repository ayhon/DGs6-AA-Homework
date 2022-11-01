/*
 *  Homework 1
 *  · Fernando Leal Sánchez
 *  · Pierre Gimalac
 *  · Iana Peix
 */

#include <bits/stdc++.h>
using namespace std;

// Type definitions {{{
// Problem specific {{{
using Vertex = int;
struct Edge {
  Vertex first, second;
  int weight;
  bool operator<(Edge const &other) const { return weight < other.weight; }
  /* bool operator<(Edge const &other) const { return weight > other.weight; } */
};

template <typename T> class UFDS {
private:
  using Index = int;
  vector<int> parents;
  vector<int> sizes;
  vector<vector<int>> children;
  vector<int> rank;
  int num_sets;
  vector<int> range(int n) {
    vector<int> v(n);
    for (int i = 0; i < n; i++)
      v[i] = i;
    return v;
  }

public:
  UFDS(int size) : rank(size,0), num_sets(size) {
    parents = range(size);
    sizes = vector<int>(size, 1);
    children = vector<vector<int>>(size);
  }

  int size() const { return num_sets; }
  int size(Index n) const { return sizes[find(n)]; }
  Index find(Index n) {
    return parents[n] = (parents[n] == n ? n : find(parents[n]));
  }
  Index join(Index x, Index y) {
    Index rx = find(x);
    Index ry = find(y);

    // Check whether they are already joined
    if (rx == ry)
      return rx;
    num_sets--;

    // Suppose that the representative of x has the lowest rank
    if (rank[rx] > rank[ry])
      swap(rx, ry);

    // Increase rank of y if it must grow
    rank[ry] += int(rank[ry] == rank[rx]);
    sizes[rx] += sizes[ry];
    children[rx].push_back(ry);
    return parents[ry] = rx;
  }
  vector<Index> successors(Index n) {
    queue<Index> to_process;
    vector<Index> result;
    Index curr = find(n);
    to_process.push(curr);
    result.push_back(curr);
    while (!to_process.empty()) {
      curr = to_process.front();
      to_process.pop();
      for (auto const &child : children[curr]) {
        to_process.push(child);
        result.push_back(child);
      }
    }
    return result;
  }
};
// }}}
// Input and output {{{
struct Output {
  vector<int> weights;
  vector<vector<int>> sets_elements;

  int get_num_non_zero_elements() const {
    int res = 0;
    for(auto const& weight : weights){
      res += (weight!=0);
    }
    return res;
  }

  void show() const {
    cout << get_num_non_zero_elements() << '\n';
    for (int i = 0; i < sets_elements.size(); i++) {
      int weight = weights[i];
      if (weight == 0) continue;
      vector<int> elements = sets_elements[i];
      cout << elements.size() << " " << weight << '\n';
      for (auto const &element : elements) {
        cout << element + 1 << " ";
      }
      cout << '\n';
    }
  }
};
struct Input {
  int num_vertices;
  int num_edges;
  vector<Edge> edges;
  /* unordered_map<Edge, int> cost; */
  void read() {
    cin >> num_vertices >> num_edges;
    edges = vector<Edge>(num_edges);
    for (auto &edge : edges) {
      cin >> edge.first >> edge.second >> edge.weight;
      edge.first--;
      edge.second--;
      /* cost[edge] = edge.weight; */
    }
  }
};
// }}}
// }}}

// Kruskal {{{
// Greedy for E = {vertices} and I = {subtrees of graph `edges`}
int Kruskal(int num_vertices, vector<Edge> const &edges) {
  UFDS<int> ufds(edges.size());
  vector<Edge> min_spanning_tree;
  if (edges.size() == 0)
    return 0;

  vector<Edge> reordered_edges(edges.size());
  copy(edges.begin(), edges.end(), reordered_edges.begin());
  sort(reordered_edges.begin(), reordered_edges.end());

  int result = 0;
  for (auto const &edge : reordered_edges) {
    if (ufds.find(edge.first) != ufds.find(edge.second)) {
      ufds.join(edge.first, edge.second);
      result += edge.weight;
    }
  }

  return result;
}
// }}}

// Greedy for E = {vertices} and I = {subtrees of graph `edges`}
Output KruskalsDual(int num_vertices, vector<Edge> const& edges) {
  UFDS<int> ufds(num_vertices);
  vector<Vertex> weight_indeces(num_vertices, -1);
  Output result;
  if (edges.size() == 0)
    return result;

  /* Rearrange the edges to be ordered by ascending weight */
  vector<Edge> reordered_edges(edges.size());
  copy(edges.begin(), edges.end(), reordered_edges.begin());
  sort(reordered_edges.begin(), reordered_edges.end());

  /*
   * Given the definitions from Section 5 found in
   *
   *    https://theory.epfl.ch/courses/topicstcs/Lecture52015.pdf
   *
   * we want to define the weights for each set of vertices
   * in the following way:
   *       ╭
   *       │ w(parent(e_j)) - w(e_j)    if S = V(e_j)
   *       │
   * y_S = ╡ w(e_j)                     if V = V(e_j)
   *       │
   *       │ 0                          otherwise
   *       ╰
   * To solve the dual of the minimum spanning tree problem:
   *
   *            max  y_V·(|V|-1) - ∑y_S(|S|-1)
   *           s.t.  for all e ∈ E, -∑y_S <= w(e) 
   *                 for all S ⊊ V, y_S >= 0
   */

  for (auto const &edge : reordered_edges) {
    int rep_first = ufds.find(edge.first);
    int rep_second = ufds.find(edge.second);
    if (rep_first != rep_second) {
      int rep_parent = ufds.join(edge.first, edge.second);
      if (weight_indeces[rep_first] != -1){
        /// It has w(e_j), but we want it to be edge.weight - w(e_j)
        result.weights[weight_indeces[rep_first]] -= edge.weight;
        result.weights[weight_indeces[rep_first]] *= -1;
	  }
      if (weight_indeces[rep_second] != -1){
        /// It has w(e_j), but we want it to be edge.weight - w(e_j)
        result.weights[weight_indeces[rep_second]] -= edge.weight;
        result.weights[weight_indeces[rep_second]] *= -1;
	  }
      weight_indeces[rep_parent] = result.weights.size();
      result.weights.push_back(edge.weight);
      result.sets_elements.push_back(ufds.successors(edge.first));
    }
  }

  return result;
}

Output solve(Input const &args) {
  return KruskalsDual(args.num_vertices, args.edges);
}

// main {{{
int main() {
  Input in;
  in.read();
  Output out = solve(in);
  out.show();
} // }}}
// vim: set foldmethod=marker:
