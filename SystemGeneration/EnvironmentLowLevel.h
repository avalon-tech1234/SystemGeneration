#pragma once
#include <vector>
#include "BOOL.h"

class EnvironmentLowLevel
{

private:
	// Получение результата обратного преобразования
	void getInvert(const std::vector<BOOL>& in, std::vector<BOOL>& out, bool print_or_not = true);

protected:

	int n; // количество уравнений, в ненормализованной системе равно количеству переменнных
	std::string foldername; // имя папки, куда пишем

	void generateSystem(bool print_or_not);
	void solveSystem(bool print_or_not = true)
	{
		std::vector<BOOL> zero(n, FALSE);
		std::vector<BOOL> tmp(1, FALSE);
		getInvert(zero, tmp);
	}
	void normalizeSystem();

	// Проверка для конкретного вектора v - поиск invP(P(v)) и сравнение его с v
	void checkYourself(const std::vector<BOOL>& v, const std::string& text);

};

