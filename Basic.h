#ifndef _BASIC_H
#define _BASIC_H

#include <string.h>


#define BOOL int
#define TRUE 1
#define FALSE 0

#define INLINE static inline

#ifndef NULL
	#define NULL 0
#endif

#define min(a,b) \
	({ __typeof__ (a) _a = (a); \
	 __typeof__ (b) _b = (b); \
	 _a > _b ? _b : _a; })

#endif
