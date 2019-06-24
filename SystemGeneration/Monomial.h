#pragma once
#include <vector>
#include "BOOL.h"
#include <algorithm>

namespace polynomials {

	// Данный класс определяет терм (моном) - произведение букв. Поскольку дело происходит в GF2, степень может быть только 1 => её и не храним

	class Monomial
	{

	private:

		// Список номеров индексов переменных терма, отсортированный по возрастанию
		// Очевидно, в терме каждая переменная встречается не более, чем 1 раз
		// Например, для монома х1х4х2 vars={1,2,4}
		std::vector<int> vars;
		void simplify();
		int n_max; // наибольший номер присутствующих переменных

	public:

		Monomial(std::vector<int>& in_grades) : n_max(0)
		{
			vars = std::move(in_grades);
			simplify();
		}
		Monomial() : n_max(0) {};
		Monomial(int num) : n_max(0)
		{
			vars.push_back(num);
			simplify();
		}

		int get_n_max() const
		{
			return n_max;
		}

		BOOL substitute(const std::vector<BOOL>& values) const;
		void toString(std::string& out) const;

		inline int size() const
		{
			return (int)vars.size();
		}

		// получение (но не изменение) номера i-ой переменной монома
		inline int operator[](int i) const
		{
			return vars[i];
		}

		void operator*= (const Monomial& m2)
		{
			int sz = m2.size();
			for (int i = 0; i < sz; i++)
				vars.push_back(m2[i]);

			simplify();
		}

		bool Monomial::operator<(const Monomial& m2) const;

		inline bool operator> (const Monomial& m2) const {
			return m2 < *this;
		}
		inline bool operator== (const Monomial& m2) const {
			return !(m2 < *this) && !(m2 > *this);
		}
		inline bool operator!= (const Monomial& m2) const {
			return !(m2 == *this);
		}
		inline bool operator<= (const Monomial& m2) const {
			return !(*this > m2);
		}
		inline bool operator>= (const Monomial& m2) const {
			return !(*this < m2);
		}


	};

#define FREE_MEMBER (Monomial())

}