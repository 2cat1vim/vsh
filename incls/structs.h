#ifndef STRUCTS
#define STRUCTS

typedef struct s_env {
	char *pwd;
	char *user;
	char *home;
} t_env;

// flags:
#define NO_OPT (1u << 0)
#define VERBOSE_OPT (1u << 1)
typedef struct s_global {
	unsigned int flags;
	t_env *env;
} t_global;

#endif
