#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int ac, char **av) {
	if (ac == 1) {
		fprintf(stderr, "[print]: print {args}\n");
		return 1;
	}
	for (size_t i = 1; av[i]; i++) {
		for (size_t j = 0; av[i][j]; j++) {
			char a = av[i][j];
			char b = av[i][j + 1];
			size_t len = strlen(av[i]);
			if (a == '\\' && j < len) {
				if (b == 'n') {
					write(STDOUT_FILENO, "\n", 1);
					j += 1;
					continue;
				}
			}	
			write(STDOUT_FILENO, &a, 1);
		}
		write(STDOUT_FILENO, " ", 1);
	}
	write(STDOUT_FILENO, "\n", 1);
	return 0;
}
