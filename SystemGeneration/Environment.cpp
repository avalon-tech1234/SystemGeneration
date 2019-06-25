#include "Environment.h"

#include "RandomEngine.h"
#include "RandomMatrixFactory.h"

#include "file_system.h"
#include "Reader.h"
#include "Writer.h"

#include <iostream>
#include <string>
#include <ctime>

using namespace std;
using namespace matrixes;
using namespace IO;
using namespace random;
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

void Environment::run(bool test_or_not, bool clean_or_not, bool print_or_not)
{
	cout << "Generating system..." << endl;
	generateSystem(print_or_not);
	cout << " ...generating system finished" << endl;

	cout << "Solving system...";
	solveSystem(true);
	cout << " finished" << endl;

	if (test_or_not)
		test();

	cout << "Normalizing system...";
	normalizeSystem();
	cout << " finished" << endl;

	if (clean_or_not)
		clean();

}

void Environment::test()
{
	checkYourself(std::vector<BOOL>(n, FALSE), "zero vector");
	checkYourself(std::vector<BOOL>(n, TRUE), "unit vector");

	std::vector<BOOL> v(n);
	RandomMatrixFactory<BOOL> factory(RandomEngine().getRandomEngine());
	for (int i = 0; i < 10; i++)
	{
		factory.getRandomRow(v);
		string text;
		RowB(v).toString(text, "{", ", ", "}");

		checkYourself(v, text);
	}

}

void Environment::clean()
{
	remove((foldername + "pre_rand/v1.txt").c_str());
	remove((foldername + "pre_rand/v2.txt").c_str());
	remove((foldername + "pre_rand/M1.txt").c_str());
	remove((foldername + "pre_rand/M2.txt").c_str());
	remove((foldername + "inv/invM1.txt").c_str());
	remove((foldername + "inv/invM2.txt").c_str());
	remove((foldername + "pre_gen/S.txt").c_str());
	remove((foldername + "pre_gen/T.txt").c_str());
	remove((foldername + "pre_gen/F.txt").c_str());
	remove((foldername + "pre_gen/FoT.txt").c_str());
	remove((foldername + "inv/invF.txt").c_str());

	std::experimental::filesystem::remove((foldername + "inv"));
	std::experimental::filesystem::remove((foldername + "pre_gen"));
	std::experimental::filesystem::remove((foldername + "pre_rand"));
}
