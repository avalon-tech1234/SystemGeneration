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

		// ����������� ������� ����������� � �����, � �� ����������� � ������� � �������� ����������
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
