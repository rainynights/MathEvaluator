#ifndef STACK_H
#define STACK_H

#include "../include/token.h"

typedef struct _StackNode {
    TokenRef Token;
    struct _StackNode * Next;
} StackNode;
typedef StackNode * StackNodeRef;

typedef struct _Stack {
    int Count;
    StackNodeRef Top;
} Stack;
typedef Stack * StackRef;

StackRef CreateStack();
void DestroyStack(StackRef stack);
int IsEmptyStack(StackRef stack);
int PushStack(StackRef stack, TokenRef token);
int PopStack(StackRef stack, TokenRef *token);
int PeekStack(StackRef stack, TokenRef *token);

#endif