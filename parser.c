#include "inc/parser.h"
#include "inc/token.h"

#include <stdlib.h>

Parser parser_new(Lexer* lexer) {
    return (Parser){
        .lexer = lexer,
    };
}

// Pratt algorithm
int parser_parseExpression(Parser* parser, int rbp) {
    Token token = lexer_nextToken(parser->lexer);

    int left = token.nud(parser);

    while (rbp < lexer_peekToken(parser->lexer).binding_power) {
        token = lexer_nextToken(parser->lexer);
        left = token.led(left, parser);
    }

    return left;
}