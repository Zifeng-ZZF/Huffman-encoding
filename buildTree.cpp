#include "node.h"
#include <cassert>

Node *  buildTree(uint64_t * counts) {
  priority_queue_t pq;
  for (unsigned i = 0; i < 257; ++i) {
    if (counts[i] == 0) { 
      continue; 
    }
    pq.push(new Node(i, counts[i]));
  }
  // build tree from top/most frequent
  // then the most frequent symbol will have the least depth
  // therefore have least bits
  while(pq.size() != 1) {
    Node * first = pq.top();
    pq.pop();
    Node * second = pq.top();
    pq.pop();
    // combine two nodes and push to the back
    // all the symbol nodes will become leaves at the end
    pq.push(new Node(first, second)); 
  }
  Node * ans = pq.top();
  pq.pop();
  assert(pq.size() == 0);
  return ans;
}  
