#pragma once
#include "Matrix.h"


class Writer
{
public:
	static void printMatrix(const MatrixB& matr, std::string filename);

	static std::string createFolder();
};