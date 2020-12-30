#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include "readFreq.h"
using std::ifstream;
using std::cout;
using std::endl;
using std::string;

void printSymbol(unsigned sym) {
  if (sym > 256 ) {
    cout << "INV";
  }
  else if (sym == 256) {
    cout << "EOF";
  }
  else if (isprint(sym)) { // is printable ?
    char c = sym;
    cout << "'" << c << "'";
  }
  else {
    std::streamsize w = cout.width(3);
    cout << std::hex << sym << std::dec;
    cout.width(w);
  }
}

uint64_t * readFrequencies(const char * fname) {
  ifstream is;
  is.open(fname);
  uint64_t * ans = new uint64_t[257](); 
  if (is.is_open()) {
    size_t c = 0;
    while (is.get((char&)c)) {
      ++ans[c];
    }
    ++ans[256];
  }
  else {
    std::cerr << "No such file: " << fname << endl;
    exit(EXIT_FAILURE);
  }
  is.close();
  return ans;
}
