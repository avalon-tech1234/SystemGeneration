#include "Environment.h"
#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

#include "Transformation.h"
#include "Polynomial.h"

using namespace std;
using namespace polynomials;

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;

	auto result = std::back_inserter(elems);
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		*(result++) = item;
	}

	return elems;
}

size_t convert_n(const string& str)
{
	try
	{
		size_t n = stoull(str, nullptr);
		return n;
	}
	catch (const std::out_of_range&)
	{
		throw exception("First parameter is too big number");
	}
	catch (const std::invalid_argument&)
	{
		throw exception("First parameter is not a number");
	}
}

vector<string> parse(int argc, char *argv[])
{
	vector<string> args;
	if (argc == 1)
	{
		string str;
		cout << "Print parameters (or type /h for help): ";
		getline(cin, str);
		args = split(str, ' ');
	}
	else
	{
		args = vector<string>(argv + 1, argv + argc);
	}
	return args;
}

int main(int argc, char *argv[])
{

	string help_text = string("First argument should contain number of equations, or /h for help\n") +
		string("If first argument is number, the second one can be:\n") +
			string("- /s - silent run (only the result) - default \n") +
			string("- /r - sumple run\n") +
			string("- /t - for testing\n") +
			string("Third argument is a name of folder where files will be printed. Default folder is 'results'\n");
	string help = "/h";
	string debug = "/t";
	string run = "/r";
	string silent = "/s";

	try
	{
		vector<string> args = parse(argc, argv);
		argc = (int)args.size();

		if (argc == 0 || args[0] == help)
		{
			cout << help_text;
			system("pause");
			return 0;
		}

		string foldername = "../results/";
		size_t n = convert_n(args[0]);
		if (argc == 3)
			foldername = "../" + args[2] + "/";
		Environment env(n, foldername);

		switch (argc)
		{
		case 1:
			// тихий запуск
			env.silent_run();
			break;
		case 2:
		case 3:
			if (args[1] == silent)
			{
				// тоже тихий запуск
				env.silent_run();
			}
			else if (args[1] == run)
			{
				// запуск в пользовательском режиме
				env.run(true);
			}
			else if (args[1] == debug)
			{
				// запуск в режиме тестирования
				env.test();
			}
			else throw exception("Unknown command!");
			break;
		default:
			throw exception("Unknown command!");
		}

		system("pause");
	}
	catch (std::exception e)
	{
		cout << "Error occupied: " << e.what() << endl << "Program terminated" << endl;
		system("pause");
	}
}
