#include "functions.h"

#include <iostream>
#include <fstream>

void shift_enc(text_t &text, int shift) {
    unsigned char *str = text.string;
    unsigned char diff_end = (str[text.len - 1] & MASK) DECODE 8 - shift;
    for (int i = text.len - 1; i > 0; --i) {
        str[i] = (str[i] CODE shift) | (str[i - 1] & MASK) DECODE 8 - shift;
    }
    str[0] = (str[0] CODE shift) | diff_end;
} // work

void shift_dec(text_t &text, int shift) {
    unsigned char *str = text.string;
    unsigned char diff_end = (str[0] & DEMASK) CODE 8 - shift;
    for (int i = 0; i < text.len - 1; ++i) {
        str[i] = (str[i] DECODE shift) | (str[i + 1] & DEMASK) CODE 8 - shift;
    }
    str[text.len - 1] = (str[text.len - 1] DECODE shift) | diff_end;
} // work

void operator CODE(text_t &text, int shift) {
    shift_enc(text, shift);
} // work

void operator DECODE(text_t &text, int shift) {
    shift_dec(text, shift);
} // work

void gen_gamma(unsigned char *gam_buf) {
    for (int i = 0; i < BLOCK_SIZE; ++i) {
        gam_buf[i] = (unsigned char)rand();
    }
}

void operator ^ (text_t &text, unsigned char *gamma) {
    gen_gamma(gamma);
    for (int i = 0; i < text.len; ++i) {
        text.string[i] = text.string[i] ^ gamma[i];
    }
}

void code_text(std::ifstream &ifs, std::ofstream &ofs) {
    while (!ifs.eof()) {
        text_t text;
        ifs.read((char *)text.string, BLOCK_SIZE);
        text.len = ifs.gcount();
        text ^ text.gamma;
        text >> SHIFT_SIZE;
        ofs.write((char *)text.string, text.len);
    }
}

void decode_text(std::ifstream &ifs, std::ofstream &ofs) {
    while (!ifs.eof()) {
        text_t text;
        ifs.read((char *)text.string, BLOCK_SIZE);
        text.len = ifs.gcount();
        text << SHIFT_SIZE;
        text ^ text.gamma;
        ofs.write((char *)text.string, text.len);
    }
}
