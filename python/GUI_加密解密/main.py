import math

class information:
    def __init__(self, encrupt: str) -> None:
        self.encryption = encrupt;


    def __encrupt(self, str_len) -> None:
        self.x = str_len;
        self.y = self.x ** 2 + self.x + 1;
        self.move = int(abs(self.y) * 10) % 10;
        bytes = self.encryption.encode('utf-8');
        parts = []
        for byte in bytes:
            parts.append(f'{byte:08b}');





def main() -> None:
    encrypt_information: information = information(input("请输入加密信息："));

    print(encrypt_information.encryption);


if __name__ == "__main__":
    main();
