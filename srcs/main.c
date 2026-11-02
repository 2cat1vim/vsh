/* vsh main file, this file is the start point.
 * no helper or any other function than main(),
 * can be there.
 * keep this file simple and always redirect,
 * to comprehensible functions and workflow.
 * if you contribute to vsh, follow my code style.
*/

#include "../incls/impl.h"

int
main(int _ac, char **_av, char **e) {
	/* Parse the options >
	 * Register them into t_opt >
	 * Allocate and use.
	 */
	t_env *env;
	env = env_handling(e);
	(void)env;
	t_opt *opt;
	opt = opt_handling(_ac, _av);
	(void)opt;
	prompt_loop(opt);
	free(opt);
}
