#include "../incls/impl.h"

typedef struct s_in {
	char **cmd;
	//s_in *prev; Necessary when i will add pipeline
	//s_in *next;
} t_in;

int parse_in(const char *_line, t_in *_in) {
	_in->cmd = calloc(16, sizeof(char*));
	if (!_in->cmd) {
		perror("calloc");
		exit(EXIT_FAILURE);
	}
	char **ptr = _in->cmd;
	while (*_line) {
		*ptr = calloc(32, sizeof(char));
		if (!*ptr) {
			free(_in->cmd);
			perror("calloc");
			exit(EXIT_FAILURE);
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

// Need to add the define of return in a dedicated header
// 10 will be ref to CMD not found; MAGIC NUMBER for the moment.
#define COMMAND_NOT_FOUND 10
#define BIN_PATH ".bin/"
#define PROMPT_END "$ "
#define LPROMPT_END (sizeof(PROMPT_END) - 1)
#define PROMPT_LINK "@"
#define LPROMPT_LINK (sizeof(PROMPT_LINK) - 1)
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
prompt_loop(t_global *_gbl) {
	t_in *in = calloc(1, sizeof(t_in));
	if (!in) {
		perror("calloc");
		exit(EXIT_FAILURE);
	}
	show_header();
	
	char *prompt = NULL;
	long int cn = -1;
	while (1) {
		long int n = ((long int)LPROMPT_END + (long int)LPROMPT_LINK +
				strlen(_gbl->env->user) + strlen(_gbl->env->pwd) + 1);
		if (cn < n) {
			cn = n;
			char *p = realloc(prompt, n);
			if (!p) {
				free(prompt);
				perror("realloc");
				exit(EXIT_FAILURE);
			}
			prompt = p;
		}
		snprintf(prompt, cn, "%s%s%s%s",
				_gbl->env->user, PROMPT_LINK, _gbl->env->pwd, PROMPT_END);

		char *line = readline(prompt);
		if (!line) {
			free(line);
			free(prompt);
			exit(EXIT_SUCCESS);
		}
		if (*line == '\0') {
			free(line);
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
