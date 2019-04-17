#pragma once
#include "Matrix.h"


class Writer
{
public:
	static void printMatrix(const Matrix<BOOL>& matr, std::string filename);

	static std::string createFolder();
};