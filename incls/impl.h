#ifndef IMPL_H
#define IMPL_H
/* this header is the global, every other header are,
 * grouped here so you can always just call impl.h.
*/

#include "structs.h"
#include "extern.h"
#include "link.h"
#define STDOUT_HELP \
	"[vsh]: ./vsh [options]\n -? | -h | -help	get this message\n"
#define STDERR_ARG_INC \
       	"[vsh]: incorrect option `%s` : ./vsh -?\n"
#define STDERR_UKW_CMD \
	"[vzh]: unknown command `%s`\n"
#endif
