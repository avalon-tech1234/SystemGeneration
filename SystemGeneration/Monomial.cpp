#include <algorithm>
#include "Monomial.h"


using namespace std;

namespace polynomials
{
	Monomial::Monomial(vector<size_t> in_grades)
	{
		sort(in_grades.begin(), in_grades.end());
		vars = std::move(in_grades);

		/*
		vector<size_t>::iterator it, itprev = vars.begin();
		for (it = vars.begin() + 1; it != vars.end(); it++)
		{
			if (*itprev == *it)
				it = --vars.erase(it);
			itprev = it;
		}
		*/
		size_t i = 0;
		while (i + 1 < vars.size())
		{
			if (vars[i] = vars[i+1])
				vars.erase(vars.begin()+i);
			i++;
		}
		int kek = 0;
	}


	// 0 равны, 1 первый больше, -1 второй больше
	bool compare(const Monomial& m1, const Monomial& m2)
	{
		if (m1.size() > m2.size()) return true;
		if (m1.size() < m2.size()) return false;
		for (size_t i = 0; i < m1.size(); i++)
		{
			if (m1[i] > m2[i]) return false;
			if (m1[i] < m2[i]) return true;
		}
		return false;
	}


	BOOL Monomial::substitute(const vector<BOOL> values) const
	{
		size_t s = size();
		for (size_t i = 0; i < s; i++)
		{
			if (values[operator[](i)] == FALSE) return FALSE;
		}
		return TRUE;
	}

}