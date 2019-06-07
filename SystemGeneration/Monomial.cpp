#include "Monomial.h"
#include <algorithm>
#include <string>

using namespace std;
using namespace polynomials;

void Monomial::simplify()
{
	if (!vars.empty())
	{
		vector<size_t> temp = move(vars);
		sort(temp.begin(), temp.end());

		vars.push_back(temp[0]);
		size_t sz = temp.size();
		for (size_t i = 1; i < sz; i++)
		{
			if (temp[i] != vars.back())
				vars.push_back(temp[i]);
		}

		temp.clear();

	}
	n_max = *std::max_element(vars.begin(), vars.end());


}


bool Monomial::operator<(const Monomial& m2) const
{
	if (size() > m2.size()) return true;
	if (size() < m2.size()) return false;
	for (size_t i = 0; i < size(); i++)
	{
		if (vars[i] > m2[i]) return false;
		if (vars[i] < m2[i]) return true;
	}
	return false;
}


BOOL Monomial::substitute(const vector<BOOL>& values) const
{
	size_t s = size();
	for (size_t i = 0; i < s; i++)
	{
		if (values[vars[i]] == FALSE)
			return FALSE;
	}
	return TRUE;
}

void Monomial::toString(string& out) const
{
	size_t size_beg = out.size();
	for (auto it = vars.begin(); it != vars.end(); it++)
	{
		out += "x" + to_string(*it);
	}
	if (out.size() == size_beg)
		out += "1";
}

