#pragma once
#include <vector>
#include <string>
#include "BOOL.h"

namespace polynomials {

	class Monomial
	{

	private:

		// Список номеров индексов переменных монома, отсортированный по возрастанию
		// Например, для монома х1х4х2 vars={1,2,4}
		std::vector<int> vars; 

	public:

		Monomial(std::vector<int> vars);
		Monomial() {};

		BOOL substitute(const std::vector<BOOL> values) const;

		size_t size() const
		{
			return vars.size();
		}

		// получение (но не изменение) номера i-ой переменной монома
		int operator[](size_t i) const
		{
			return vars[i];
		}

		void toString(std::string& out) const
		{
			size_t size_beg = out.size();
			for (auto it = vars.begin(); it != vars.end(); it++)
			{
				out += "x" + std::to_string(*it);
			}
			if (out.size() == size_beg)
				out += "1";
		}




		/*

		В данном блоке определяется логика сравнения двух мономов.
		Пока не удаляю, возможно пригодится

		friend int compare(const Monomial& m1, const Monomial& m2);
		int compareTo(const Monomial& m2) const
		{
			return compare(*this, m2);
		}
		friend bool operator == (const Monomial& m1, const Monomial& m2) { return compare(m1, m2) == 0; }
		friend bool operator != (const Monomial& m1, const Monomial& m2) { return compare(m1, m2) != 0; }
		friend bool operator < (const Monomial& m1, const Monomial& m2) { return compare(m1, m2) == -1; }
		friend bool operator > (const Monomial& m1, const Monomial& m2) { return compare(m1, m2) == 1; }
		friend bool operator <= (const Monomial& m1, const Monomial& m2) { return compare(m1, m2) <= 0; }
		friend bool operator >= (const Monomial& m1, const Monomial& m2) { return compare(m1, m2) >= 0; }
		*/

	};
}