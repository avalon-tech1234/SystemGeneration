#include <algorithm>
#include "Monomial.h"
#include <string>

using namespace std;
using namespace polynomials;

Monomial::Monomial(vector<size_t>& in_grades)
{
	sort(in_grades.begin(), in_grades.end());

	vars.clear();
	if (!in_grades.empty()) {
		vars.push_back(in_grades[0]);
		size_t i = 1;
		while (i < in_grades.size())
		{
			if (in_grades[i] != in_grades[i - 1])
				vars.push_back(in_grades[i]);
			i++;
		}
	}

}


bool Monomial::operator<(const Monomial& m2) const
{
	if (size() > m2.size()) return true;
	if (size() < m2.size()) return false;
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

