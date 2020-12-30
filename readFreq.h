#ifndef __READ_FREQ_H__
#define __READ_FREQ_H__
#include <stdint.h>
#include <assert.h>
#include <iostream>

/* readFrequency
 * ----------------
 * open a file and record the frequencies of every character
 * the 256-th element represent the occurrence of EOF, which should be exactly 1
 * 
 * fname: name of the file to read
 * return: the array of frequencies, with index representing the character's numeric value
 */
uint64_t * readFrequencies(const char * fname);


/* printSymbol
 * ------------
 * formatted output of different symbol
 * 
 * sym: the numeric value of symbol
 */
void printSymbol(unsigned sym);

#endif
