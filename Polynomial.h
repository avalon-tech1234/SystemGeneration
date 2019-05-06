#pragma once
#include "Monomial.h"

namespace polynomials {

	/*

	������ ����� ���������� �������. ������� �������������� ��� ������ �������.
	�������� � ������ ������ (� ����� ������ �����) ������������� ��������� �������:
	- ������ � ������� �������� (����������� ����) ����������� ������, ��� � ������� �����������
	- ������ ������ ������� ����������� �����������������: ��, ��, ..., ��, ��, ��, ..., ��
	
	*/

	class Polynomial
	{
	private:

		std::vector <Monomial> terms;
		void simplify();


	public:
		Polynomial(const std::vector <Monomial>& in_monomials)
		{
			terms = std::move(in_monomials);
			simplify();
		}

		// ��� ������������
		Polynomial(const std::vector <std::vector <size_t>> input)
		{
			for (size_t i = 0; i < input.size(); i++)
			{
				std::vector <size_t> cur = input[i];
				terms.push_back(Monomial(cur));
			}
			simplify();
		}

		Polynomial(const Monomial& m)
		{
			terms.push_back(m);
		}

		Polynomial() {}

		inline void clear()
		{
			terms.clear();
			terms.shrink_to_fit();
		}

		void operator+=(const Polynomial& p2);
		void operator*=(const Polynomial& p2);

		inline const Monomial& operator[](size_t i) const
		{
			return terms[i];
		}

		inline size_t size() const
		{
			return terms.size();
		}

		BOOL substitute(const std::vector<BOOL> values) const;

		void toString(std::string& out) const;

	};
}

