#include "BOOL.h"
#include <exception>

BOOL toBOOL(int a)
{
	if (a == 0) return FALSE;
	if (a == 1) return TRUE;
	throw std::exception("Incorrect argument for BOOL. Must be 0 or 1");
}
BOOL toBOOL(size_t a)
{
	if (a == 0) return FALSE;
	if (a == 1) return TRUE;
	throw std::exception("Incorrect argument for BOOL. Must be 0 or 1");
}
BOOL toBOOL(long a)
{
	if (a == 0) return FALSE;
	if (a == 1) return TRUE;
	throw std::exception("Incorrect argument for BOOL. Must be 0 or 1");
}
BOOL toBOOL(double a)
{
	if (a == 0) return FALSE;
	if (a == 1) return TRUE;
	throw std::exception("Incorrect argument for BOOL. Must be 0 or 1");
}
BOOL toBOOL(bool a)
{
	if (a == false) return FALSE;
	if (a == true) return TRUE;
	throw std::exception("Incorrect argument for BOOL. Must be 0 or 1");
}
