#include "BOOL.h"

BOOL toBOOL(int a)
{
	if (a == 0)
		return FALSE;
	else
		return TRUE;
}
BOOL toBOOL(size_t a)
{
	if (a == 0)
		return FALSE;
	else
		return TRUE;
}
BOOL toBOOL(long a)
{
	if (a == 0)
		return FALSE;
	else
		return TRUE;
}
BOOL toBOOL(double a)
{
	if (a == 0)
		return FALSE;
	else
		return TRUE;
}
BOOL toBOOL(bool a)
{
	if (a == 0)
		return FALSE;
	else
		return TRUE;
}
