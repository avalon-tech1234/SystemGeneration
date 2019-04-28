#pragma once
#include <vector>
#include "BOOL.h"

	// ƒанный класс описывает строку матрицы, состо€щую из 0 и 1

namespace matrixes
{

	template <class _T>
	class Row
	{

	private:
		std::vector<_T> elements;
		Row() = delete;

	public:

		Row(size_t length) : elements(length) {};

		void operator^=(const Row<_T>* second)
		{
			size_t sz = size();
			if (sz != second->size())
			{
				throw std::exception("For operation XOR vectors must have same dimension");
			}
			for (size_t i = 0; i < sz; i++)
			{
				_T res = elements[i] ^ (*second)[i];
				elements[i] = res;
			}
		}

		inline _T& element(size_t index)
		{
			return (_T&)elements[index];
		}

		inline _T operator[](size_t index) const
		{
			return (_T)elements[index];
		}

		inline size_t size() const
		{
			return elements.size();
		}

		void Row::toString(
			std::string& output,
			std::string left_border = "{",
			std::string delimiter = ",",
			std::string right_border = "}") const;

		// дл€ векторов небольшого размера
		std::string toString(
			std::string left_border = " {",
			std::string delimiter = ",",
			std::string right_border = "}") const
		{
			std::string s = "";
			toString(s, left_border, delimiter, right_border);
			return s;
		}

	};

}