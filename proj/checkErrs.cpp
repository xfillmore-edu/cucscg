/* Error checking Function */

#include "config.hpp"
#include <cstring>

/* takes string of function name as argument */
void checkErrs (std::string fn)
{
    int err = glGetError();
    if (err)
    {
        int n = fn.length();
        char c[n+1];
        strcpy(c, fn.c_str());
        fprintf (stderr, "ERROR: %s in function <%s>.\n", gluErrorString(err), c);
    }
}