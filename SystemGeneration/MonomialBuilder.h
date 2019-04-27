#pragma once
#include "Monomial.h"

// �����, ������������ ��� ���������� �������� ����� � ����������. ������������ ��� ���� ��� ������������ ������� PolynomialBuilder, � �� ��� ��������������� � Parser

namespace polynomials
{
	class MonomialBuilder
	{
	private:
		std::vector<size_t> gr; // ������ ���������� � ������

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
