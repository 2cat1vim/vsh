#ifndef LINK_H
#define LINK_H
/* this header purpose is to link to functions prototype,
 * across the project.
*/

void show_header();

t_opt* opt_handling(size_t _n, char **_args);
int prompt_loop(t_opt *_opt);

#endif
