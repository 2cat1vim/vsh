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

#define COMMAND_NOT_FOUND 10
#define BIN_PATH ".bin/"
int dispatch_in(t_in *_in) {
	char *p = malloc(sizeof(char) * strlen(_in->cmd[0]) + strlen((const char*)BIN_PATH) + 1);
	if (!p) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	strcpy(p, (const char*)BIN_PATH);
	strcat(p, _in->cmd[0]);

	int status;
	pid_t pid = fork();
	switch (pid) {
	case -1:
		perror("fork");
		exit(EXIT_FAILURE);
	case 0:
		execv(p, _in->cmd);
		fflush(stdout);
		_exit(COMMAND_NOT_FOUND);
	default:
		if (waitpid(pid, &status, 0) == -1) {
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		if (WEXITSTATUS(status) == COMMAND_NOT_FOUND) {			
			fprintf(stderr, STDERR_UKW_CMD, _in->cmd[0]);
		}
		break;
	}
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
		if (strlen(line) == 0) {
			continue;
		}
		if (strcmp(line, "exit") == 0) {
			exit(EXIT_SUCCESS);
		}
		parse_in(line, in);
		dispatch_in(in);
		add_history(line);
		free(line);
	}
	return 0;
}
