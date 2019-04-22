#pragma once
#include "Matrix.h"
#include "AffineTransformation.h"
#include <fstream>


class Writer
{
private:
	std::string foldername;
	std::ofstream out;

public:

	Writer();

	void printMatrix(const matrixes::MatrixB& matr, std::string filename);

	void printAffineTransformation(const transformations::AffineTransformation& trans, std::string filename);


};