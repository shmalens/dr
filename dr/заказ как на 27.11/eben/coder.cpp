#include <iostream>

#include "functions.h"

int main(int argc, char *argv[]) {
    if (argc < 4) {
        std::cerr << "Too few args\n";
        return -1;
    }
    srand(atoi(argv[1]));


    std::ifstream fd_in(argv[2]);
    std::ofstream fd_out(argv[3], std::ios::binary);
    if (!fd_in.is_open()) {
        std::cerr << "File not opened\n";
        return -1;
    }

    code_text(fd_in, fd_out);
    fd_in.close();
    fd_out.close();
}

//int main(int argc, char *argv[]) {
//    unsigned char str[12] = "Hello World";
//    unsigned char res[12];
//
//    srand(atoi(argv[1]));
//
//    unsigned char gammas[BLOCK_SIZE];
//
//    for (int i = 0; i < BLOCK_SIZE; ++i) {
//        gammas[i] = rand();
//    }
//
//    for (int i = 0; i < BLOCK_SIZE; ++i) {
//        std::cout << (int)gammas[i] << std::endl;
//        res[i] = str[i] ^ gammas[i];
//    }
//    std::cout << res << std::endl;
//
//    for (int i = 0; i < BLOCK_SIZE; ++i) {
//        std::cout << (unsigned char)(res[i] ^ gammas[i]);
//    }
//    std::cout << '\n';
//}

//int main() {
//    srand(12);
//    text_t text;
//    std::cout << "test1" << std::endl;
//
//    std::ofstream fd(INPUT, std::ios::binary);
//    fd << "hello world!";
//    fd.close();
//
//    std::ifstream fd_fill(INPUT, std::ios::binary);
//    fd_fill.read((char * )text.string, BLOCK_SIZE);
//    text.len = fd_fill.gcount();
//    gen_gamma(text.gamma);
//    for (int i = 0; i < BLOCK_SIZE; ++i) {
//        text.string[i] = text.string[i] ^ text.gamma[i];
//    }
//    text >> SHIFT_SIZE;
//    std::cout << text.string << std::endl;
//
//    text << SHIFT_SIZE;
//    for (int i = 0; i < BLOCK_SIZE; ++i) {
//        text.string[i] = text.string[i] ^ text.gamma[i];
//    }
//    std::cout.write((char *)text.string, text.len);
//    fd_fill.close();
//}
