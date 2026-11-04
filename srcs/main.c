/* vsh main file, this file is the start point.
 * no helper or any other function than main(),
 * can be there.
 * keep this file simple and always redirect,
 * to comprehensible functions and workflow.
 * if you contribute to vsh, follow my code style.
*/

#include "../incls/impl.h"

int
main(int _ac, char **_av, char **_env) {
	/* Parse the options >
	 * Register them into t_opt >
	 * Allocate and use.
	 */
	t_global *gbl = calloc(1, sizeof(t_global));
	if (!gbl) {
		perror("calloc");
		exit(EXIT_FAILURE);
	}
	gbl->env = calloc(1, sizeof(t_env)), gbl->flags = 0;
	if (!gbl->env) {
		free(gbl);
		perror("calloc");
		exit(EXIT_FAILURE);
	}
	gbl->env = env_handling(_env);
	gbl->flags = opt_handling(_ac, _av);
	prompt_loop(gbl);
	/* free all */
}
