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

unsigned int
opt_parse(size_t _n, char **_args) {
	const char *help[] = {"-?", "-h", "--help", NULL};
	const char *verbose[] = {"-v", "--verbose", NULL};
	const char **list_opt[] = {help, verbose, NULL};
	unsigned int flags = 0;
	if (_n == NO_OPT) {
		flags |= NO_OPT;	
		return flags;
	}
	for (size_t i = 1; i < _n; i++) {
		switch (opt_find(_args[i], list_opt)) {
		case LIST_OPT_VERBOSE:
			flags |= VERBOSE_OPT;
			break;
		case LIST_OPT_HELP:
			fprintf(stdout, STDOUT_HELP);
			exit(EXIT_SUCCESS);
		default: 
			fprintf(stderr, STDERR_ARG_INC, _args[i]);	
			exit(EXIT_FAILURE);
		}
	}
	return flags;
}

unsigned int
opt_handling(size_t _n, char **_args) {
	return opt_parse(_n, _args);
}
