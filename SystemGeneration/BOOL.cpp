#include "BOOL.h"
#include <exception>

BOOL toBOOL(int a)
{
	if (a == 0) return FALSE;
	if (a == 1) return TRUE;
	throw std::exception("Incorrect argument for BOOL. Must be 0 or 1");
}