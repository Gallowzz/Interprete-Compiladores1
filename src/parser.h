#include "lexer.h"
#include <istream>

class Parser {
    Token currToken;
    Lexer lexer;

    void program();
    void statement();
    void varDecl();
    void assignment();
    void ifStmt();
    void whileStmt();
    void printStmt();
    void block();
    void expression();
    void logicalOr();
    void logicalAnd();
    void equality();
    void comparison();
    void term();
    void factor();
    void unary();
    void primary();
public:
    Parser(std::istream& in): lexer(in) {};
    void Parse();
};
