#include <algorithm>
#include "Monomial.h"


using namespace std;

namespace polynomials
{
	Monomial::Monomial(vector<int> in_grades)
	{
		sort(in_grades.begin(), in_grades.end());
		size_t s = in_grades.size();
		for (size_t i = 0; i < s; i++)
		{
			push_back(in_grades[i]);
		}
	}

	// 0 равны, 1 первый больше, -1 второй больше
	int compare(const Monomial& m1, const Monomial& m2)
	{
		size_t i1 = 0, i2 = 0;
		size_t i1_max = m1.size(), i2_max = m1.size();
		while (i1 < i1_max, i2 < i2_max)
		{
			if (m1[i1] > m2[i2]) return -1;
			if (m1[i1] < m2[i2]) return 1;
		}
		if (i1 < i1_max) return 1;
		if (i2 < i2_max) return -1;
		return 0;
	}

	BOOL Monomial::substitute(const vector<BOOL> values)
	{
		size_t s = size();
		for (size_t i = 0; i < s; i++)
		{
			if (values[operator[](i)]== FALSE) return FALSE;
		}
		return TRUE;
	}

}