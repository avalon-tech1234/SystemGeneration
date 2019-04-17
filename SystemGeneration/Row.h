#pragma once
#include <vector>
#include "BOOL.h"
#include <string>


// Данный класс описывает строку матрицы, состоящую из 0 и 1
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

	void toString(
		std::string& output,
		std::string left_border,
		std::string delimiter,
		std::string right_border) const
	{
		size_t res_size = (cend() - cbegin()) *
			(1 + delimiter.length()) + left_border.length() + right_border.length();
		output = left_border;
		output.reserve(res_size);

		for (auto it = begin(); it != end(); it++)
		{
			if (it != begin())
				output += delimiter;

			if (*it) output += '1';
			else output += '0';
		}
		output += right_border;

	}

};
