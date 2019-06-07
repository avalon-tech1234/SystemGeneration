#include "Polynomial.h"
#include <algorithm>

using namespace std;
using namespace polynomials;

void Polynomial::toString(string& out) const
{
	out.clear();
	if (terms.empty()) out = "0";
	else {
		auto it = terms.begin(), end = terms.end();
		(it++)->toString(out);
		while (it < end)
		{
			out += " + ";
			(it++)->toString(out);
		}
	}
}


BOOL Polynomial::substitute(const vector<BOOL>& values) const
{
	BOOL result = FALSE;
	size_t s = size();
	for (size_t i = 0; i < s; i++)
	{
		result ^= terms[i].substitute(values);
	}
	return result;
}

void Polynomial::simplify()
{

	if (!terms.empty())
	{
		vector<Monomial> temp = move(terms);
		sort(temp.begin(), temp.end());

		terms.push_back(temp[0]);
		size_t i = 1, sz = temp.size();
		while (i < sz)
		{
			if (!terms.empty() && temp[i] == terms.back())
				terms.pop_back();
			else
				terms.push_back(temp[i]);
			i++;
		}

		temp.clear();
	}

	// обновляем максимальный номер переменной
	size_t sz = terms.size();
	for (size_t i = 0; i < sz; i++)
	{
		if (terms[i].get_n_max() > n_max)
			n_max = terms[i].get_n_max();
	}
}


void Polynomial::operator*=(const Polynomial& p2)
{
	if (this->size() == 0 || p2.size() == 0)
	{
		terms.clear();
		return;
	}

	if (p2.size() == 1 && p2[0] == FREE_MEMBER)
		return;
	if (this->size() == 1 && (*this)[0] == FREE_MEMBER)
	{
		terms.clear();
		size_t sz = p2.size();
		for (size_t i = 0; i < sz; i++)
		{
			terms.push_back(p2[i]);
		}
		return;
	}

	std::vector<Monomial> temp = move(terms);
	size_t sz1 = temp.size(), sz2 = p2.size();
	Monomial cur;

	for (size_t i = 0; i < sz1; i++)
	{
		for (size_t j = 0; j < sz2; j++)
		{
			cur = temp[i];
			cur *= p2[j]; //// !!!!!!?????
			terms.push_back(cur);
		}
	}

	simplify();
}

void Polynomial::operator+=(const Polynomial& p2)
{
	size_t sz = p2.size(), i = 0;
	while (i < sz)
		terms.push_back(p2[i++]);

	simplify();
}


