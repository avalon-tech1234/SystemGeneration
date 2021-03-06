#include "Monomial.h"
#include <algorithm>
#include <string>

using namespace std;
using namespace polynomials;

void Monomial::simplify()
{
	if (!vars.empty())
	{
		vector<int> temp = move(vars);
		sort(temp.begin(), temp.end());

		vars.push_back(temp[0]);
		int sz = (int) temp.size();
		for (int i = 1; i < sz; i++)
		{
			if (temp[i] != vars.back())
				vars.push_back(temp[i]);
		}

		temp.clear();

	}

	n_max = 0;
	std::vector<int>::iterator it = std::max_element(vars.begin(), vars.end());
	if (it != vars.end())
		n_max = *it;
	else {
		//_ASSERT(FALSE);
	}



}


bool Monomial::operator<(const Monomial& m2) const
{
	if (size() > m2.size()) return true;
	if (size() < m2.size()) return false;
	for (int i = 0; i < size(); i++)
	{
		if (vars[i] > m2[i]) return false;
		if (vars[i] < m2[i]) return true;
	}
	return false;
}


BOOL Monomial::substitute(const vector<BOOL>& values) const
{
	int s = size();
	for (int i = 0; i < s; i++)
	{
		if (values[vars[i]] == FALSE)
			return FALSE;
	}
	return TRUE;
}

void Monomial::toString(string& out) const
{
	int size_beg = (int)out.size();
	for (auto it = vars.begin(); it != vars.end(); it++)
	{
		out += "x" + to_string(*it);
	}
	if (out.size() == size_beg)
		out += "1";
}

