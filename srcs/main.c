/* vsh main file, this file is the start point.
 * no helper or any other function than main(),
 * can be there.
 * keep this file simple and always redirect,
 * to comprehensible functions and workflow.
 * if you contribute to vsh, follow my code style.
*/

#include "../incls/impl.h"

int
main(int _ac, char **_av) {
	/* Parse the options >
	 * Register them into t_opt >
	 * Allocate and use.
	 */
	t_opt *opt;
	opt = opt_handling(_ac, _av);
	(void)opt;
}
