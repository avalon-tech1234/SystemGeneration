#pragma once
#include "Monomial.h"

namespace polynomials {


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

		Polynomial(const Monomial& m)
		{
			terms.push_back(m);
		}

		Polynomial() {}

		inline Polynomial& operator+(const Polynomial& p2)
		{
			operator+=(p2);
			return *this;
		}

		inline Polynomial& operator+(const Monomial& p2)
		{
			operator+=(Polynomial(p2));
			return *this;
		}

		void operator+=(const Polynomial& p2)
		{
			size_t sz = p2.size(), i = 0;
			while (i < sz)
				terms.push_back(p2[i++]);

			simplify();
		}

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

