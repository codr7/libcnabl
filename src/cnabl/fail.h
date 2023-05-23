#ifndef FAIL_H
#define FAIL_H

#include <stdio.h>
#include <stdlib.h>

#define cl_fail(spec, ...)				\
  fprintf(stderr, "Failure in %s, line %d:\n" spec,	\
	  __FILE__, __LINE__, ##__VA_ARGS__);		\
  abort();					  

#endif
