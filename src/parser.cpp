#include "parser.h"

void Parser::Parse() {
    currToken = lexer.nextToken();
    while (currToken != Token::END_OF_FILE){
        statement();
    }
}

void Parser::statement(){
    if (currToken == Token::KW_INT){
        currToken = lexer.nextToken();
        varDecl();
    }
    else if (currToken == Token::IDENTIFIER){
        currToken = lexer.nextToken();
        assignment();
    }
    else if (currToken == Token::KW_IF) {
        currToken = lexer.nextToken();
        ifStmt();
    }
    else if (currToken == Token::KW_WHILE){
        currToken = lexer.nextToken();
        whileStmt();
    }
    else if (currToken == Token::KW_PRINT) {
        currToken = lexer.nextToken();
        printStmt();
    }
    else if (currToken == Token::LBRACKET) {
        currToken = lexer.nextToken();
        block();
    }
    else {
        throw std::runtime_error("Expected Statement");
    }
}

void Parser::varDecl(){
    if (currToken == Token::IDENTIFIER){
        currToken = lexer.nextToken();
        if (currToken == Token::OP_ASSIGN){
            currToken = lexer.nextToken();
            expression();
        }
        else if (currToken == Token::SEMICOLON){
            currToken = lexer.nextToken();
        }
        else {
            throw std::runtime_error("Expected assignment or ';'");
        }
    }
    else {
        throw std::runtime_error("Expected Identifier");
    }
}

void Parser::assignment(){
    if (currToken == Token::OP_ASSIGN){
        currToken = lexer.nextToken();
        expression();
        if (currToken == Token::SEMICOLON) {
            currToken = lexer.nextToken();
        }
        else {
            throw std::runtime_error("Expected ';'");
        }
    }
    else {
        throw std::runtime_error("Expected '='");
    }
}

void Parser::ifStmt(){
    if (currToken == Token::LPAREN){
        currToken = lexer.nextToken();
        expression();
        if (currToken == Token::RPAREN){
            currToken = lexer.nextToken();
            statement();
            if (currToken == Token::KW_ELSE){
                currToken = lexer.nextToken();
                statement();
            }
        }
        else {
            throw std::runtime_error("Expected ')'");
        }
    }
    else {
        throw std::runtime_error("Expected '('");
    }
}

void Parser::whileStmt(){
    if (currToken == Token::LPAREN) {
        currToken = lexer.nextToken();
        expression();
        if (currToken == Token::RPAREN) {
            statement();
        }
        else {
            throw std::runtime_error("Expected ')'");
        }
    }
    else {
        throw std::runtime_error("Expected '('");
    }
}

void Parser::printStmt(){
    if (currToken == Token::LPAREN) {
        currToken = lexer.nextToken();
        expression();
        if (currToken == Token::RPAREN) {
            if (currToken == Token::SEMICOLON){
                currToken = lexer.nextToken();
            }
            else {
                throw std::runtime_error("Expected ';'");
            }
        }
        else {
            throw std::runtime_error("Expected ')'");
        }
    }
    else {
        throw std::runtime_error("Expected '('");
    }
}

void Parser::block(){
    while(currToken != Token::RBRACKET) {
        if (currToken == Token::END_OF_FILE){
            throw std::runtime_error("Expected '}'");
        }
        else {
            currToken = lexer.nextToken();
            statement();
        }
    }
    currToken = lexer.nextToken();
}
