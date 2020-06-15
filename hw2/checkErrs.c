/* Error checking Function */

#include "config.h"

/* takes string of function name as argument */
void checkErrs (char* fn)
{
    int err = glGetError();
    if (err)
    {
        fprintf (stderr, "ERROR: %s in function <%s>.\n", gluErrorString(err), fn);
    }
}