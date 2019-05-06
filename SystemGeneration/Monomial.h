#pragma once
#include <vector>
#include "BOOL.h"

namespace polynomials {

	class Monomial
	{

	private:

		// Список номеров индексов переменных терма, отсортированный по возрастанию
		// Очевидно, в терме каждая переменная встречается не более, чем 1 раз
		// Например, для монома х1х4х2 vars={1,2,4}
		std::vector<size_t> vars;
		void simplify();


	public:

		Monomial(std::vector<size_t>& in_grades)
		{
			vars = std::move(in_grades);
			simplify();
		}
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

		// получение (но не изменение) номера i-ой переменной монома
		inline size_t operator[](size_t i) const
		{
			return vars[i];
		}
		
		void operator*= (const Monomial& m2)
		{
			size_t sz = m2.size(), i = 0;
			while (i < sz)
				vars.push_back(m2[i++]);

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