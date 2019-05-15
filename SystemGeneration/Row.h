#pragma once
#include <vector>
#include "BOOL.h"

namespace matrixes
{

	// ƒанный класс описывает строку матрицы, состо€щую из 0 и 1
	// ƒопускаетс€ создание только Row<bool> и Row<BOOL>

	template <class _T>
	class Row
	{

	private:
		std::vector<_T> elements;
		Row() = delete;

	public:

		Row(size_t length) : elements(length) {};
		Row(std::vector<_T> v) : elements(v) {};

		void toVector(std::vector<BOOL>& res)
		{
			res.clear();
			size_t n = size();
			for (size_t i = 0; i < n; i++)
			{
				res.push_back(get(i));
			}
		}
		
		void operator^=(const Row<_T>& second)
		{
			size_t sz = size();
			if (sz != second.size())
				throw std::exception("For operation XOR vectors must have same dimension");

			for (size_t i = 0; i < sz; i++)
			{
				_T res = elements[i] ^ second.get(i);
				elements[i] = res;
			}
		}

		inline void set(size_t index, _T value)
		{
			elements[index] = value;
		}

		inline _T get(size_t index) const
		{
			return elements[index];
		}

		inline size_t size() const
		{
			return elements.size();
		}

		auto begin() const
		{
			return elements.begin();
		}

		auto end() const
		{
			return elements.end();
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