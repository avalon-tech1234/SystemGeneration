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
		int n_max;

	public:
		Polynomial(const std::vector <Monomial>& in_monomials) : n_max(0)
		{
			terms = std::move(in_monomials);
			simplify();
		}

		// ��� ������������
		Polynomial(const std::vector <std::vector <int>> input) : n_max(0)
		{
			for (size_t i = 0; i < input.size(); i++)
			{
				std::vector <int> cur = input[i];
				terms.push_back(Monomial(cur));
			}
			simplify();
		}

		Polynomial(const Monomial& m) : n_max(0)
		{
			terms.push_back(m);
		}

		Polynomial() : n_max(0) {}

		inline int get_n_max() const
		{
			return n_max;
		}

		inline void clear()
		{
			terms.clear();
			terms.shrink_to_fit();
		}

		void operator+=(const Polynomial& p2);
		void operator*=(const Polynomial& p2);

		inline const Monomial& operator[](int i) const
		{
			return terms[i];
		}

		inline int size() const
		{
			return (int)terms.size();
		}

		inline auto begin() const
		{
			return terms.begin();
		}

		BOOL substitute(const std::vector<BOOL>& values) const;

		void toString(std::string& out) const;

		// ���� � �������� ��������� ������� Lr �, ���� �������, �������� �� ����� ���������� x_z
		void replace(Polynomial Lr, int z)
		{
			int sz = Lr.size();

			for (int i = 0; i < sz; i++)
			{
				if (std::find(begin(), begin() + size(), Lr[i]) == begin() + size())
					return;
			}
			
			// ����������, ��� Lr ����������� ����, ���������� ������
			for (int i = 0; i < sz; i++)
			{
				*this += (Lr[i]);
			}
			*this += Monomial(z);
			simplify();
		}

		/* ���������, �������� �� ��������� ���������. ��������� ����������:
		 * x + yz = 0
		 * x + (y + z) = 0
		 * x + y + � = 0 - ����� ��������� ������ � ����� ��������� ���������, c - ��������� (0 ��� 1)
		 */
		bool is_standard() const
		{
			switch (size())
			{
			case 2:
				if (terms[1].size() == 1 && terms[0].size() == 2)
					return true;
				return false;
			case 3:
				if (terms[0].size() == 1 && terms[1].size() == 1 && terms[2].size() == 1)
					return true;
				return false;
			default:
				return false;
			}
		}

	};
}

