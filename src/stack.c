#include "../include/stack.h"
#include "../include/token.h"
#include <stdio.h>
#include <stdlib.h>

StackNodeRef CreateStackNode(TokenRef token) {
    StackNodeRef node = calloc(1, sizeof(StackNode));
    if (!node) {
        printf("ERROR: Couldn't allocate memory for stack node\n");
        return 0;
    }

    node->Token = token;
    node->Next = 0;
    return node;
}

void DestroyStackNode(StackNodeRef node) {
    if (node) {
        free(node);
    }
}

StackRef CreateStack() {
    StackRef stack = calloc(1, sizeof(Stack));
    if (!stack) {
        printf("ERROR: Couldn't allocate memory for stack\n");
        return 0;
    }

    stack->Count = 0;
    return stack;
}

void DestroyStack(StackRef stack) {
    if (stack) {
        StackNodeRef node;
        while (stack->Top) {
            node = stack->Top;
            stack->Top = stack->Top->Next;
            DestroyStackNode(node);
        }

        free(stack->Top);
    }
}

int IsEmptyStack(StackRef stack) {
    return (!stack || !stack->Top || !stack->Count);
}

int PushStack(StackRef stack, TokenRef token) {
    if (!stack) {
        printf("ERROR: Stack was null\n");
        return 0;
    }

    StackNodeRef node = CreateStackNode(token);
    if (IsEmptyStack(stack)) {
        stack->Top = node;
        stack->Count = 1;
        return 1;
    }

    node->Next = stack->Top;
    stack->Top = node;
    stack->Count++;
    return 1;
}

int PopStack(StackRef stack, TokenRef *token) {
    if (!stack) {
        printf("ERROR: Stack was null\n");
        return 0;
    }

    if (IsEmptyStack(stack)) {
        return 0;
    }

    StackNodeRef node = stack->Top;
    stack->Top = stack->Top->Next;
    stack->Count--;
    *token = node->Token;
    DestroyStackNode(node);
    return 1;
}

int PeekStack(StackRef stack, TokenRef *token) {
    if (!stack) {
        printf("ERROR: Stack was null\n");
        return 0;
    }
    
    if (IsEmptyStack(stack)) {
        return 0;
    }

    *token = stack->Top->Token;
    return 1;
}
