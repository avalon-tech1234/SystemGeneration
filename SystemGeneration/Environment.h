#pragma once
#include <string>
#include "BOOL.h"
#include <vector>

#include "Reader.h"
#include "Writer.h"
#include "Transformation.h"

class Environment
{
private:

	size_t n; // ���������� ���������, ����� ���������� �����������
	std::string foldername; // ��� �����, ���� �����

	IO::Reader reader;
	IO::Writer writer;

	transformations::Transformation P;

	void generateSystem(bool print_or_not = true);
	void solveSystem(const std::vector<BOOL>& c, std::vector<BOOL>& out, bool print_or_not = true);
	void check(const std::vector<BOOL>& v, const std::string& text);


public:

	Environment(size_t n);

	std::string getFoldername()
	{
		return foldername;
	}

	void run(bool print_or_not = true)
	{
		generateSystem(print_or_not);
		solveSystem(std::vector<BOOL>(n, FALSE), std::vector<BOOL>(n, FALSE), print_or_not);
	}

	void test();

};