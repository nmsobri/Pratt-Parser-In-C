
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "inc/lexer.h"

bool isDigit(char ch) {
    if (ch >= '0' && ch <= '9') {
        return true;
    }
    return false;
}

Lexer lexer_new(char* code) {
    Lexer lexer = {
        .position = 0,
        .code = code,
        .current_token = {},
    };

    return lexer;
}

void lexer_skipWhitespace(Lexer* lexer) {
    while (lexer->code[lexer->position] == '\r' ||
           lexer->code[lexer->position] == '\n' ||
           lexer->code[lexer->position] == ' ') {
        lexer->position++;
    }
}

char lexer_currentChar(Lexer* lexer) {
    return lexer->code[lexer->position];
}

Token lexer_peekToken(Lexer* lexer) {
    int original_position = lexer->position;

    lexer_skipWhitespace(lexer);

    if (isDigit(lexer_currentChar(lexer))) {
        int start = lexer->position;

        while (isDigit(lexer_currentChar(lexer))) {
            lexer->position++;
        }

        int end = lexer->position;
        int buff_len = end - start + 1;  // +1 for terminator

        char buff[buff_len];
        memcpy(buff, &lexer->code[start], buff_len - 1);
        buff[buff_len - 1] = '\0';

        lexer->position = original_position;
        return token_make(TOKEN_NUMBER, buff, BP_NULL);
    } else if (lexer_currentChar(lexer) == '+') {
        lexer->position = original_position;
        return token_make(TOKEN_PLUS, "+", BP_PLUS);
    } else if (lexer_currentChar(lexer) == '-') {
        lexer->position = original_position;
        return token_make(TOKEN_MINUS, "-", BP_PLUS);
    } else if (lexer_currentChar(lexer) == '*') {
        lexer->position = original_position;
        return token_make(TOKEN_MULTI, "*", BP_MULTI);
    } else if (lexer_currentChar(lexer) == '/') {
        lexer->position = original_position;
        return token_make(TOKEN_DIVIDE, "/", BP_MULTI);
    } else {
        lexer->position = original_position;
        return token_make(TOKEN_EOF, "eof", BP_NULL);
    }
}

Token lexer_nextToken(Lexer* lexer) {
    lexer_skipWhitespace(lexer);

    if (isDigit(lexer_currentChar(lexer))) {
        int start = lexer->position;

        while (isDigit(lexer_currentChar(lexer))) {
            lexer->position++;
        }

        int end = lexer->position;
        int buff_len = end - start + 1;  // +1 for terminator

        char buff[buff_len];
        memcpy(buff, &lexer->code[start], buff_len - 1);
        buff[buff_len - 1] = '\0';

        lexer->current_token = token_make(TOKEN_NUMBER, buff, BP_NULL);
        return lexer->current_token;

    } else if (lexer_currentChar(lexer) == '+') {
        lexer->position++;
        lexer->current_token = token_make(TOKEN_PLUS, "+", BP_PLUS);
        return lexer->current_token;
    } else if (lexer_currentChar(lexer) == '-') {
        lexer->position++;
        lexer->current_token = token_make(TOKEN_MINUS, "-", BP_PLUS);
        return lexer->current_token;
    } else if (lexer_currentChar(lexer) == '*') {
        lexer->position++;
        lexer->current_token = token_make(TOKEN_MULTI, "*", BP_MULTI);
        return lexer->current_token;
    } else if (lexer_currentChar(lexer) == '/') {
        lexer->position++;
        lexer->current_token = token_make(TOKEN_DIVIDE, "/", BP_MULTI);
        return lexer->current_token;
    } else {
        lexer->current_token = token_make(TOKEN_EOF, "eof", BP_NULL);
        return lexer->current_token;
    }
}