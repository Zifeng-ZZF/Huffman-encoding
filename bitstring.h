#ifndef __BIT_STRING_H__
#define __BIT_STRING_H__
#include <deque>
#include <iostream>
#include <stdio.h>

/* BitString
 * ----------
 * Represent a bit sequence
 * using a boolean deque to hold bits
 */
class BitString {
  std::deque<bool> bits;
  BitString(std::deque<bool> b);
 public:
  BitString();
  BitString plusZero() const; // return a new BitString object appending bit 1 to the back
  BitString plusOne() const; // return a new BitString object appending bit 0 to the back
  void append(const BitString & rhs); // append bitstring rhs to the back of the current bit sequence
  void insertByte(unsigned char b); // 8 bits of the byte are appended to the back to current bits sequence from higher to lower bit
  unsigned char removeByte(); // remove the first byte of the bit sequences and return it
  bool removeBit(); // remove the first bit, and return it 
  int size() const;  // return the number of bits
  friend std::ostream & operator<<(std::ostream & s, const BitString & bs);
};


/* BitFileWriter
 * -------------
 * Wrapping a FILE * to write bit string to a file
 */
class BitFileWriter {
private:
  //This should NOT be copied or assigned to.
  BitFileWriter(const BitFileWriter & rhs);
  BitFileWriter & operator=(const BitFileWriter & rhs);
  FILE * f;
  BitString pending;
  void pushData();
public:
  BitFileWriter(const char * fname);
  void writeByte(unsigned char b);
  void writeBitString(const BitString & bs);
  ~BitFileWriter();
};

class BitReader {
private:
  FILE * f;
  BitString bs;
  void ensureData(int);
public:
  BitReader(FILE * input): f(input), bs(){}
  virtual ~BitReader(){
    fclose(f);
    f = NULL;
  }
  bool readBit();
  unsigned char readByte();
};

#endif
