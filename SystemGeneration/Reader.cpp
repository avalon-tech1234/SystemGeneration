#include "Reader.h"

#include <sstream>
#include "MatrixBuilder.h"

#include "Parser.h"
#include "TransformationBuilder.h"

using namespace IO;
using namespace std;
using namespace matrixes;
using namespace polynomials;
using namespace transformations;

void Reader::read(matrixes::MatrixB& matr, std::string filename)
{
	in.open(foldername + filename);
		string cur;

		// по первой строке (зная, что матрица квадратная) узнаем размерность матрицы
		getline(in, cur);
		util.trim2(cur);
		size_t n = std::count(cur.cbegin(), cur.cend(), ' ') + 1;
		MatrixBuilder builder(n);

		// для каждой строки
		for (int i = 0; i < n; i++)
		{
			if (i != 0) getline(in, cur);
			util.trim2(cur); // оставляем все между фигурными скобками
			std::stringstream ss(cur);
			// разбираем CSV
			while (getline(ss, cur, ',')) {
				util.trim(cur);
				builder << stoi(cur);
			}
		}

		builder.operator>>(matr);

		in.close();
	

}

void Reader::read(transformations::Transformation& trans, std::string filename)
{
	in.open(foldername + filename);
	Parser parser;
	TransformationBuilder builder;

	string cur;
	Polynomial p;
	while (getline(in, cur))
	{
		cur = cur.substr(cur.find('=') + 2);
		parser.read(cur, p);
		builder << p;
	}

	builder >> trans;

	in.close();
}

void Reader::read(matrixes::RowB& row, std::string filename)
{
	in.open(foldername + filename);
	string cur;
	getline(in, cur);
	util.trim2(cur);
	std::stringstream ss(cur);
	vector<BOOL> vect;
	// разбираем CSV
	while (getline(ss, cur, ',')) {
		util.trim(cur);
		vect.push_back(stoi(cur));
	}
	row = vect;

	in.close();
}




