#include <stdio.h>
#include <stdlib.h>
#define MAX_B 32

void gui(int *, int *);
int conversion(char *, int, int);
void to_char(char *, int);

int main(void) {
    char bit[MAX_B] = {0};
    int num = 0;
    int len = 0;
    int chioce = 0;
    gui(&chioce, &num);


    len = conversion(bit, num, chioce);
    to_char(bit, len);

    for (int i = len - 1; i >= 0; i--) {
        printf("%c", bit[i]);
    }

    return EXIT_SUCCESS;
}

int conversion(char *ptr, int num, int option) {
    int i = 0;
    int t = num;
    if (option) {
        while (t) {
            *(ptr + i) = t % option;
            t /= option;
            i++;
        }
    } else {
        exit(EXIT_SUCCESS);
    }

    return i;
}

void to_char(char *ptr, int len) {
    for (int i = 0; i < len; i++) {
        if (*(ptr + i) < 10) {
            *(ptr + i) = *(ptr + i) + '0';
        } else {
            *(ptr + i) = (*(ptr + i) - 10) + 'A';
        }
    }
}

void gui(int *chioce, int *num) {
    printf("============================\n");
    printf("==  欢迎，使用进制转换器  ==\n");
    printf("============================\n");
    printf("请输入进制，目前支持36进制:\n");
    scanf("%d", chioce);
    printf("请输入要转的数值:\n");
    scanf("%d", num);
}
