#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "token.h"

typedef struct Lexer {
    int position;
    char* code;
    Token current_token;
} Lexer;

bool isDigit(char ch);
Lexer lexer_new(char* code);
void lexer_skipWhitespace(Lexer* lexer);
char lexer_currentChar(Lexer* lexer);
Token lexer_nextToken(Lexer* lexer);
Token lexer_peekToken(Lexer* lexer);