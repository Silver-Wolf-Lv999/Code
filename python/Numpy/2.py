import numpy as np;


numbers = np.array([3, 1, 2, 9, 4]);

len_array = numbers.size;
k = 2;
i = 0;
j = 0;
while i < len_array:
    if i > len_array - k:
        pass;
    i+=1;
print(numbers);
