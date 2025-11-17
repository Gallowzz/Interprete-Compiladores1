#include "lexer.h"
#include <string>

enum class State {
    Q0,             // Estado Inicial
    EOF_Q1,         // Final de Archivo
    NUM_Q1,         // Enteros 64-bits
    ID_Q1,          // Identificadores y Palabras Claves (minusculas)
    ID_Q2,          // Solo Identificadores
    SPACES_Q1       // Espacios
};

std::string keywords[] = {
    "int",
    "if",
    "else",
    "while",
    "print"
};

Token Lexer::nextToken() {
    State state = State::Q0;

    while (true) {
        switch (state) {
            case State::Q0:
                lexeme.clear();
                if (currChar == EOF)
                    state = State::EOF_Q1;
                else if (currChar >= '0' && currChar <= '9') {
                    lexeme += static_cast<char>(currChar);
                    currChar = in.get();
                    state = State::NUM_Q1;
                }
                else if (currChar >= 'a' && currChar <= 'z') {
                    lexeme += static_cast<char>(currChar);
                    currChar = in.get();
                    state = State::ID_Q1;
                }
                else if (currChar >= 'A' && currChar <= 'Z' || currChar == '_') {
                    lexeme += static_cast<char>(currChar);
                    currChar = in.get();
                    state = State::ID_Q2;
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
                if (currChar >= '0' && currChar <= '9') {
                    lexeme += static_cast<char>(currChar);
                    currChar = in.get();
                    state = State::NUM_Q1;
                }
                else {
                    return Token::NUMBER;
                }
                break;

            case State::ID_Q1:
                if (currChar >= 'a' && currChar <= 'z') {
                    lexeme += static_cast<char>(currChar);
                    currChar = in.get();
                    state = State::ID_Q1;
                }
                else if (currChar >= 'A' && currChar <= 'Z' || currChar >= '0' && currChar <= '9' || currChar == '_') {
                    lexeme += static_cast<char>(currChar);
                    currChar = in.get();
                    state = State::ID_Q2;
                }
                else {
                    if (is_Keyword(lexeme))
                        return Token::KEYWORD;
                    else
                        return Token::IDENTIFIER;
                }
                break;

            case State::ID_Q2:
                if (currChar >= '0' && currChar <= '9'
                    || currChar >= 'a' && currChar <= 'z'
                    || currChar >= 'A' && currChar <= 'Z'
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

            case State::SPACES_Q1:
                if (currChar == ' ' || currChar == '\t') {
                    currChar = in.get();
                    state = State::SPACES_Q1;
                }
                else {
                    state = State::Q0;
                }

            default:
                break;
        }
    }
}

bool Lexer::is_Keyword(std::string &lexeme) {
    for (int i=0 ; i < keywords->length() ; i++) {
        if (lexeme == keywords[i])
            return true;
    }
    return false;
}

const char *Lexer::tokenToString(Token &token){
    switch (token) {
        case Token::END_OF_FILE: return "END_OF_FILE";
        case Token::NUMBER: return "NUMBER";
        case Token::IDENTIFIER: return "IDENTIFIER";
        case Token::KEYWORD: return "KEYWORD";
        default: return "Unknown";
    }
}
