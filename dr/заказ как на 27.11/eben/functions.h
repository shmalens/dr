#ifndef FUNCTIONS
#define FUNCTIONS

#include <iostream>
#include <fstream>

#define RESULT "result"

#define BLOCK_SIZE 16

#define CODE >>
#define DECODE <<
#define SHIFT_SIZE 6

#define MASK 0b00011111
#define DEMASK 0b11111000

typedef struct {
    unsigned char string[BLOCK_SIZE];
    unsigned char gamma[BLOCK_SIZE];
    size_t len;
} text_t;

void shift_enc(text_t &text, int shift);
void shift_dec(text_t &text, int shift);
void operator CODE(text_t &text, int shift);
void operator DECODE(text_t &text, int shift);
void gen_gamma(unsigned char *gam_buf);
void code_text(std::ifstream &ifs, std::ofstream &ofs);
void decode_text(std::ifstream &ifs, std::ofstream &ofs);


#endif
