#pragma once
#include "Polynomial.h"

// ������ ����� ������ "���" - �������� ������� ����,
// �������������� ����� ����� ������������ ������ ���������
// ������������ ��� ���������� ���������� �����������

namespace polynomials
{
	class DNFBuilder
	{
	private:
		Polynomial cur; // �������, ������� �� ��������
		std::vector<Polynomial> factors; // �����������

	public:

		// ���������� ������������ �������� ������������ � �������� ����������
		void push()
		{
			if (!factors.empty())
				// ���� ������ ��� �������, ��, ���� factors ����, � �������� ���������� ��������
			{
				Polynomial product = FREE_MEMBER;
				size_t i = 0, sz = factors.size();
				while (i < sz) 
					product *= factors[i++];
				cur += product;
				factors.clear();
			}
		}

		void operator<<(const Polynomial& pol)
		{
			factors.push_back(pol);
		}

		void operator>>(Polynomial& out)
		{
			push();
			out = cur;
			cur.clear();
		}

	};
}