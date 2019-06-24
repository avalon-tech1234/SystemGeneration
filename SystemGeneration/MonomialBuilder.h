#pragma once
#include "Monomial.h"

// ������������ ��� ���� ��� ������������ ������� PolynomialBuilder

namespace polynomials
{
	class MonomialBuilder
	{
	private:
		std::vector<int> gr; // ������ ���������� � ������

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
