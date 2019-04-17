#include "Writer.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>

using namespace std;

string Writer::createFolder()
{
	string foldername = "../results/";

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
	return foldername;
}

void Writer::printMatrix(const Matrix<BOOL>& matr, std::string filename)
{

	ofstream out(filename);
	size_t sz = matr.size();
	string cur;
	for (size_t i = 0; i < sz - 1; i++)
	{
		matr.const_row(i)->toString(cur, " {", ", ", "},");
		out << cur << endl;
	}
	matr.const_row(sz - 1)->toString(cur, " {", ", ", "}");
	out << cur << endl;
	out.close();
}