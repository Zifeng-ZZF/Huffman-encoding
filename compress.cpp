#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <map>
#include <queue>
#include <assert.h>
#include <functional>
#include <stdlib.h>
#include "readFreq.h"
#include "node.h"
#include <fstream>
using std::ifstream;


void writeHeader(BitFileWriter * bfw, const std::map<unsigned, BitString> & theMap) {
  for (int i =0 ; i < 257; i++) {
    std::map<unsigned,BitString>::const_iterator it = theMap.find(i);
    if (it != theMap.end()) {
      bfw->writeByte(it->second.size()); // current BitString's size information
      bfw->writeBitString(it->second); // current BitString's content
    }
    else {
      bfw->writeByte(0); // if no such character, write empty byte
    }
  }
}

void writeCompressedOutput(const char * inFile, const char * outFile, const std::map<unsigned, BitString> & theMap){
  BitFileWriter bfw(outFile);
  //header information of how to decompress the bits
  writeHeader(&bfw, theMap);
  //open the input file for reading
  ifstream is;
  is.open(inFile);
  if (!is.is_open()) {
    std::cerr << "File not valid: " << inFile << std::endl;
    exit(EXIT_SUCCESS);
  }
  //lookup the characters in the map & and write the proper bit string with the BitFileWriter
  unsigned c = 0;
  while (is.get((char&)c)) {
    assert(theMap.find(c) != theMap.end());
    //    std::cout << (char)c << ":" << theMap.find(c)->second << std::endl;
    bfw.writeBitString(theMap.find(c)->second);
  }
  //dont forget to lookup 256 for the EOF marker, and write it out.
  bfw.writeBitString(theMap.find(256)->second);
  is.close();
}

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr,"Usage: compress input output\n");
    return EXIT_FAILURE;
  }
  // get frequencies of character of the input file
  uint64_t * counts = readFrequencies(argv[1]);
  assert(counts != NULL);
  // build the binary tree
  Node * root = buildTree(counts);
  // free the frequencies
  delete[] counts;
  std::map<unsigned, BitString> theMap;
  BitString bstr;
  // build the map of "character : bits representation" from the tree
  root->buildMap(bstr, theMap);
  // open src file again and write to dest file
  writeCompressedOutput(argv[1], argv[2], theMap);
  // free tree structure
  delete root;
  return EXIT_SUCCESS;
}
