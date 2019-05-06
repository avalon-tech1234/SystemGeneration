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
