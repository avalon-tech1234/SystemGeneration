#pragma once
#include <vector>
#include "BOOL.h"

class EnvironmentLowLevel
{

private:
	// Получение результата обратного преобразования
	void getInvert(const std::vector<BOOL>& in, std::vector<BOOL>& out, bool print_to_file_or_not);

protected:

	int n; // количество уравнений, в ненормализованной системе равно количеству переменнных
	std::string foldername; // имя папки, куда пишем

	void generateSystem(bool print_or_not);
	void solveSystem(bool print_or_not);
	void normalizeSystem();

	// Проверка для конкретного вектора v - поиск invP(P(v)) и сравнение его с v
	void checkYourself(const std::vector<BOOL>& v, const std::string& text);

};

