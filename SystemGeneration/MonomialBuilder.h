#pragma once
#include "Monomial.h"

//  ласс, используемый при построчном парсинге файла с полиномами. »спользуетс€ как база дл€ наследовани€ классом PolynomialBuilder

namespace polynomials
{
	class MonomialBuilder
	{
	private:
		std::vector<size_t> gr; // номера переменных в мономе

	protected:

		void create(Monomial& out) {
			out = Monomial(gr);
			gr.clear();
		}


	public:

		void operator<<(size_t grade) {
			gr.push_back(grade);
		}

	};
}
