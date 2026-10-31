/* opt stand for options.
 * we parse the user selected options,
 * register them in t_opt, allocate and use them.
 * if there is any error during the process we will,
 * use our previous definitions to return them.
*/

#include "../incls/impl.h"

#define LIST_OPT_HELP 0
#define LIST_OPT_VERBOSE 1

int
opt_find(const char *_arg, const char ***list_opt) {
	for (size_t j = 0; list_opt[j]; j++) {
		for (size_t k = 0; list_opt[j][k]; k++) {
			if (strcmp(_arg, list_opt[j][k]) == 0) {
				return j;
			}
		}
	}
	return -1;
}

int
opt_parse(size_t _n, char **_args, t_opt *_opt) {
	const char *help[] = {"-?", "-h", "--help", NULL};
	const char *verbose[] = {"-v", "--verbose", NULL};
	const char **list_opt[] = {help, verbose, NULL};
	if (_n == NO_OPT) {
		_opt->o_flags |= NO_OPT;	
		return 0;
	}
	for (size_t i = 1; i < _n; i++) {
		switch (opt_find(_args[i], list_opt)) {
		case LIST_OPT_VERBOSE:
			_opt->o_flags |= VERBOSE_OPT;
			break;
		case LIST_OPT_HELP:
			free(_opt);
			fprintf(stdout, STDOUT_HELP);
			exit(EXIT_SUCCESS);
		default: 
			free(_opt);
			fprintf(stderr, STDERR_ARG_INC, _args[i]);	
			exit(EXIT_FAILURE);
		}
	}
	return 0;
}

t_opt*
opt_handling(size_t _n, char **_args) {
	t_opt *opt = calloc(1, sizeof(t_opt));
	if (!opt) {
		perror("calloc");
		exit(EXIT_FAILURE);
	}
	opt_parse(_n, _args, opt);
	return opt;
}
