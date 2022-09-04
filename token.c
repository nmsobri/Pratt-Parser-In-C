#include <stdio.h>
#include <stdlib.h>

#include "inc/token.h"
#include "inc/parser.h"

static int token_number_nud(Parser* parser) {
    return atoi(parser->lexer->current_token.literal);
}

static int token_plus_nud(Parser* parser) {
    return atoi(parser->lexer->current_token.literal);
}

static int token_plus_led(int left, Parser* parser) {
    return left + parser_parseExpression(parser, parser->lexer->current_token.binding_power);
}

static int token_minus_nud(Parser* parser) {
    return -parser_parseExpression(parser, parser->lexer->current_token.binding_power);
}

static int token_minus_led(int left, Parser* parser) {
    return left - parser_parseExpression(parser, parser->lexer->current_token.binding_power);
}

static int token_multi_nud() {}

static int token_multi_led(int left, Parser* parser) {
    return left * parser_parseExpression(parser, parser->lexer->current_token.binding_power);
}

static int token_divide_nud(Parser* parser) {}

static int token_divide_led(int left, Parser* parser) {
    return left / parser_parseExpression(parser, parser->lexer->current_token.binding_power);
}

Token _token_make(TokenType type, char* literal, int binding_power, nudFn nud, ledFn led) {
    return (Token){
        .type = type,
        .literal = literal,
        .binding_power = binding_power,
        .nud = nud,
        .led = led,
    };
}

Token token_make(TokenType type, char* literal, int binding_power) {
    switch (type) {
        case TOKEN_NUMBER:
            return _token_make(type, literal, BP_NULL, &token_number_nud, NULL);
        case TOKEN_PLUS:
            return _token_make(type, literal, BP_PLUS, &token_plus_nud, &token_plus_led);
        case TOKEN_MINUS:
            return _token_make(type, literal, BP_PLUS, &token_minus_nud, &token_minus_led);
        case TOKEN_MULTI:
            return _token_make(type, literal, BP_MULTI, &token_multi_nud, &token_multi_led);

        case TOKEN_DIVIDE:
            return _token_make(type, literal, BP_MULTI, &token_divide_nud, &token_divide_led);
        default:
            return _token_make(type, literal, BP_NULL, NULL, NULL);
    }
}
