#include "../include/token.h"
#include <stdio.h>
#include <stdlib.h>

TokenRef CreateToken(TokenKind kind, double value) {
    TokenRef token = calloc(1, sizeof(Token));
    if (!token) {
        printf("ERROR: Couldn't allocate memory for token!\n");
        return 0;
    }

    token->Kind = kind;
    token->Value = value;
    return token;
}

void DestroyToken(TokenRef token) {
    if (token) {
        free(token);
    }
}

int GetPrecedence(TokenKind kind) {
    if (kind == Plus || kind == Minus) {
        return 1;
    }
    
    if (kind == Star || kind == Slash || kind == Mod) {
        return 2;
    }
    
    if (kind == UnaryMinus) {
        return 3;
    }
    
    return 0;
}
