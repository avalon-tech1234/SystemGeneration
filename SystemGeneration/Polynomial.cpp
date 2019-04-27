#include "Polynomial.h"
#include <algorithm>

using namespace std;
using namespace polynomials;

void Polynomial::toString(string& out) const
{
	out = "";
	string cur;
	for (auto it = begin(); it != end(); it++)
	{
		if (it == begin())
			out += " ";
		else
			out += " + ";
		it->toString(out);
	}
	if (out == "") out = " 0";
}

BOOL Polynomial::substitute(const vector<BOOL> values) const
{
	BOOL result = FALSE;
	size_t s = size();
	for (size_t i = 0; i < s; i++)
	{
		result ^= operator[](i).substitute(values);
	}
	return result;
}

void Polynomial::simplify()
{
	std::sort(begin(), end());

	size_t i = 0;
	while (i + 1 < size())
	{
		if (operator[](i) == operator[](i + 1))
		{
			erase(begin() + i);
			erase(begin() + i);
		}
		i++;
	}
}



