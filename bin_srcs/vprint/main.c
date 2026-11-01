#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int ac, char **av) {
	if (ac == 1) {
		fprintf(stderr, "[vprint]: vprint {args}\n");
		return 1;
	}
	for (size_t i = 1; i < (size_t)ac; i++) {
		write(STDOUT_FILENO, av[i], strlen(av[i]));
		write(STDOUT_FILENO, " ", 1);
	}
	write(STDOUT_FILENO, "\n", 1);
	return 0;
}
