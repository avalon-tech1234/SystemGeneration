#pragma once
#include "Monomial.h"

// �����, ������������ ��� ���������� �������� ����� � ����������. ������������ ��� ���� ��� ������������ ������� PolynomialBuilder, � �� ��� ��������������� � Parser

namespace polynomials
{
	class MonomialBuilder
	{
	private:
		std::vector<int> gr; // ������ ���������� � ������
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
