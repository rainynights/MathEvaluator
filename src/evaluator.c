#include "../include/evaluator.h"
#include "../include/token.h"
#include "../include/parser.h"
#include "../include/stack.h"
#include <stdio.h>
#include <stdlib.h>

int EvaluateResult(ParseResultRef result, double *outValue) {
    if (!result) {
        printf("ERROR: Unable to evaluate result because it was null\n");
        return 0;
    }

    *outValue = 0;
    StackRef numStack = CreateStack();
    StackRef opStack = CreateStack();
    TokenRef token = 0, token2 = 0;

    int lastWasNum = 0;
    for (int index = 0; index < result->Count; index++) {
        token = result->Tokens[index];

        if (token->Kind == Number) {
            PushStack(numStack, token);
            lastWasNum = 1;
        }
        else if (token->Kind == OpenParan) {
            PushStack(opStack, token);
        }
        else if (token->Kind == CloseParan) {
            while (PopStack(opStack, &token) && token->Kind != OpenParan) {
                TokenKind op = token->Kind;

                if (op == UnaryMinus) {
                    if (!PeekStack(numStack, &token2)) {
                        printf("ERROR: Invalid expression\n");
                        return 0;
                    }

                    token2->Value *= -1;
                    continue;
                }
                
                if (!PopStack(numStack, &token2)) {
                    printf("ERROR: Invalid expression\n");
                    return 0;
                }

                double value = token2->Value;

                if (!PeekStack(numStack, &token2)) {
                    printf("ERROR: Invalid expression\n");
                    return 0;
                }

                if (op == Plus) {
                    token2->Value += value;
                }
                else if (op == Minus) {
                    token2->Value -= value;
                }
                else if (op == Star) {
                    token2->Value *= value;
                }
                else if (op == Slash) {
                    token2->Value /= value;
                }
                else if (op == Mod) {
                    token2->Value = token2->Value - (int)(token2->Value / value) * value;
                }
                else {
                    printf("ERROR: Unexpected operation type\n");
                    return 0;
                }
            }
        }
        else {
            if (!lastWasNum) {
                if (token->Kind == Plus) {
                    continue;
                }
                else if (token->Kind == Minus) {
                    token->Kind = UnaryMinus;
                }
            }

            while (PeekStack(opStack, &token2) && GetPrecedence(token2->Kind) >= GetPrecedence(token->Kind)) {
                PopStack(opStack, &token2);
                TokenKind op = token2->Kind;

                if (op == UnaryMinus) {
                    if (!PeekStack(numStack, &token2)) {
                        printf("ERROR: Invalid expression\n");
                        return 0;
                    }

                    token2->Value *= -1;
                    continue;
                }
                    
                if (!PopStack(numStack, &token2)) {
                    printf("ERROR: Invalid expression\n");
                    return 0;
                }

                double value = token2->Value;

                if (!PeekStack(numStack, &token2)) {
                    printf("ERROR: Invalid expression\n");
                    return 0;
                }

                if (op == Plus) {
                    token2->Value += value;
                }
                else if (op == Minus) {
                    token2->Value -= value;
                }
                else if (op == Star) {
                    token2->Value *= value;
                }
                else if (op == Slash) {
                    token2->Value /= value;
                }
                else if (op == Mod) {
                    token2->Value = token2->Value - (int)(token2->Value / value) * value;
                }
                else {
                    printf("ERROR: Unexpected operation type\n");
                    return 0;
                }
            }

            PushStack(opStack, token);
            lastWasNum = 0;
        }
    }

    while (PopStack(opStack, &token2)) {
        TokenKind op = token2->Kind;

        if (op == UnaryMinus) {
            if (!PeekStack(numStack, &token2)) {
                printf("ERROR: Invalid expression\n");
                return 0;
            }

            token2->Value *= -1;
            continue;
        }
        
        if (!PopStack(numStack, &token2)) {
            printf("ERROR: Invalid expression\n");
            return 0;
        }

        double value = token2->Value;

        if (!PeekStack(numStack, &token2)) {
            printf("ERROR: Invalid expression\n");
            return 0;
        }

        if (op == Plus) {
            token2->Value += value;
        }
        else if (op == Minus) {
            token2->Value -= value;
        }
        else if (op == Star) {
            token2->Value *= value;
        }
        else if (op == Slash) {
            token2->Value /= value;
        }
        else if (op == Mod) {
            token2->Value = token2->Value - (int)(token2->Value / value) * value;
        }
        else {
            printf("ERROR: Unexpected operation type\n");
            return 0;
        }
    }

    if (!PopStack(numStack, &token)) {
        return 0;
    }

    *outValue = token->Value;
    return 1;
}
