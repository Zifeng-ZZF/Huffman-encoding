## Huffman-encoding
Using huffman-encoding to compress text file.


### Basic process
* Read a source file and record the frequencies of every characters
* Construct a binary tree according to the frequencies
* Construct a map of every character and its bit representation using the tree
* Read the source file again and write into new file using the bit representation map

### Read frequencies
- related files: readFreq.h, readFreq.cpp
* Open source file
* Count the occurrence of every character (including exactly one EOF, there are 256 of them) and read into a uint64_t array

### Construct a binary tree
- related files: node.h, buildTree.cpp
* Principle: using a priority queue which treat the node with higher frequency as higher priority. Build the tree by popping two node from the pq and make them children of a new node with no symbol. Then push the new node into the pq. The last node in the pq is the root of the tree. In this way, all the original nodes (which have symbol) will be the leaves of the tree.
* take the frequencies array and push them into a priority queue - pq
* iterate through the pq and construct the tree
* the last node in the pq is the root

### Construct the map
- related files: node.h, node.cpp, bitstring.h, bitstring.cpp
* recursively fill in the map with BitString by way of backtracing and DFS (no edit to the original BitString)
* plus zero to the BitString if goes left, plus one if goes right
* when reach leave node, the BitString for that symbol in the leaf is complete and should then be put into the map

### write the bitstring as bits into a new file
