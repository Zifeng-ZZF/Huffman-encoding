#ifndef __NODE_H__
#define __NODE_H__
#include <queue>
#include <vector>
#include <map>
#include <cstdlib>
#include <stdint.h>
#include "bitstring.h"
#include <assert.h>
#define NO_SYM 999 // only leaf node has symbol, others filled with NO_SYM

/* class Binary Tree Node */
class Node {
private:
  // buildMap recursion helper
  void helper(BitString b, std::map<unsigned, BitString> & theMap, Node * node);

public:
  unsigned sym;
  uint64_t freq;
  Node * left; 
  Node * right;

  Node(unsigned s, uint64_t f): sym(s), freq(f), left(NULL), right(NULL) {}
  Node(Node * l, Node * r): sym(NO_SYM), freq(l->freq + r->freq), left(l), right(r) {}
  void buildMap(BitString b, std::map<unsigned, BitString> & theMap);

  ~Node() {
    if (left != NULL) {
      delete left;
    }
    if (right != NULL) {
      delete right;
    }
  }
};

/* binary comparator by overloading "bool operator()(...)": higher frequency gets higher priority */
class NodePtrCompare: std::binary_function <Node *, Node *, bool> {
public:
  bool operator()(Node * const & x, Node * const & y) const {
    return x->freq > y->freq;
  }
};

/* define a priority queue type which holds Node* and has implemented comparing class */
typedef std::priority_queue<Node *, std::vector<Node*>, NodePtrCompare> priority_queue_t;

/* building the tree encoding using the frequency array */
Node *  buildTree(uint64_t * counts);

#endif
