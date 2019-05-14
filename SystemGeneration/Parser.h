#pragma once
#include "ParserBackground.h"

// данный класс отвечает за построчный парсинг строки в уравнение. Используется в классе Reader при построчном чтении системы уравнений

namespace IO
{
	class Parser
	{
	public:
		void read(std::string source, polynomials::Polynomial& result);
	};

}