#pragma once
#include "Monomial.h"

// Класс, используемый при построчном парсинге файла с полиномами. Используется как база для наследования классом PolynomialBuilder, а он уже инкапсулируется в Parser

namespace polynomials
{
	class MonomialBuilder
	{
	private:
		std::vector<int> gr; // номера переменных в мономе
		Monomial mon;
	protected:

		virtual const void createMonomial(Monomial& m)
		{
			mon = Monomial(gr);
			m = mon;
			std::vector<int>().swap(gr);
		}

	public:
		virtual void addGrade(int grade)
		{
			gr.push_back(grade);
		}
	};

}
