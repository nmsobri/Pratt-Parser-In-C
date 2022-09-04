#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "inc/lexer.h"
#include "inc/parser.h"

int main() {
    // char* code = "2 * 3 + 5";
    char* code = "4 / 2 - 2";

    Lexer lexer = lexer_new(code);
    Parser parser = parser_new(&lexer);
    int result = parser_parseExpression(&parser, 0);

    printf("Result: %d\n", result);
    return 0;
}