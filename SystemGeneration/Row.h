#pragma once
#include <vector>
#include "BOOL.h"
#include <string>


// ƒанный класс описывает строку матрицы, состо€щую из 0 и 1
template <class _T>
class Row : private std::vector<_T>
{

private:
	Row() = delete;

public:

	Row(size_t length) : std::vector<_T>(length) {};

	void xor(Row<_T>* second)
	{
		size_t s = size();
		for (size_t i = 0; i < s; i++)
		{
			operator[](i) = operator[](i) ^ second->element(i);
		}
	}

	inline _T& element(size_t index)
	{
		return (_T&)operator[](index);
	}

	inline size_t size()
	{
		return std::vector<_T>::size();
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
		std::string right_border = "}" ) const
	{
		std::string s = "";
		toString(s, left_border, delimiter, right_border);
		return s;
	}

};
