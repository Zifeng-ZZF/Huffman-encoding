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


void writeHeader(BitFileWriter * bfw, const std::map<unsigned,BitString> &theMap) {
  for (int i =0 ; i < 257; i++) {
    std::map<unsigned,BitString>::const_iterator it = theMap.find(i);
    if (it != theMap.end()) {
      bfw->writeByte(it->second.size());
      bfw->writeBitString(it->second);
    }
    else {
      bfw->writeByte(0);
    }
  }
}

void writeCompressedOutput(const char* inFile,
			   const char *outFile,
			   const std::map<unsigned,BitString> &theMap ){
  BitFileWriter bfw(outFile);
  writeHeader(&bfw,theMap);

  //WRITE YOUR CODE HERE!
  //open the input file for reading
  ifstream is;
  is.open(inFile);
  if (!is.is_open()) {
    std::cerr << "File not valid: " << inFile << std::endl;
    exit(EXIT_SUCCESS);
  }
  //You need to read the input file, lookup the characters in the map,
  //and write the proper bit string with the BitFileWriter
  unsigned c = 0;
  while (is.get((char&)c)) {
    assert(theMap.find(c) != theMap.end());
    //    std::cout << (char)c << ":" << theMap.find(c)->second << std::endl;
    bfw.writeBitString(theMap.find(c)->second);
  }
  //dont forget to lookup 256 for the EOF marker, and write it out.
  bfw.writeBitString(theMap.find(256)->second);
  //BitFileWriter will close the output file in its destructor
  //but you probably need to close your input file.
  is.close();
}

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr,"Usage: compress input output\n");
    return EXIT_FAILURE;
  }
  //WRITE YOUR CODE HERE
  //Implement main
  //hint 1: most of the work is already done. 
  //hint 2: you can look at the main from the previous tester for 90% of this
  uint64_t * counts = readFrequencies(argv[1]);
  assert(counts != NULL);
  Node * root = buildTree(counts);
  delete[] counts;
  std::map<unsigned, BitString> theMap;
  BitString bstr;
  root->buildMap(bstr, theMap);
  writeCompressedOutput(argv[1], argv[2], theMap);
  delete root;
  return EXIT_SUCCESS;
}
