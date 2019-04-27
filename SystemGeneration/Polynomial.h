#pragma once
#include "Monomial.h"
#include <algorithm>

namespace polynomials {


	class Polynomial : private std::vector <Monomial>
	{
	private:
		//Monomial leadingMonomial;

		//void refreshLeadingMonomial() { leadingMonomial = getLeadingMonomial(); };

	public:
		Polynomial(std::vector <Monomial> in_monomials)
			: std::vector <Monomial>(in_monomials)
		{
			simplify();
		}

		Polynomial(Monomial m)
		{
			push_back(m);
		}

		Polynomial() {}

		//Monomial getLeadingMonomial();

		BOOL substitute(const vector<BOOL> values) const
		{
			BOOL result = FALSE;
			size_t s = size();
			for (size_t i = 0; i < s; i++)
			{
				result ^= operator[](i).substitute(values);
			}
			return result;
		}

		void toString(std::string& out) const
		{
			out = "";
			std::string cur;
			for (auto it = begin(); it != end(); it++)
			{
				if (it == begin())
					out += " ";
				else
					out += " + ";
				it->toString(out);
			}
			if (out == "") out = " 0";
		}

		Polynomial& operator+(Polynomial& p2)
		{
			insert(end(), p2.begin(), p2.end());
			simplify();
			return *this;
		}

		void operator+=(Polynomial& p2)
		{
			insert(end(), p2.begin(), p2.end());
			simplify();
		}

		void simplify()
		{
			std::sort(begin(), end(), compare);

			size_t i = 0;
			while (i + 1 < size())
			{
				if (operator[](i) == operator[](i + 1))
				{
					erase(begin() + i);
					erase(begin() + i);
				}
				i++;
			}
		}

	};
}

