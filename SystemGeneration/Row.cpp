#include "Row.h"

using namespace matrixes;

template <class _T>
void Row<_T>::toString(
	std::string& output,
	std::string left_border = " {",
	std::string delimiter = ",",
	std::string right_border = "}")
	const
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


template class Row<bool>;
template class Row<BOOL>;
