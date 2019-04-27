#pragma once
#include "Monomial.h"

// Класс, используемый при построчном парсинге файла с полиномами. Используется как база для наследования классом PolynomialBuilder, а он уже инкапсулируется в Parser

namespace polynomials
{
	class MonomialBuilder
	{
	private:
		std::vector<size_t> gr; // номера переменных в мономе

	protected:

		virtual const void createMonomial(Monomial& m)
		{
			m = Monomial(gr);
			gr.clear();
		}

	public:
		virtual void addGrade(size_t grade)
		{
			gr.push_back(grade);
		}
		virtual void addGrades(std::vector<size_t> new_grades)
		{
			gr.insert(gr.end(), new_grades.begin(), new_grades.end());
		}
	};

}
