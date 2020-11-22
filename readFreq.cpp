#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include "readFreq.h"
using std::ifstream;
using std::cout;
using std::endl;
using std::string;

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256 ) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
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
