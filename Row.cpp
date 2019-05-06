#include "Row.h"

using namespace matrixes;
using namespace std;

template <class _T>
void Row<_T>::toString(string& output, string left_border = " {", string delimiter = ",", string right_border = "}") const
{
	output = left_border;
	output.reserve(size() * (1 + delimiter.length()) + left_border.length() + right_border.length());

	if (!elements.empty())
	{
		auto it = elements.begin(), end = elements.end();

		if (*it++ == TRUE) output += '1';
		else output += '0';
		while (it < end)
		{

			output += delimiter;
			if (*it++ == TRUE) output += '1';
			else output += '0';
		}
	}

	output += right_border;
}


template class Row<bool>;
template class Row<BOOL>;
