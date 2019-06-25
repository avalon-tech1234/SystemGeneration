#pragma once

typedef int BOOL;
#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

BOOL toBOOL(int a);
BOOL toBOOL(size_t a);
BOOL toBOOL(long a);
BOOL toBOOL(double a);
BOOL toBOOL(bool a);
