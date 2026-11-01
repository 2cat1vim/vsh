#include <stdio.h>

int main(int ac, char **av) {
	(void)av;
	if (ac < 2) {
		fprintf(stderr, "[see]: see {files}\n");
	}
}
