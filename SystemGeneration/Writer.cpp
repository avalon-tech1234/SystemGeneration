#include "Writer.h"
#include <string>

using namespace std;
using namespace IO;


void Writer::print(const matrixes::MatrixB& matr, std::string filename)
{
	out.open(foldername + filename);

	size_t sz = matr.size();
	string cur;
	for (size_t i = 0; i < sz - 1; i++)
	{
		matr[i]->toString(cur, " {", ", ", "},");
		out << cur << endl;
	}
	matr[sz - 1]->toString(cur, " {", ", ", "}");
	out << cur << endl;

	out.close();
}

void Writer::print(const transformations::Transformation& trans, std::string filename)
{
	out.open(foldername + filename);

	size_t sz = trans.size();
	string cur;
	for (size_t i = 0; i < sz; i++)
	{
		trans[i].toString(cur);
		//out << "y" << i << " = " << cur << endl;
		out << "[" << i << "] " << cur << " = 0;" << endl;
	}

	out.close();
}

void Writer::print(const matrixes::RowB& row, std::string filename)
{
	out.open(foldername + filename);

	string cur;
	row.toString(cur, " {", ", ", "}");
	out << cur << endl;

	out.close();
}