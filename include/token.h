#ifndef TOKEN_H
#define TOKEN_H

typedef enum _TokenKind {
    Number,
    Plus,
    Minus,
    Star,
    Slash,
    Mod,
    UnaryMinus,
    OpenParan,
    CloseParan,
} TokenKind;

typedef struct _Token {
    TokenKind Kind;
    double Value;
} Token;
typedef Token * TokenRef;

TokenRef CreateToken(TokenKind kind, double value);
void DestroyToken(TokenRef token);
int GetPrecedence(TokenKind kind);

#endif