#pragma once
#include <vector>
#include "BOOL.h"

class EnvironmentLowLevel
{

private:
	// ��������� ���������� ��������� ��������������
	void getInvert(const std::vector<BOOL>& in, std::vector<BOOL>& out, bool print_or_not = true);

protected:

	int n; // ���������� ���������, � ����������������� ������� ����� ���������� �����������
	std::string foldername; // ��� �����, ���� �����

	void generateSystem(bool print_or_not);
	void solveSystem(bool print_or_not = true)
	{
		std::vector<BOOL> zero(n, FALSE);
		std::vector<BOOL> tmp(1, FALSE);
		getInvert(zero, tmp);
	}
	void normalizeSystem();

	// �������� ��� ����������� ������� v - ����� invP(P(v)) � ��������� ��� � v
	void checkYourself(const std::vector<BOOL>& v, const std::string& text);

};

