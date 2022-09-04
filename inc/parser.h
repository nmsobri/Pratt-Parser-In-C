#pragma once

#include "lexer.h"

typedef struct Parser {
    Lexer* lexer;
} Parser;

Parser parser_new(Lexer* lexer);
int parser_parseExpression(Parser* parser, int rbp);