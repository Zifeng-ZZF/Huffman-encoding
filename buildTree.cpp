#include "node.h"
#include <cassert>

Node *  buildTree(uint64_t * counts) {
  priority_queue_t pq;
  for (unsigned i = 0; i < 257; ++i) {
    if (counts[i] == 0) { continue; }
    pq.push(new Node(i, counts[i]));
  }
  while(pq.size() != 1) {
    Node * first = pq.top();
    pq.pop();
    Node * second = pq.top();
    pq.pop();
    pq.push(new Node(first, second));
  }
  Node * ans = pq.top();
  pq.pop();
  assert(pq.size() == 0);
  return ans;
}  
