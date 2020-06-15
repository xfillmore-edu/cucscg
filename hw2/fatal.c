/* Error catching routine */

#include "config.h"

/* copied directly from ex10/Fatal.c */
void fatal(const char* format , ...)
{
   va_list args;
   va_start(args,format);
   vfprintf(stderr,format,args);
   va_end(args);
   exit(1);
}