#pragma once
#include "Row.h"

namespace matrixes
{

	// ƒанный класс описывает квадратную матрицу, состо€щую из 0 и 1
	// ƒопускаетс€ создание только Matrix<bool> и Matrix<BOOL>
	template <class _T>
	class Matrix
	{
	private:
		std::vector<Row <_T> *> data;

		// эта функци€ используетс€ при построении обратной матрицы, извне матрица всегда квадратна€ 
		BOOL init_zeros(int dimension, int dimension2);

	public:

		Matrix() : data() { }

		Matrix(Matrix && mat) : data(std::move(mat.data)) {}

		//Matrix(Matrix& mat) : data(std::move(mat.data)) {}

		Matrix& operator=(Matrix&& other)
		{
			if (this != &other)
			{
				data.clear();
				data = std::move(other.data);
			}
			return *this;
		}

		bool operator==(Matrix& other)
		{
			int n = size();
			if (n != other.size()) return false;

			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					if (get(i)->get(j) != other.get(i)->get(j)) return false;

			return true;
		}

		// устанавливает размеры матрицы как dimension*dimension и заполн€ет еЄ нул€ми
		BOOL init_zeros(int dimension)
		{
			return init_zeros(dimension, dimension);
		}

		/*
		»нициализирует матрицу как матрицу, обратную к матрице, переданной в качестве параметра
		»спользуетс€ метод √аусса-∆ордана
		ќбратимость матрицы не провер€етс€ (если не обратима, на выходе кака€-то матрица)
		*/
		void initInverse(const Matrix<_T>& matrix);

		~Matrix()
		{
			for (size_t i = 0; i < data.size(); i++)
				delete data[i];

			data.clear();
		}

		void multiply(const Row<_T>& r, Row<_T>& result) const
		{
			int n = size();
			if (n != r.size()) return;

			result = Row<_T>(n);
			BOOL b;
			for (int i = 0; i < n; i++)
			{
				b = 0;
				for (int j = 0; j < n; j++)
					b ^= data[i]->get(j) * r.get(j);
				result.set(i, b);
			}
		}

		inline Row <_T>* get(int n)
		{
			return data[n];
		}

		inline Row <_T>* const operator[](int n) const
		{
			return data[n];
		}

		inline void swap(int index1, int index2);

		// ¬озвращает количество строк (оно же количество столбцов) в матрице
		inline int size() const
		{
			return (int)data.size();
		}

		// используетс€ в тестовых цел€х
		void print() const;

	};

	typedef Matrix<BOOL> MatrixB;
	typedef Row<BOOL> RowB;


}