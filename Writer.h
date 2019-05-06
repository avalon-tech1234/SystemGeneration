#pragma once
#include "Matrix.h"
#include "Transformation.h"
#include <fstream>

namespace IO {

	// ������ ����� �������� �� ����� � ����

	class Writer 
	{
	private:
		std::string foldername;
		std::ofstream out;

	public:

		Writer();

		void printMatrix(const matrixes::MatrixB& matr, std::string filename);

		void printTransformation(const transformations::Transformation& trans, std::string filename);


	};
}