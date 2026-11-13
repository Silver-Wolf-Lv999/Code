#include "stdio.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#define MAX_EX 50
#define MAX_RESULT 25

int result = 0;

int __add(int, int);
int __sub(int, int);
int __mul(int, int);
int __div(int, int);
void calculation_process(char *, int);

int main(void) {
    char ex[MAX_EX];
    size_t len_process = 0;
    size_t len_result = 0;

    fgets(ex, MAX_EX, stdin);

    len_process = strlen(ex);
    calculation_process(ex, len_process);

    printf("最后结果为：%d", result);

    return 0;

}

void calculation_process(char *formula, int len_process) {
    int num = 0;
    result = formula[0] - '0';
    for (int i = 1; i < len_process; i+=2) {
        if (formula[0] == '+' || formula[0] == '*' || formula[0] == '-' || formula[0] == '/' ) {
            fputs("第一行不是数字", stderr);
            exit(EXIT_FAILURE);
        } else {
            formula[i + 1] = formula[i + 1] - '0';
            switch (formula[i]) {
                case '+':
                    result = __add(result, formula[i+1]);
                    break;
                case '-':
                    result = __sub(result, formula[i+1]);
                    break;
                case '*':
                    result = __mul(result, formula[i+1]);
                    break;
                case '/':
                    result = __div(result, formula[i+1]);
                    break;
            }
        }
    }
}

int __add(int num_1, int num_2) {
    return num_1 + num_2;
}

int __sub(int num_1, int num_2) {
    return  num_1 - num_2;
}

int __mul(int num_1, int num_2) {
    return  num_1 * num_2;
}

int __div(int num_1, int num_2) {
    return  num_1 / num_2;
}
