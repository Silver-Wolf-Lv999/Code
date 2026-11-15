#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""任意进制转换器

支持 2~62 进制的整数与小数互转。
数字字符表:0-9(0~9)、A-Z(10~35)、a-z(36~61),大小写不敏感(除 36 进制以上)。

用法:
    1. 交互模式:      python base_converter.py
    2. 命令行一次性转换: python base_converter.py <数值> <原进制> <目标进制>
       例如:python base_converter.py 255 10 16  ->  FF
"""

import sys

# 2~62 进制通用的数字字符表
DIGITS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
CHAR_MAP = {ch: idx for idx, ch in enumerate(DIGITS)}


def _check_base(base: int) -> None:
    if not (2 <= base <= 62):
        raise ValueError(f"进制必须在 2~62 之间,收到:{base}")


def _to_int(char: str, base: int) -> int:
    """把单个数字字符按给定进制解释成整数(大小写不敏感)。"""
    value = CHAR_MAP.get(char)
    upper_value = CHAR_MAP.get(char.upper())
    # 大小写不敏感:base ≤ 36 时,小写字母按大写字母的值处理
    if upper_value is not None and (value is None or value >= base) and upper_value < base:
        value = upper_value
    if value is None or value >= base:
        raise ValueError(f"字符 '{char}' 不是合法的 {base} 进制数字")
    return value


def to_decimal(number: str, base: int) -> str:
    """把 base 进制的字符串转成十进制字符串(支持小数)。"""
    _check_base(base)
    number = number.strip()
    if not number:
        raise ValueError("输入为空")

    negative = number[0] in "+-"
    if number[0] in "+-":
        number = number[1:]

    integer_part, _, fraction_part = number.partition(".")

    # 整数部分:按位权累加
    int_value = 0
    for ch in integer_part:
        int_value = int_value * base + _to_int(ch, base)

    if not fraction_part:
        result = str(int_value)
    else:
        # 小数部分:乘以 base 累加
        frac_value = 0.0
        weight = 1.0
        for ch in fraction_part:
            weight /= base
            frac_value += _to_int(ch, base) * weight
        result = f"{int_value + frac_value:.15f}".rstrip("0").rstrip(".")

    return ("-" if negative else "") + result


def from_decimal(number: str, base: int, precision: int = 10) -> str:
    """把十进制字符串(支持小数)转成 base 进制字符串。"""
    _check_base(base)
    number = number.strip()
    if not number:
        raise ValueError("输入为空")

    negative = number[0] in "+-"
    if negative:
        number = number[1:]

    integer_part, _, fraction_part = number.partition(".")
    int_value = int(integer_part) if integer_part else 0

    if int_value == 0:
        int_str = "0"
    else:
        chars = []
        while int_value:
            int_value, rem = divmod(int_value, base)
            chars.append(DIGITS[rem])
        int_str = "".join(reversed(chars))

    if not fraction_part:
        result = int_str
    else:
        frac_value = float("0." + fraction_part)
        chars = []
        for _ in range(precision):
            frac_value *= base
            digit = int(frac_value)
            chars.append(DIGITS[digit])
            frac_value -= digit
            if frac_value <= 0:
                break
        # 去掉末尾多余的 0
        while chars and chars[-1] == "0":
            chars.pop()
        result = int_str + ("." + "".join(chars) if chars else "")

    return ("-" if negative else "") + result


def convert(number: str, from_base: int, to_base: int, precision: int = 10) -> str:
    """任意进制互转:先转成十进制,再转成目标进制。"""
    return from_decimal(to_decimal(number, from_base), to_base, precision)


def parse_base(text: str) -> int:
    try:
        return int(text)
    except ValueError:
        raise ValueError(f"进制必须是整数,收到:{text!r}")


def interactive() -> None:
    print("=" * 46)
    print("          任意进制转换器 (2 ~ 62 进制)")
    print("  字符表:0-9, A-Z(10~35), a-z(36~61)")
    print("=" * 46)
    while True:
        try:
            number = input("\n请输入要转换的数值(直接回车退出): ").strip()
            if not number:
                print("已退出,再见!")
                break
            from_base = parse_base(input("原进制 (2~62): "))
            to_base = parse_base(input("目标进制 (2~62): "))
            print(f"\n结果:{number}({from_base}) = {convert(number, from_base, to_base)}({to_base})")
        except ValueError as e:
            print(f"输入有误:{e}")


def main() -> None:
    if len(sys.argv) == 4:
        # 命令行模式
        try:
            result = convert(sys.argv[1], parse_base(sys.argv[2]), parse_base(sys.argv[3]))
            print(result)
        except ValueError as e:
            print(f"错误:{e}", file=sys.stderr)
            sys.exit(1)
    else:
        interactive()


if __name__ == "__main__":
    main()
