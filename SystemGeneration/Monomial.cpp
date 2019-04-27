#include <algorithm>
#include "Monomial.h"
#include <string>

using namespace std;
using namespace polynomials;

Monomial::Monomial(vector<size_t> in_grades)
{
	sort(in_grades.begin(), in_grades.end());
	vars = move(in_grades);

	size_t i = 0;
	while (i + 1 < vars.size())
	{
		if (vars[i] = vars[i + 1])
			vars.erase(vars.begin() + i);
		i++;
	}
	int kek = 0;
}


bool Monomial::operator<(const Monomial& m2) const
{
	if (size() > size()) return true;
	if (size() < size()) return false;
	for (size_t i = 0; i < size(); i++)
	{
		if (operator[](i) > m2[i]) return false;
		if (operator[](i) < m2[i]) return true;
	}
	return false;
}


BOOL Monomial::substitute(const vector<BOOL> values) const
{
	size_t s = size();
	for (size_t i = 0; i < s; i++)
	{
		if (values[operator[](i)] == FALSE) 
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

