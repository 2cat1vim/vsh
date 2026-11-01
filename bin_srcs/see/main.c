#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>	
#include <fcntl.h>

int main(int ac, char **av) {
	(void)av;
	if (ac < 2) {
		fprintf(stderr, "[see]: see {files}\n");
	}
	for (size_t i = 1; av[i]; i++) {
		fprintf(stdout, "\n%s:\n", av[i]);
		int fd = open(av[i], O_RDONLY, 0);
		if (fd == -1) {
			perror("open");
			exit(EXIT_SUCCESS);
		}
		ssize_t r = -1;
		size_t rl = 0;
		char full[5047];
		while (1) {
			char buf;
			r = read(fd, &buf, 1);
			if (r == -1) {
				perror("read");
				exit(EXIT_SUCCESS);
			}
			if (r == 0) {
				break;
			}
			full[rl] = buf;
			rl += r;
		}
		full[rl] = '\0';
		ssize_t w = write(STDOUT_FILENO, full, rl);
		if (w == -1) {
			perror("write");
			exit(EXIT_SUCCESS);
		}
	}
}
