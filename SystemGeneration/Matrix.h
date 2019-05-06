#pragma once
#include "Row.h"

namespace matrixes
{

	// ������ ����� ��������� ���������� �������, ��������� �� 0 � 1
	// ����������� �������� ������ Matrix<bool> � Matrix<BOOL>
	template <class _T>
	class Matrix
	{
	private:
		std::vector<Row <_T> *> data;

	public:

		Matrix() : data() { }

		Matrix(Matrix && mat) : data(std::move(mat.data)) {}

		BOOL Init(size_t dimension);


		~Matrix()
		{
			for (size_t i = 0; i < data.size(); i++)
				delete data[i];

			data.clear();
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

		// ���������� ���������� ����� (��� �� ���������� ��������) � �������
		inline size_t size() const
		{
			return data.size();
		}



	};

	typedef Matrix<BOOL> MatrixB;
	typedef Row<BOOL> RowB;


}