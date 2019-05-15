#pragma once
#include "Matrix.h"
#include <random> 

namespace random
{

	template <class _T>
	class RandomMatrixFactory
	{
	private:
		std::mt19937 gen; // генерит случайные числа

	public:
		// принимает строку матрицы, заполненную нулями
		// на выходе строка заполнена случайными числами (0 и 1)
		void getRandomRow(matrixes::Row<_T>& output)
		{
			size_t sz = output.size();
			for (size_t i = 0; i < sz; i++)
				output.set(i, gen() % 2);
		}
		
		void getRandomRow(std::vector<BOOL>& output, size_t n)
		{
			size_t sz = output.size();
			for (size_t i = 0; i < sz; i++)
				output[i]= gen() % 2;
		}
		

		// принимает квадратную матрицу, заполненную нулями
		// на выходе матрица заполнена случайными числами (0 и 1). Гарантируется, что она обратима
		void getRandomMatrix(matrixes::Matrix <_T>& output, size_t dimension);

		RandomMatrixFactory(const std::mt19937& gen) : gen(gen) {}

	};

}