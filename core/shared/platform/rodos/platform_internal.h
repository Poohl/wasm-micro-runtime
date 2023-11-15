
#pragma once

#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <stdlib.h>
#include <math.h>

//#define snprintf SNPRINTF
//#define printf PRINTF

typedef uint32_t korp_tid;


// TODO
typedef unsigned int korp_mutex;
typedef uint32_t korp_cond;
typedef uint32_t korp_sem;
void abort(void);
int snprintf(char*, size_t, const char*, ...);
//int vsnprintf(char*, unsigned long, const char*, struct __va_list_tag*);
