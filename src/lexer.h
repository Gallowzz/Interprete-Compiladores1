#include <istream>
#include <string>

enum class Token {
    END_OF_FILE,
    NUMBER,
    IDENTIFIER,
    // Keywords
    KW_INT,
    KW_IF,
    KW_ELSE,
    KW_WHILE,
    KW_PRINT,
    // Operadores Aritmeticos
    OP_PLUS,
    OP_MINUS,
    OP_MULT,
    OP_DIV,
    OP_MOD,
    // Operadores Relacionales
    OP_EQ,
    OP_NEQ,
    OP_LESS,
    OP_GREAT,
    OP_LEQ,
    OP_GEQ,
    // Operadores Logicos
    OP_AND,
    OP_OR,
    OP_NOT,
    // Operador Assignacion
    OP_ASSIGN,
    // Delimitadores
    SEMICOLON,
    COMA,
    LPAREN,
    RPAREN,
    LBRACKET,
    RBRACKET,
    // Not a Token
    N_A_T
};

class Lexer {
private:
    std::istream& in;
    std::string lexeme;
    int currChar;
public:
    Lexer(std::istream& in_): in(in_) {
        currChar = in.get();
    }

    Token nextToken();
    std::string getLexeme() const { return lexeme; }
    static const char *Lexer::tokenToString(Token &token);

    // Para identificar tokens pertenecientes a grupos amplios
    // e.g. Keywords, Operadores, o Delimitadores
    Token tokenize_keyword(std::string& lexeme);
    Token tokenize_arithmetic(std::string& lexeme);
    Token tokenize_delimiter(std::string& lexeme);

    // Para revisar a que grupo pertenece un caracter. Mejora la lectura.
    bool is_Digit(char);
    bool is_upper(char);
    bool is_lower(char);
    bool is_arithmetic(char);
    bool is_delim(char);
};
