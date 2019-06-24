#include "Environment.h"

#include "RandomMatrixFactory.h"
#include "RandomPolynomialFactory.h"
#include "RandomEngine.h"
#include "AffineTransformation.h"
#include "TransformationBuilder.h"
#include "speedtest.h"

#include "file_system.h"
#include "Reader.h"
#include "Writer.h"

#include <iostream>
#include <string>
#include <ctime>

using namespace std;
using namespace matrixes;
using namespace transformations;
using namespace IO;
using namespace random;
using namespace polynomials;
using namespace filesystem;

Environment::Environment(int _n, string _foldername)
{
	n = _n;
	foldername = _foldername;

	if (n == 0)
		throw std::exception("Attempt to create equation system with 0 equations. Forbidden");

	create_folder(foldername);

	time_t t = time(0);
	struct tm now;
	localtime_s(&now, &t);

	foldername +=
		to_string(now.tm_year + 1900) + "." +
		to_string(now.tm_mon + 1) + "."
		+ to_string(now.tm_mday) + "_"
		+ (now.tm_hour < 10 ? "0" + to_string(now.tm_hour) : to_string(now.tm_hour)) + "."
		+ (now.tm_min < 10 ? "0" + to_string(now.tm_min) : to_string(now.tm_min)) + "."
		+ (now.tm_sec < 10 ? "0" + to_string(now.tm_sec) : to_string(now.tm_sec)) + "/";

	create_folder(foldername);
	create_folder(foldername + "inv/");
	create_folder(foldername + "pre_rand/");
	create_folder(foldername + "pre_gen/");

}

void Environment::run(bool print_or_not)
{
	cout << "Generating system..." << endl;
	generateSystem(print_or_not);
	cout << " ...generating system finished" << endl;

	cout << "Solving system...";
	std::vector<BOOL> tmp(1, FALSE);
	solveSystem(std::vector<BOOL>(n, FALSE), tmp);
	cout << " finished" << endl;

	cout << "Normalizing system...";
	normalizeSystem();
	cout << " finished" << endl;

}

void Environment::test()
{
	cout << "Generating system..." << endl;
	generateSystem(true);
	cout << " ...generating system finished" << endl;


	cout << "Solving system...";
	std::vector<BOOL> tmp(1, FALSE);
	solveSystem(std::vector<BOOL>(n, FALSE), tmp);
	cout << " finished" << endl;

	check(std::vector<BOOL>(n, FALSE), "zero vector");
	check(std::vector<BOOL>(n, TRUE), "unit vector");

	std::vector<BOOL> v(n);
	RandomMatrixFactory<BOOL> factory(RandomEngine().getRandomEngine());
	for (int i = 0; i < 10; i++)
	{
		factory.getRandomRow(v);
		string text;
		RowB(v).toString(text, "{", ", ", "}");

		check(v, text);
	}

}