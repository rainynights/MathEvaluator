#ifndef PARSER_H
#define PARSER_H

#include "../include/token.h"

typedef struct _ParseResult {
    TokenRef *Tokens;
    int Count;
} ParseResult;
typedef ParseResult * ParseResultRef;

ParseResultRef ParseExpression(char *source);
void DestroyResult(ParseResultRef result);

#endif