#include "node.h"
#include <cassert>

void Node::helper(BitString b, std::map<unsigned, BitString> & theMap, Node * node) {
  if (node->sym != NO_SYM) {
    assert(node->left == NULL && node->right == NULL);
    //    std::cout << b << std::endl;
    theMap[node->sym] = b;
    //    std::cout << (char)sym << ":" << b << std::endl;
    return;			 
  }
  if (node->left != NULL) {
    helper(b.plusZero(), theMap, node->left);
  }
  if (node->right != NULL) {
    helper(b.plusOne(), theMap, node->right);
  }
}

void Node::buildMap(BitString b, std::map<unsigned,BitString> & theMap) {
  helper(b, theMap, this);
}

