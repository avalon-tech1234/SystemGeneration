#pragma once
#include "ParserBackground.h"

// ������ ����� �������� �� ���������� ������� ������ � ���������. ������������ � ������ Reader ��� ���������� ������ ������� ���������

namespace IO
{
	class Parser
	{
	public:
		void read(std::string source, polynomials::Polynomial& result);
	};

}