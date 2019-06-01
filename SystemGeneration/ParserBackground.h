#pragma once
#include "PolynomialBuilder.h"
#include <cctype>
#include <string>

// в данном файле описан класс ParserBackground и отдельные функции, используемые в классе Parser

namespace IO
{
	enum class AddMode
	{
		push_empty,
		puth_others
	};

	enum class SymbolTypes
	{
		unknown,
		sign,
		cap,
		digit,
		letter,
		empty,
		trail,
		open_comment,
		close_comment,

		// доп. значения
		plus
	};

	inline SymbolTypes what_type(char symb)
	{
		if (symb == '+')
			return SymbolTypes::sign;
		if (symb == '\0' || symb == '=' || symb == ';')
			return SymbolTypes::trail;
		if (symb == '^')
			return SymbolTypes::cap;
		if (isdigit(symb) != 0)
			return SymbolTypes::digit;
		if (isalpha(symb) != 0)
			return SymbolTypes::letter;
		if (isblank(symb) != 0)
			return SymbolTypes::empty;
		if (symb == '[')
			return SymbolTypes::open_comment;
		if (symb == ']')
			return SymbolTypes::close_comment;
		return SymbolTypes::unknown;
	}

	inline SymbolTypes what_coeff(char symb)
	{
		if (symb == '+') return SymbolTypes::plus;
		return SymbolTypes::digit;
	}


	class ParserBackground : public polynomials::PolynomialBuilder
	{
	private:
		int state;
		std::string str; // накапливаемая строка
		char symb; // текущий символ
		std::string source;
		int state_saved; // хранит значение state при чтении комментария
		int symb_place;
		int base = 0;
		int first_free_num = 0;


	public:

		ParserBackground(std::string source) : source(source) {}

		inline void to(int st)
		{
			str = symb;
			state = st;
		}

		inline void refresh()
		{
			char c = source[symb_place++];
			symb = c;
		}

		inline SymbolTypes cur_type()
		{
			return what_type(symb);
		}
		inline SymbolTypes cur_coeff()
		{
			return what_coeff(str[0]);
		}

		inline void pause()
		{
			state_saved = state;
			state = 6;
		}
		inline void unpause()
		{
			state = state_saved;
		}

		/*
		Отражает текущее состояние Машины. Принимает значения:
		0 - начальное состояние
		1 - выполняется парсинг коэффициента
		2 - выполняется парсинг названия переменной
		3 - выполняется начальный парсинг степени
		4 - конец парсинга
		5 - выполняется парсинг степени
		6 - парсинг комментария (между [ и ])
		*/
		inline int show_state()
		{
			return state;
		}

		inline void read()
		{
			str += symb;
		}

		inline bool stop()
		{
			return state == 4;
		}

		inline void setCoeff()
		{
			// MonomialBuilder::setCoeff(1); - коэфф и так не могут быть отличны от 1
			to(2);
		}

		void addMonomial(AddMode mode)
		{
			if (mode == AddMode::puth_others)
				polynomials::PolynomialBuilder::push();
			if (mode == AddMode::push_empty)
				polynomials::PolynomialBuilder::push();
		}
		void addGrade(AddMode mode)
		{
			polynomials::PolynomialBuilder::operator<<(get_var_num());
		}
		int get_var_num()
		{
			return std::stoi(str.substr(1));
		}

		void setBase()
		{
			base = get_var_num();
		}
	};


}