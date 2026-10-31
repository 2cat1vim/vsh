#include "../incls/impl.h"

typedef struct s_in {
	char **cmd;
	//s_in *prev; Necessary when i will add pipeline
	//s_in *next;
} t_in;

int parse_in(const char *_line, t_in *_in) {
	_in->cmd = calloc(16, sizeof(char*));
	if (!_in->cmd) {
		exit(EXIT_SUCCESS);
	}
	char **ptr = _in->cmd;
	while (*_line) {
		*ptr = calloc(32, sizeof(char));
		if (!*ptr) {
			free(_in->cmd);
			exit(EXIT_SUCCESS);
		}
		char *cptr = *ptr;
		while (!isspace(*_line) && *_line) {
			*cptr++ = *_line++;
		}
		if (isspace(*_line)) {
			_line++;
		}
		*cptr = '\0';
		ptr++;
	}
	return 0;
}

int dispatch_in(t_in *_in) {
	fprintf(stderr, STDERR_UKW_CMD, _in->cmd[0]);
	printf("alive\n");
	return 0;
}

int
prompt_loop(t_opt *_opt) {
	(void)_opt;
	t_in *in = calloc(1, sizeof(t_in));
	while (1) {
		char *line = readline("vsh-1.0$ ");
		if (!line) {
			free(line);
			exit(EXIT_SUCCESS);
		}
		if (strcmp(line, "exit") == 0) {
			exit(EXIT_SUCCESS);
		}
		parse_in(line, in);
		dispatch_in(in);
		free(line);
	}
	return 0;
}
