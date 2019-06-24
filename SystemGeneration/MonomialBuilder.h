#pragma once
#include "Monomial.h"

// Используется как база для наследования классом PolynomialBuilder

namespace polynomials
{
	class MonomialBuilder
	{
	private:
		std::vector<int> gr; // номера переменных в мономе

	protected:

		void create(Monomial& out) {
			if (gr.size() > 0)
			{
				out = Monomial(gr);
				gr.clear();
			}
			else
			{
				out = FREE_MEMBER;
			}
		}


	public:

		void operator<<(int grade) {
			gr.push_back(grade);
		}

	};
}
