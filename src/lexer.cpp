#include "lexer.h"
#include <string>

enum class State {
    Q0,             // Estado Inicial
    // Operadores
    MINUS_Q1,       // Resta o Numero Negativo
    DIV_Q1,         // Divisor (o pasa a comentario)
    ARITHM_Q1,      // Otros Operadores Aritmeticos
    ASSIGN_Q1,      // Asignacion
    EQ_Q1,          // Comparacion Igualdad
    DELIM_Q1,       // Delimitadores
    NOT_Q1,         // Operador !
    NEQ_Q1,         // Desigualdad
    LESS_Q1,        // Menor
    LEQ_Q1,         // Menor o Igual
    GREAT_Q1,       // Mayor
    GEQ_Q1,         // Mayor o Igual
    AND_Q1,
    AND_Q2,
    OR_Q1,
    OR_Q2,
    // Tipos de Datos
    NUM_Q1,         // Enteros 64-bits
    ID_Q1,          // Identificadores y Palabras Claves (minusculas)
    ID_Q2,          // Solo Identificadores
    // Otros
    SPACES_Q1,      // Espacios
    COMMENT_Q1,     // Comentarios
    EOF_Q1,         // Final de Archivo
};

Token Lexer::nextToken() {
    State state = State::Q0;

    while (true) {
        switch (state) {
            case State::Q0:
                lexeme.clear();
                if (currChar == EOF)
                    state = State::EOF_Q1;
                else if (is_Digit(currChar)) {
                    lexeme += static_cast<char>(currChar);
                    currChar = in.get();
                    state = State::NUM_Q1;
                }
                else if (is_lower(currChar)) {
                    lexeme += static_cast<char>(currChar);
                    currChar = in.get();
                    state = State::ID_Q1;
                }
                else if (is_upper(currChar) || currChar == '_') {
                    lexeme += static_cast<char>(currChar);
                    currChar = in.get();
                    state = State::ID_Q2;
                }
                else if (currChar == '-'){
                    lexeme += static_cast<char>(currChar);
                    currChar = in.get();
                    state = State::MINUS_Q1;
                }
                else if (currChar == '/') {
                    lexeme += static_cast<char>(currChar);
                    currChar = in.get();
                    state = State::DIV_Q1;
                }
                else if (is_arithmetic(currChar)){
                    lexeme += static_cast<char>(currChar);
                    currChar = in.get();
                    state = State::ARITHM_Q1;
                }
                else if (currChar == '='){
                    lexeme += static_cast<char>(currChar);
                    currChar = in.get();
                    state = State::ASSIGN_Q1;
                }
                else if (currChar == '<'){
                    lexeme += static_cast<char>(currChar);
                    currChar = in.get();
                    state = State::LESS_Q1;
                }
                else if (currChar == '>'){
                    lexeme += static_cast<char>(currChar);
                    currChar = in.get();
                    state = State::GREAT_Q1;
                }
                else if (currChar == '&'){
                    lexeme += static_cast<char>(currChar);
                    currChar = in.get();
                    state = State::AND_Q1;
                }
                else if (currChar == '|'){
                    lexeme += static_cast<char>(currChar);
                    currChar = in.get();
                    state = State::OR_Q1;
                }
                else if (is_delim(currChar)) {
                    lexeme += static_cast<char>(currChar);
                    currChar = in.get();
                    state = State::DELIM_Q1;
                }
                else if (currChar == ' ' || currChar == '\t' || currChar == '\n') {
                    currChar = in.get();
                    state = State::SPACES_Q1;
                }
                else {
                    throw std::runtime_error("Invalid Character");
                }
                break;

            case State::EOF_Q1:
                return Token::END_OF_FILE;

            case State::NUM_Q1:
                if (is_Digit(currChar)) {
                    lexeme += static_cast<char>(currChar);
                    currChar = in.get();
                    state = State::NUM_Q1;
                }
                else {
                    return Token::NUMBER;
                }
                break;

            case State::ID_Q1:
                if (is_lower(currChar)) {
                    lexeme += static_cast<char>(currChar);
                    currChar = in.get();
                    state = State::ID_Q1;
                }
                else if (is_upper(currChar) || is_Digit(currChar) || currChar == '_') {
                    lexeme += static_cast<char>(currChar);
                    currChar = in.get();
                    state = State::ID_Q2;
                }
                else {
                    return tokenize_keyword(lexeme);
                }
                break;

            case State::ID_Q2:
                if (is_Digit(currChar)
                    || is_lower(currChar)
                    || is_upper(currChar)
                    || currChar == '_')
                {
                    lexeme += static_cast<char>(currChar);
                    currChar = in.get();
                    state = State::ID_Q2;
                }
                else {
                    return Token::IDENTIFIER;
                }
                break;

            case State::MINUS_Q1:
                if (is_Digit(currChar)) {
                    lexeme += static_cast<char>(currChar);
                    currChar = in.get();
                    state = State::NUM_Q1;
                }
                else
                    return Token::OP_MINUS;
                break;

            case State::DIV_Q1:
                if (currChar == '/') {
                    currChar = in.get();
                    state = State::COMMENT_Q1;
                }
                else
                    return Token::OP_DIV;
                break;

            case State::ARITHM_Q1:
                return tokenize_arithmetic(lexeme);

            case State::ASSIGN_Q1:
                if (currChar == '=') {
                    lexeme += static_cast<char>(currChar);
                    currChar = in.get();
                    state = State::EQ_Q1;
                }
                else
                    return Token::OP_ASSIGN;
                break;

            case State::EQ_Q1:
                return Token::OP_EQ;

            case State::NOT_Q1:
                if (currChar == '=') {
                    lexeme += static_cast<char>(currChar);
                    currChar = in.get();
                    state = State::EQ_Q1;
                }
                else
                    return Token::OP_NOT;
                break;

            case State::NEQ_Q1:
                return Token::OP_NEQ;

            case State::LESS_Q1:
                if (currChar == '=') {
                    lexeme += static_cast<char>(currChar);
                    currChar = in.get();
                    state = State::LEQ_Q1;
                }
                else
                    return Token::OP_LESS;
                break;

            case State::LEQ_Q1:
                return Token::OP_LEQ;

            case State::GREAT_Q1:
                if (currChar == '=') {
                    lexeme += static_cast<char>(currChar);
                    currChar = in.get();
                    state = State::GEQ_Q1;
                }
                else
                    return Token::OP_GREAT;
                break;

            case State::GEQ_Q1:
                return Token::OP_GEQ;

            case State::AND_Q1:
                if (currChar == '&') {
                    lexeme += static_cast<char>(currChar);
                    currChar = in.get();
                    state = State::AND_Q2;
                }
                else
                    return Token::N_A_T;
                break;

            case State::AND_Q2:
                return Token::OP_AND;

            case State::OR_Q1:
                if (currChar == '|') {
                    lexeme += static_cast<char>(currChar);
                    currChar = in.get();
                    state = State::OR_Q2;
                }
                else
                    return Token::N_A_T;
                break;

            case State::OR_Q2:
                return Token::OP_OR;

            case State::DELIM_Q1:
                return tokenize_delimiter(lexeme);

            case State::COMMENT_Q1:
                if (currChar != '\n') {
                    currChar = in.get();
                    state = State::COMMENT_Q1;
                }
                else {
                    state = State::Q0;
                }
                break;

            case State::SPACES_Q1:
                if (currChar == ' ' || currChar == '\t') {
                    currChar = in.get();
                    state = State::SPACES_Q1;
                }
                else {
                    state = State::Q0;
                }
                break;

            default:
                break;
        }
    }
}

// -----------------
// Token Assigner
// -----------------

Token Lexer::tokenize_keyword(std::string &lexeme) {
    if (lexeme == "int")
        return Token::KW_INT;
    else if (lexeme == "if")
        return Token::KW_IF;
    else if (lexeme == "else")
        return Token::KW_ELSE;
    else if (lexeme == "while")
        return Token::KW_WHILE;
    else if (lexeme == "print")
        return Token::KW_PRINT;
    else
        return Token::IDENTIFIER;
}

Token Lexer::tokenize_arithmetic(std::string& lexeme){
    if (lexeme == "+")
        return Token::OP_PLUS;
    else if (lexeme == "*")
        return Token::OP_MULT;
    else if (lexeme == "%")
        return Token::OP_MOD;
    else
        return Token::N_A_T;
}

Token Lexer::tokenize_delimiter(std::string &lexeme){
    if (lexeme == ";")
        return Token::SEMICOLON;
    else if (lexeme == ",")
        return Token::COMA;
    else if (lexeme == "(")
        return Token::LPAREN;
    else if (lexeme == ")")
        return Token::RPAREN;
    else if (lexeme == "{")
        return Token::LBRACKET;
    else if (lexeme == "}")
        return Token::RBRACKET;
    else
        return Token::N_A_T;
}

// -----------------
// Character Checker
// -----------------

bool Lexer::is_Digit(char){
    if (currChar >= '0' && currChar <= '9')
        return true;
    return false;
}

bool Lexer::is_upper(char){
    if (currChar >= 'A' && currChar <= 'Z')
        return true;
    return false;
}

bool Lexer::is_lower(char){
    if (currChar >= 'a' && currChar <= 'z')
        return true;
    return false;
}

bool Lexer::is_arithmetic(char) {
    if (currChar == '+' || currChar == '*' || currChar == '%')
        return true;
    return false;
}

bool Lexer::is_delim(char) {
    if (currChar == ';' || currChar == ',' || currChar == '('
        || currChar == ')' || currChar == '{' || currChar == '}')
        return true;
    return false;
}

// Token Clasifier for output
const char *Lexer::tokenToString(Token &token){
    switch (token) {
        case Token::END_OF_FILE: return "END_OF_FILE";
        case Token::NUMBER: return "NUMBER";
        case Token::IDENTIFIER: return "IDENTIFIER";
        case Token::KW_INT: return "KW_INT";
        case Token::KW_IF: return "KW_IF";
        case Token::KW_ELSE: return "KW_ELSE";
        case Token::KW_WHILE: return "KW_WHILE";
        case Token::KW_PRINT: return "KW_PRINT";
        default: return "Unknown";
    }
}
