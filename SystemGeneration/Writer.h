#pragma once
#include "Matrix.h"
#include "Transformation.h"
#include <fstream>

namespace IO {

	// Данный класс отвечает за вывод в файл

	class Writer 
	{
	private:
		std::string foldername;
		std::ofstream out;

	public:

		Writer(std::string foldername) : foldername(foldername) {}

		void print(const matrixes::MatrixB& matr, std::string filename);

		void print(const transformations::Transformation& trans, std::string filename);

		void print(const matrixes::RowB& row, std::string filename);

		std::string getFoldername()
		{
			return foldername;
		}



	};
}