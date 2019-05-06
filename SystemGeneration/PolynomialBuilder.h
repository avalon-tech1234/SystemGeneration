#pragma once
#include "MonomialBuilder.h"
#include "Polynomial.h"

namespace polynomials
{
	class PolynomialBuilder : public MonomialBuilder
	{
	protected:
		std::vector <Monomial> monomials;

	public:

		// Хранившиеся индексы добавляются в моном, а он добавляется в полином в качестве слагаемого
		void push()
		{
			Monomial m;
			create(m);
			monomials.push_back(m);
		}

		void operator>>(Polynomial& out)
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
