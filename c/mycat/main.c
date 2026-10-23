#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "用法: %s 文件名\n", argv[0]);
		return EXIT_FAILURE;
	}
	FILE *file;
	int i = 1;
	while (*file = fopen(argv[i], "r") && i < argc) {

		if (file == NULL) {
			perror(argv[1]);
			return EXIT_FAILURE;
		}

		int ch;
		while ((ch = fgetc(file)) != EOF) {
			putchar(ch);
		}

		if (ferror(file)) {
			perror(argv[1]);
			fclose(file);
			return EXIT_FAILURE;
		}

		i++;
	}

	if (fclose(file) == EOF) {
		perror(argv[1]);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
