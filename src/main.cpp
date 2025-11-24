#include <fstream>
#include <iostream>
#include "parser.h"

int main (int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Incorrect Argument Amount\n";
        return 1;
    }

    std::ifstream in(argv[1]);
    if (!in.is_open()) {
        std::cerr << "Cannot open file\n";
        return 1;
    }

    Parser parser(in);
    parser.Parse();

    in.close();

    return 0;
}
