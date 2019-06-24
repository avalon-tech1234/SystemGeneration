#pragma once
#include "stdafx.h"
#include <string>
#include "BOOL.h"
#include <vector>

#include "Reader.h"
#include "Writer.h"
#include "Transformation.h"

class Environment
{
private:

	int n; // ���������� ���������, ����� ���������� �����������
	std::string foldername; // ��� �����, ���� �����

	void generateSystem(bool print_or_not = true);
	void solveSystem(const std::vector<BOOL>& c, std::vector<BOOL>& out, bool print_or_not = true);
	void check(const std::vector<BOOL>& v, const std::string& text);
	void clean(); // ������� ���� ������������� ������
	void normalizeSystem();

public:

	Environment(int n, std::string foldername);

	void run(bool print_or_not = true);
	void test();
	void silent_run()
	{
		run(true);
		clean();
	}

};