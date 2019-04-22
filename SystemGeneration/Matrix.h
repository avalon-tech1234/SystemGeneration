#pragma once
#include "Row.h"

namespace matrixes
{


	// Данный класс описывает квадратную матрицу, состоящую из 0 и 1
	// Допускается создание только Matrix<bool> и Matrix<BOOL>
	template <class _T>
	class Matrix
	{
		typedef _T t_vattype;
	private:
		std::vector<Row <_T> *> data;

	public:

		Matrix() : data() { }

		Matrix(Matrix && mat) : data(std::move(mat.data)) {}

		BOOL Init(size_t dimension);


		~Matrix()
		{
			for (size_t i = 0; i < data.size(); i++)
			{
				delete data[i];
			}

			data.clear();
		}


		inline Row <t_vattype>* row(size_t n)
		{
			return data[n];
		}

		inline Row <t_vattype>* const const_row(size_t n) const
		{
			return data[n];
		}

		inline void swap(size_t index1, size_t index2)
		{
			Row<t_vattype> save = *data[index1];
			delete data[index1];					// ????????????????????????????????
			data[index1] = data[index2];
			data[index2] = new Row<t_vattype>(std::move(save));
		}

		// Возвращает количество строк (оно же количество столбцов) в матрице
		inline size_t size() const
		{
			return data.size();
		}



	};

	typedef Matrix<BOOL> MatrixB;
	typedef Row<BOOL> RowB;


}