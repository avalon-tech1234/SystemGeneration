#include "Polynomial.h"
#include <algorithm>

using namespace std;
using namespace polynomials;

void Polynomial::toString(string& out) const
{
	out.clear();
	if (terms.empty()) out = "0";
	else {
		auto it = terms.begin(), end = terms.end();
		(it++)->toString(out);
		while (it < end)
		{
			out += " + ";
			(it++)->toString(out);
		}
	}
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

	/*
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
	*/

	if (!terms.empty())
	{
		vector<Monomial> temp = move(terms);
		sort(temp.begin(), temp.end());

		size_t i = 0;
		while (i + 1 < temp.size())
		{
			if (temp[i] != temp[i + 1])
				terms.push_back(temp[i++]);
			else
				i += 2;
		}
		if (!terms.empty() && temp.back() != terms.back())
			terms.push_back(temp.back());

		terms = move(temp);
	}
}



