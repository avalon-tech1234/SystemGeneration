#include "Writer.h"
#include <ctime>
#include <string>

using namespace std;
using namespace IO;

Writer::Writer()
{
	foldername = "../results/";

	time_t t = time(0);
	struct tm now;
	localtime_s(&now, &t);

	foldername +=
		to_string(now.tm_year + 1900) + "." +
		to_string(now.tm_mon + 1) + "."
		+ to_string(now.tm_mday) + "_"
		+ (now.tm_hour < 10 ? "0" + to_string(now.tm_hour) : to_string(now.tm_hour)) + "."
		+ (now.tm_min < 10 ? "0" + to_string(now.tm_min) : to_string(now.tm_min)) + "."
		+ (now.tm_sec < 10 ? "0" + to_string(now.tm_sec) : to_string(now.tm_sec));

	wstring ws(foldername.begin(), foldername.end());
	_wmkdir(&ws[0]);

	foldername += "/";
}

void Writer::printMatrix(const matrixes::MatrixB& matr, std::string filename)
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

void Writer::printTransformation(const transformations::Transformation& trans, std::string filename)
{
	out.open(foldername + filename);

	size_t sz = trans.size();
	string cur;
	for (size_t i = 0; i < sz; i++)
	{
		trans[i].toString(cur);
		out << "y" << i << " = " << cur << endl;
	}

	out.close();
}