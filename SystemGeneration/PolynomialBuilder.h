#pragma once
#include "MonomialBuilder.h"
#include "Polynomial.h"

namespace polynomials
{
	class PolynomialBuilder : public MonomialBuilder
	{
	private:
		std::vector <Monomial> monomials;

	public:

		void pushMonomial()
		{
			Monomial m;
			createMonomial(m);
			monomials.push_back(m);
		}

		void createPolynomial(Polynomial& out)
		{
			out = Polynomial(monomials);
			monomials.clear();
		}

		~PolynomialBuilder()
		{
			monomials.clear();
			monomials.shrink_to_fit();
		}

	};
}
