/*
 * 任意进制转换器 (C11) —— 仅整数
 *
 * 支持 2~62 进制的整数互转。
 * 字符表:0-9(0~9)、A-Z(10~35)、a-z(36~61)。
 * 36 进制以内大小写不敏感。
 *
 * 用法:
 *   ./base_converter                      交互模式
 *   ./base_converter <数值> <原进制> <目标进制>
 *   例如: ./base_converter 255 10 16   ->  FF
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define MAX_OUT 512     /* 输出缓冲区大小 */
#define DIGIT_CHARS "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

/* 返回字符 c 的数值,非法字符返回 -1 */
static int char_value(int c, int base)
{
    const char *pos = strchr(DIGIT_CHARS, (char)toupper((unsigned char)c));
    const char *losp = strchr(DIGIT_CHARS, (char)c);
    int low, up;

    if (pos != NULL && (pos - DIGIT_CHARS) < base)
        return (int)(pos - DIGIT_CHARS);
    /* 大小写不敏感:base <= 36 时,小写字母按大写字母处理 */
    if (losp == NULL)
        return -1;
    low = (int)(losp - DIGIT_CHARS);
    up = (pos == NULL) ? -1 : (int)(pos - DIGIT_CHARS);
    if (up >= 0 && up < base)
        return up;
    if (low < base)
        return low;
    return -1;
}

/* 把 base 进制字符串转成十进制 long long,失败返回 0 并置 *ok=0 */
static long long to_decimal(const char *s, int base, int *ok)
{
    long long value = 0;
    int negative = 0;

    *ok = 1;
    if (base < 2 || base > 62) { *ok = 0; return 0; }
    if (*s == '\0')            { *ok = 0; return 0; }

    if (*s == '+' || *s == '-') {
        negative = (*s == '-');
        s++;
    }
    if (*s == '\0')            { *ok = 0; return 0; }

    for (; *s != '\0'; s++) {
        int v = char_value(*s, base);
        if (v < 0) { *ok = 0; return 0; }
        if (value > (LLONG_MAX - v) / base) {   /* 溢出检查 */
            printf("错误: 数值超出 64 位范围\n");
            *ok = 0;
            return 0;
        }
        value = value * base + v;
    }
    return negative ? -value : value;
}

/* 把十进制整数 n 转成 base 进制字符串,失败返回 NULL */
static const char *from_decimal(long long n, int base, char *out, size_t outsize)
{
    char buf[MAX_OUT];
    char *p = out;
    int i = 0;
    unsigned long long un;

    if (base < 2 || base > 62 || outsize < 4)
        return NULL;

    if (n < 0) {
        *p++ = '-';
        un = (unsigned long long)(-(n + 1)) + 1;    /* 避免对 LLONG_MIN 取负溢出 */
    } else {
        un = (unsigned long long)n;
    }

    /* 反复除 base 取余(低位在前) */
    do {
        buf[i++] = DIGIT_CHARS[un % (unsigned long long)base];
        un /= (unsigned long long)base;
    } while (un > 0);

    /* 反转写入输出 */
    while (i > 0 && p < out + outsize - 1)
        *p++ = buf[--i];
    *p = '\0';
    return out;
}

/* 任意进制互转,失败返回 NULL */
static const char *convert(const char *number, int from_base, int to_base,
                           char *out, size_t outsize)
{
    int ok;
    long long dec = to_decimal(number, from_base, &ok);
    if (!ok)
        return NULL;
    return from_decimal(dec, to_base, out, outsize);
}

static int read_base(const char *prompt)
{
    int base = 0;
    printf("%s", prompt);
    if (scanf("%d", &base) != 1 || base < 2 || base > 62) {
        printf("进制必须是 2~62 之间的整数!\n");
        /* 清空输入缓冲区 */
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        return 0;
    }
    return base;
}

static void interactive(void)
{
    char number[128], out[MAX_OUT];
    int from_base, to_base;
    const char *result;

    printf("================================================\n");
    printf("       任意进制转换器 (2 ~ 62 进制, 整数)\n");
    printf("  字符表: 0-9, A-Z(10~35), a-z(36~61)\n");
    printf("================================================\n");

    while (1) {
        printf("\n请输入要转换的整数(直接回车退出): ");
        number[0] = '\0';
        scanf("%127s", number);
        if (number[0] == '\0' || strcmp(number, "q") == 0 || strcmp(number, "Q") == 0) {
            printf("已退出,再见!\n");
            break;
        }
        from_base = read_base("原进制 (2~62): ");
        if (from_base == 0)
            continue;
        to_base = read_base("目标进制 (2~62): ");
        if (to_base == 0)
            continue;

        result = convert(number, from_base, to_base, out, sizeof(out));
        if (result != NULL)
            printf("\n结果: %s(%d) = %s(%d)\n", number, from_base, result, to_base);
        else
            printf("输入有误: '%s' 不是合法的 %d 进制整数\n", number, from_base);

        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }
}

int main(int argc, char *argv[])
{
    char out[MAX_OUT];
    const char *result;

    if (argc == 4) {
        int from_base = atoi(argv[2]);
        int to_base = atoi(argv[3]);
        if (from_base < 2 || from_base > 62 || to_base < 2 || to_base > 62) {
            fprintf(stderr, "错误: 进制必须在 2~62 之间\n");
            return 1;
        }
        result = convert(argv[1], from_base, to_base, out, sizeof(out));
        if (result == NULL) {
            fprintf(stderr, "错误: '%s' 不是合法的 %d 进制整数\n", argv[1], from_base);
            return 1;
        }
        printf("%s\n", result);
    } else {
        interactive();
    }
    return 0;
}
