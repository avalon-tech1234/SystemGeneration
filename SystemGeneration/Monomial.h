#pragma once
#include <vector>
#include "BOOL.h"

namespace polynomials {

	class Monomial
	{

	private:

		// ������ ������� �������� ���������� ������, ��������������� �� �����������
		// ��������, ��� ������ �1�4�2 vars={1,2,4}
		std::vector<size_t> vars;

	public:

		Monomial(std::vector<size_t>& in_grades);
		Monomial() {};
		Monomial(size_t num)
		{
			vars.push_back(num);
		}

		BOOL substitute(const std::vector<BOOL> values) const;
		void toString(std::string& out) const;

		inline size_t size() const
		{
			return vars.size();
		}

		// ��������� (�� �� ���������) ������ i-�� ���������� ������
		inline size_t operator[](size_t i) const
		{
			return vars[i];
		}

		bool operator<(const Monomial& m2) const;

		bool operator> (const Monomial& m2) const {
			return m2 < *this;
		}
		bool operator== (const Monomial& m2) const {
			return !(m2 < *this) && !(m2 > *this);
		}
		bool operator!= (const Monomial& m2) const {
			return !(m2 == *this);
		}
		bool operator<= (const Monomial& m2) const {
			return !(*this > m2);
		}
		bool operator>= (const Monomial& m2) const {
			return !(*this < m2);
		}


	};
}