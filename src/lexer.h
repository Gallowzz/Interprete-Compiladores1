#include <istream>
#include <string>

enum class Token {
    END_OF_FILE,
    NUMBER,
    IDENTIFIER,
    KEYWORD
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

    // Para revisar a que grupo pertenece un caracter. Mejora la lectura.
    bool is_Keyword(std::string& lexeme);
    bool is_Digit(char);
    bool is_upper(char);
    bool is_lower(char);
    bool is_symbol(char);
};
