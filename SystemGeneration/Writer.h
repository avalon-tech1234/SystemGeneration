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

		void print(const matrixes::MatrixB& matr, std::string filename);

		void print(const transformations::Transformation& trans, std::string filename);

		std::string getFoldername()
		{
			return foldername;
		}



	};
}