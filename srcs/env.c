#include "../incls/impl.h"

t_env*
env_handling(char **e) {
	t_env *env = calloc(1, sizeof(t_env));
	if (!env) {
		perror("calloc");
		exit(EXIT_SUCCESS);
	}
	for (size_t i = 0; e[i]; i++) {
		if (strncmp(e[i], "PWD=", 4) == 0) {
			env->pwd = strdup(e[i] + 4);
		}
		else if (strncmp(e[i], "USERNAME=", 9) == 0) {
			env->user = strdup(e[i] + 9);
		}
		else if (strncmp(e[i], "HOME=", 5) == 0) {
			env->home = strdup(e[i] + 5);
		}
	}
	printf("user: %s, pwd: %s, home: %s\n", env->user, env->pwd, env->home);
	return env;
}
