#include "../incls/impl.h"

t_env*
env_handling(char **_env) {
	t_env *env = calloc(1, sizeof(t_env));
	if (!env) {
		perror("calloc");
		exit(EXIT_SUCCESS);
	}
	for (size_t i = 0; _env[i]; i++) {
		if (strncmp(_env[i], "PWD=", 4) == 0) {
			env->pwd = strdup(_env[i] + 4);
		}
		else if (strncmp(_env[i], "USERNAME=", 9) == 0) {
			env->user = strdup(_env[i] + 9);
		}
		else if (strncmp(_env[i], "HOME=", 5) == 0) {
			env->home = strdup(_env[i] + 5);
		}
	}
	printf("user: %s, pwd: %s, home: %s\n", env->user, env->pwd, env->home);
	return env;
}
