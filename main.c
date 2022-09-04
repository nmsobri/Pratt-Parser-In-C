#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "inc/lexer.h"
#include "inc/parser.h"

char* getLine() {
    int ch = 0;
    int count = 0;
    int capacity = 5;
    char* buffer = NULL;

    buffer = (char*)realloc(buffer, capacity * sizeof(*buffer));
    while ((ch = getchar()) != '\n') {
        count++;

        if (count >= capacity) {
            capacity *= 2;
            buffer = (char*)realloc(buffer, capacity * sizeof(*buffer));
        }

        if (!buffer) {
            free(buffer);
            break;
        }

        buffer[count - 1] = (char)ch;
    }

    count++;
    buffer = (char*)realloc(buffer, count * sizeof(*buffer));
    buffer[count - 1] = '\0';

    return buffer;
}

int main() {
    char* code = NULL;
    printf("Enter 'quit' to exit\n");

    do {
        printf("> ");
        code = getLine();

        if (strcmp(code, "quit") == 0) {
            break;
        }

        Lexer lexer = lexer_new(code);
        Parser parser = parser_new(&lexer);
        int result = parser_parseExpression(&parser, 0);

        printf("%d\n", result);
    } while (true);

    free(code);
    return 0;
}