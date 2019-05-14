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
		BOOL init_zeros(size_t dimension, size_t dimension2);

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
			size_t n = size();
			if (n != other.size()) return false;

			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					if (get(i)->get(j) != other.get(i)->get(j)) return false;

			return true;
		}

		// устанавливает размеры матрицы как dimension*dimension и заполн€ет еЄ нул€ми
		BOOL init_zeros(size_t dimension)
		{
			return init_zeros(dimension, dimension);
		}

		// инициализирует матрицу как матрицу, обратную к матрице, переданной в качестве параметра
		// используетс€ метод √аусса-∆ордана
		// обратимость матрицы должна провер€тьс€ клиентом
		void initInverse(const Matrix<_T>& matrix);

		~Matrix()
		{
			for (size_t i = 0; i < data.size(); i++)
				delete data[i];

			data.clear();
		}

		void multiply(const Row<_T>& r, Row<_T>& result)
		{
			size_t n = size();
			if (n != r.size()) return;

			result = Row<_T>(n);
			BOOL b;
			for (size_t i = 0; i < n; i++)
			{
				b = 0;
				for (size_t j = 0; j < n; j++)
					b += get(i)->get(j) * r.get(j);
				result.set(i, b);
			}
		}

		inline Row <_T>* get(size_t n)
		{
			return data[n];
		}

		inline Row <_T>* const operator[](size_t n) const
		{
			return data[n];
		}

		inline void swap(size_t index1, size_t index2);

		// ¬озвращает количество строк (оно же количество столбцов) в матрице
		inline size_t size() const
		{
			return data.size();
		}

		// используетс€ в тестовых цел€х
		void print() const;

	};

	typedef Matrix<BOOL> MatrixB;
	typedef Row<BOOL> RowB;


}