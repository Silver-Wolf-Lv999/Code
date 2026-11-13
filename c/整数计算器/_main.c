#include <stdio.h>
#include <stdlib.h>
#define MAX_NUM 100

int _add(int, int);
int _mul(int, int);
int _sub(int, int);
int _div(int, int);


int main(void) {
	int 	numbers[MAX_NUM] = {0};
	int	result 		 = 0;
	char 	*operatorses[4]	 = {
		"+",
		"-",
		"*",
		"/"
	};
	int  	operators 	 = 0;
	printf("请输入两个数：\n");
	scanf("%d%d", &numbers[0], &numbers[1]);
	printf("请输入要用的运算符(1:add,2:sub,3:mul,4:div：\n");
	scanf("%d", &operators);
	switch (operators) {
		case 1:
			result = _add(numbers[0], numbers[1]);
			break;
		case 2:
			result = _sub(numbers[0], numbers[1]);
			break;
		case 3:
			result = _mul(numbers[0], numbers[1]);
			break;
		case 4:
			result = _div(numbers[0], numbers[1]);
			break;
		default:
			printf("ERROR");
			exit(EXIT_FAILURE);

	}
	printf("%d %s %d = %d", numbers[0], operatorses[operators - 1], numbers[1], result);

	return EXIT_SUCCESS;
}

int _add(int num_1, int num_2) {
	return num_1 + num_2;
}

int _mul(int num_1, int num_2) {
	return num_1 * num_2;
}

int _sub(int num_1, int num_2) {
	return num_1 - num_2;
}

int _div(int num_1, int num_2) {
	return num_1 / num_2;
}
