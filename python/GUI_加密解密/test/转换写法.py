str = 'hello';
b = str.encode('utf-8');
parts = []
for byte in b:
    parts.append(f'{byte:08b}');
move = 2;
part_2 = [];
print(parts)
i = 0;
for part in parts:
    len_list = len(part);
    for k in part:
        part_2[i+move] = k;
        i+=1;
        if (i == len_list):
            i = 0;

print(part_2);
