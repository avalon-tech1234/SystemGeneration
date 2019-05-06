#pragma once
#include "Polynomial.h"

// ƒанный класс строит "ƒЌ‘" - полиномы особого вида,
// представл€ющие собой сумму произведений других полиномов
// »спользуетс€ дл€ построени€ композиции отображений

namespace polynomials
{
	class DNFBuilder
	{
	private:
		Polynomial cur; // полином, который мы собираем
		std::vector<Polynomial> factors; // сомножители

	public:

		// добавление произведени€ хранимых сомножителей в качестве слагаемого
		void push()
		{
			if (!factors.empty())
				// если убрать это условие, то, если factors пуст, к полиному прибавитс€ единичка
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