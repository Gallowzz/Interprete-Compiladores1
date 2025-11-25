#include <fstream>
#include <iostream>
#include "lexer.h"

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

    Lexer lexer(in);

    Token token = lexer.nextToken();
    while (token != Token::END_OF_FILE) {
        std::cout << "Token: " << lexer.tokenToString(token) << ", Lexeme: '" << lexer.getLexeme() << "'\n";
        token = lexer.nextToken();
    }


    in.close();

    return 0;
}
