#pragma once
#include "Monomial.h"


namespace polynomials {


	class Polynomial : public std::vector <Monomial>
	{
	private:
		Monomial leadingMonomial;

		void refreshLeadingMonomial() 
		{ leadingMonomial = getLeadingMonomial(); };

	public:
		Polynomial(std::vector <Monomial> in_monomials): std::vector <Monomial>(in_monomials) {};

		Polynomial() {}

		Monomial getLeadingMonomial();

		BOOL substitute(const vector<BOOL> values)
		{
			BOOL result = FALSE;
			size_t s = size();
			for (size_t i = 0; i < s; i++)
			{
				result ^= operator[](i).substitute(values);
			}
			return result;
		}
	};
}

