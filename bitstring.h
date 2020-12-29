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
  BitFileWriter(const BitFileWriter & rhs); // throw exception
  BitFileWriter & operator=(const BitFileWriter & rhs); // throw exception
  FILE * f; // file stream
  BitString pending; // BitString to write to the file
  void pushData(); // write complete bytes in BitString 'bits' to file 'f', byte by byte
public:
  BitFileWriter(const char * fname); // open a file stream to fname with "w" permission
  void writeByte(unsigned char b); // add to back of the pending BitString and pushData
  void writeBitString(const BitString & bs); // append a Bitstring to pending and push Data
  ~BitFileWriter(); // destructor: supplement zeros to remaining bits and pushData & close file stream
};

/* BitReader
 * -----------
 * Wrapping a FILE * and a BitString to read bit/byte from the file into BitString
 */
class BitReader {
private:
  FILE * f;
  BitString bs;
  void ensureData(int); // make sure enough bits are read from file into BitString to be returned
public:
  BitReader(FILE * input): f(input), bs(){}
  virtual ~BitReader(){ // destructor
    fclose(f);
    f = NULL;
  }
  bool readBit(); // read one bit from file
  unsigned char readByte(); // read one byte from file
};

#endif
