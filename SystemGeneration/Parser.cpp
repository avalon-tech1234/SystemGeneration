#include "Parser.h"


using namespace IO;

void Parser::read(std::string source, polynomials::Polynomial& result)
{
	ParserBackground engine(source); // source - текущая строка

	do
	{
		engine.refresh();
		SymbolTypes type = engine.cur_type();
		SymbolTypes coeff = engine.cur_coeff();

		if (type == SymbolTypes::empty) continue;
		if (type == SymbolTypes::open_comment)
		{
			engine.pause();
			continue;
		}

		switch (engine.show_state())
		{
		case 0:
			switch (type) {
			case SymbolTypes::sign:
			case SymbolTypes::digit:
				engine.to(1); break;
			case SymbolTypes::letter:
				engine.setCoeff();
				engine.to(2);
				break;
			case SymbolTypes::trail:
				engine.to(4); break;
			default:
				throw std::exception("некорректное начало полинома");
			}
			break;
		case 1:
			switch (type) {
			case SymbolTypes::digit:
				engine.read(); break;
			case SymbolTypes::letter:
				switch (coeff)
				{
				case SymbolTypes::plus:
					engine.setCoeff();
					break;
				case SymbolTypes::digit:
					engine.setCoeff();
					break;
				}
				break;
			case SymbolTypes::trail:
				engine.addMonomial(AddMode::puth_others);
				engine.to(4);
				break;
			default: throw std::exception("некорректно введен коэффициент");
			}
			break;
		case 2:
			switch (type)
			{
			case SymbolTypes::digit:
				engine.read(); break;
			case SymbolTypes::sign:
				engine.addGrade(AddMode::push_empty);
				engine.addMonomial(AddMode::push_empty);
				engine.to(1); break;
			case SymbolTypes::letter:
				engine.addGrade(AddMode::push_empty);
				engine.to(2); break;
			case SymbolTypes::trail:
				engine.addGrade(AddMode::push_empty);
				engine.addMonomial(AddMode::push_empty);
				engine.to(4); break;
			case SymbolTypes::cap:
				engine.setBase();
				engine.to(3); break;
			default: throw std::exception("некорректно введен коэффициент");
			}
			break;
		case 3:
			switch (type)
			{
			case SymbolTypes::digit:
				engine.to(5); break;
			default: throw std::exception("некорректно введен коэффициент");
			}
			break;
		case 5:

			switch (type)
			{
			case SymbolTypes::digit:
				engine.read(); break;
			case SymbolTypes::sign:
				engine.addGrade(AddMode::puth_others);
				engine.addMonomial(AddMode::push_empty);
				engine.to(1); break;
			case SymbolTypes::letter:
				engine.addGrade(AddMode::puth_others);
				engine.to(2); break;
			case SymbolTypes::trail:
				engine.addGrade(AddMode::puth_others);
				engine.addMonomial(AddMode::push_empty);
				engine.to(4); break;
			default: throw std::exception("некорректно введен коэффициент");
			}
			break;

		case 6:
			switch (type) {
			case SymbolTypes::close_comment:
				engine.unpause(); break;

			}
			break;
		}

	} while (!engine.stop());


	engine >> result;

}

