s = '汉'
b = s.encode('utf-8')          # b'\xe6\xb1\x89'
bin_str = ''.join(f'{byte:08b}' for byte in b)
print(bin_str)                 # 111001101011000110001001
