#pragma once
#include "MonomialBuilder.h"
#include "Polynomial.h"

namespace polynomials
{
	class PolynomialBilder : public MonomialBuilder
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

		const Polynomial& createPolynomial()
		{
			pol = Polynomial(monomials);
			std::vector<Monomial>().swap(monomials);
			return pol;
		}
	};
}
