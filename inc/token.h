#pragma once

typedef struct Parser Parser;

typedef enum TokenType {
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTI,
    TOKEN_DIVIDE,
    TOKEN_EOF,
} TokenType;

struct Token;
typedef int (*nudFn)(Parser* parser);
typedef int (*ledFn)(int left, Parser* parser);

typedef struct Token {
    TokenType type;
    char* literal;
    int binding_power;
    nudFn nud;
    ledFn led;
} Token;

typedef enum BindingPower {
    BP_PLUS = 10,
    BP_MULTI = 20,
    BP_NULL = -1,
} BindingPower;

Token token_make(TokenType type, char* literal, int binding_power);