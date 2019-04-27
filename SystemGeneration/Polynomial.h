#pragma once
#include "Monomial.h"

namespace polynomials {


	class Polynomial : private std::vector <Monomial>
	{

	public:
		Polynomial(const std::vector <Monomial>& in_monomials)
			: std::vector <Monomial>(in_monomials)
		{
			simplify();
		}

		Polynomial(const Monomial& m)
		{
			push_back(m);
		}

		Polynomial() {}

		Polynomial& operator+(const Polynomial& p2)
		{
			insert(end(), p2.begin(), p2.end());
			simplify();
			return *this;
		}

		void operator+=(const Polynomial& p2)
		{
			insert(end(), p2.begin(), p2.end());
			simplify();
		}

		void simplify();

		BOOL substitute(const vector<BOOL> values) const;

		void toString(std::string& out) const;

	};
}

