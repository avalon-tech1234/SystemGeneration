#pragma once
#include "MonomialBuilder.h"
#include "Polynomial.h"

namespace polynomials
{
	class PolynomialBuilder : public MonomialBuilder
	{
	private:
		std::vector <Monomial> monomials;
		Polynomial pol;

	public:

		void pushMonomial()
		{
			Monomial m;
			MonomialBuilder::createMonomial(m);
			monomials.push_back(m);
		}

		Polynomial& createPolynomial()
		{
			pol = Polynomial(monomials);
			monomials.clear();
			return pol;
		}

		~PolynomialBuilder()
		{
			monomials.clear();
			monomials.shrink_to_fit();
		}

	};
}
