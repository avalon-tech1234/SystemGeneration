#pragma once
#include "Matrix.h"
#include "Transformation.h"
#include <fstream>

namespace IO
{
	class Reader
	{
	private:
		std::string foldername;
		std::ifstream in;


	public:
		Reader(std::string foldername): foldername(foldername) {}

		void read(matrixes::MatrixB& matr, std::string filename);

		void read(transformations::Transformation& trans, std::string filename);

	};

}

