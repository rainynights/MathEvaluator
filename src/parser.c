#include "../include/parser.h"
#include "../include/token.h"
#include <stdio.h>
#include <stdlib.h>

int IsDigit(char c) {
    return c >= '0' && c <= '9';
}

double ParseDouble(char *start, char* end) {
    if (!start || !end || start > end) {
        return 0;
    }

    double value = 0;
    int digit, divide = 0;
    while (start <= end) {
        if ((*start) == '.') {
            divide = 10;
            continue;
        }

        divide /= 10;
        digit = (*start) & 0b1111;
        value = (divide)
            ? value + (digit / divide)
            : value * 10 + digit;
        start++;
    }

    return value;
}

int AddToken(ParseResultRef result, TokenKind kind, double value) {
    if (!result) {
        printf("ERROR: ResultRef was null\n");
        return 0 ;
    }

    TokenRef token = CreateToken(kind, value);
    if (!token) {
        return 0;
    }

    result->Tokens = realloc(result->Tokens, sizeof(TokenRef) * (result->Count + 1));
    result->Tokens[result->Count++] = token;
    return 1;
}

ParseResultRef ParseExpression(char *source) {
    ParseResultRef result = calloc(1, sizeof(ParseResult));
    result->Count = 0;
    int index = -1, state;
    char current;
    int scope = 0;
    while ((current = source[++index])) {
        if (current == ' ') {
            continue;
        }
        else if (IsDigit(current)) {
            int start = index;
            int floatingPoint = 0;
            do {
                if (current == '.' && floatingPoint++) {
                    printf("ERROR: Invalid numeric value at %d\n", index);
                    return 0;
                }
            } while ((current = source[++index]) && (IsDigit(current) || current == '.'));

            double value = ParseDouble(source + start, source + --index);
            state = AddToken(result, Number, value);
        }
        else if (current == '+') {
            state = AddToken(result, Plus, 0);
        }
        else if (current == '-') {
            state = AddToken(result, Minus, 0);
        }
        else if (current == '*') {
            state = AddToken(result, Star, 0);
        }
        else if (current == '%') {
            state = AddToken(result, Mod, 0);
        }
        else if (current == '/') {
            state = AddToken(result, Slash, 0);
        }
        else if (current == '(') {
            state = AddToken(result, OpenParan, 0);
            scope++;
        }
        else if (current == ')') {
            if (scope-- == 0) {
                printf("ERROR: Found unmatched paranthesis at %d\n", index);
                return 0;
            }

            state = AddToken(result, CloseParan, 0);
        }
        else {
            printf("ERROR: Unresolved character at %d: %c\n", index, current);
            return 0;
        }

        if (!state) {
            return 0;
        }
    }

    return result;
}

void DestroyResult(ParseResultRef result) {
    if (result) {
        for (int i = 0; i < result->Count; i++) {
            free(result->Tokens[i]);
        }

        free(result->Tokens);
        free(result);
    }
}
