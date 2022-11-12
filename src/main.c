#include <stdio.h>
#include <stdlib.h>
#include "../include/parser.h"
#include "../include/evaluator.h"

int main(int argc, char **argv) {
    char source[128];
    ParseResultRef result;
    double value;
    while (1) {
        printf("> ");
        gets(source);
        if (source[0] == 'q') {
            break;
        }
        else if (source[0] == 'c') {
            system("cls");
            continue;
        }

        result = ParseExpression(source);
        if (result && EvaluateResult(result, &value)) {
            printf("%lf\n", value);
        }

        DestroyResult(result);
    }

    return 0;
}
