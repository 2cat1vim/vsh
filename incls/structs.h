#ifndef STRUCTS
#define STRUCTS

// o_flags:
#define NO_OPT (1u << 0)
#define VERBOSE_OPT (1u << 1)
typedef struct s_opt {
	unsigned int o_flags;
} t_opt;

typedef struct s_env {
	char *pwd;
	char *user;
	char *home;
} t_env;

#endif
