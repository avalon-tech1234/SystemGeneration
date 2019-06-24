#pragma once
#include <vector>
#include "BOOL.h"

class EnvironmentLowLevel
{
protected:

	int n; // ���������� ���������, ����� ���������� �����������
	std::string foldername; // ��� �����, ���� �����

	void generateSystem(bool print_or_not = true);
	void solveSystem(const std::vector<BOOL>& c, std::vector<BOOL>& out, bool print_or_not = true);
	void check(const std::vector<BOOL>& v, const std::string& text);
	void clean(); // ������� ���� ������������� ������
	void normalizeSystem();

};

