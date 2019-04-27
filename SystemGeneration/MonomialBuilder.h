#pragma once
#include "Monomial.h"

// �����, ������������ ��� ���������� �������� ����� � ����������. ������������ ��� ���� ��� ������������ ������� PolynomialBuilder

namespace polynomials
{
	class MonomialBuilder
	{
	private:
		std::vector<size_t> gr; // ������ ���������� � ������

	protected:

		void createMonomial(Monomial& out) {
			out = Monomial(gr);
			gr.clear();
		}


	public:

		void addGrade(size_t grade) {
			gr.push_back(grade);
		}

		void addGrades(const std::vector<size_t>& new_grades) {
			gr.insert(gr.end(), new_grades.begin(), new_grades.end());
		}


	};
}
