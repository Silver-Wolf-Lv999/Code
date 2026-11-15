import numpy as np


str = 'hello';
b = str.encode('utf-8');
part = [];
parts = [];
for byte in b:
    part.append(f'{byte:032b}');
for bytes in part:
    for byte in bytes:
        parts.append(byte);

k = 2;
array = np.array(parts);
len_array = array.size;

i = 0;
t = 0;

print(len_array);
print(array);
