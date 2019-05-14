#pragma once
#include "Matrix.h"
#include "Transformation.h"
#include <fstream>
#include "Utility.h"


namespace IO
{
	class Reader
	{
	private:
		std::string foldername;
		std::ifstream in;
		Utility util;


	public:
		Reader(std::string foldername): foldername(foldername) {}

		void read(matrixes::MatrixB& matr, std::string filename);

		void read(transformations::Transformation& trans, std::string filename);

		void read(matrixes::RowB& row, std::string filename);

	};

}

