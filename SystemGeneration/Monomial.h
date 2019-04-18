#pragma once
#include <vector>
#include "BOOL.h"

namespace polynomials {

	class Monomial : public std::vector<int>
	{
	private:

	public:

		Monomial(std::vector< int > in_grades);
		Monomial() {};

		BOOL substitute(const std::vector<BOOL> values);

		friend int compare(const Monomial& m1, const Monomial& m2);
		friend bool operator == (const Monomial& m1, const Monomial& m2) { return compare(m1, m2) == 0; }
		friend bool operator != (const Monomial& m1, const Monomial& m2) { return compare(m1, m2) != 0; }
		friend bool operator < (const Monomial& m1, const Monomial& m2) { return compare(m1, m2) == -1; }
		friend bool operator > (const Monomial& m1, const Monomial& m2) { return compare(m1, m2) == 1; }
		friend bool operator <= (const Monomial& m1, const Monomial& m2) { return compare(m1, m2) <= 0; }
		friend bool operator >= (const Monomial& m1, const Monomial& m2) { return compare(m1, m2) >= 0; }

	};
}