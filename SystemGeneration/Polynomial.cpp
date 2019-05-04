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

		terms.push_back(temp[0]);
		for (size_t i = 1; i < temp.size(); i++)
		{
			if (temp[i] == terms.back()) 
				terms.pop_back();
			else 
				terms.push_back(temp[i]);
		}

		// terms = move(temp); - вроде эта строка здесь неспроста, но зачем?..
	}
}



