#include <iostream>

#include "functions.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Too few args\n";
        return -1;
    }
    srand(atoi(argv[1]));


    std::ifstream input(argv[2], std::ios::binary);
    std::ofstream res(RESULT);
    if (!input.is_open() || !res.is_open()) {
        std::cerr << "File not opened\n";
        return -1;
    }

    decode_text(input, res);
    input.close();
    res.close();
}
