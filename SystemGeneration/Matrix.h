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

		// ��� ������� ������������ ��� ���������� �������� �������, ����� ������� ������ ���������� 
		BOOL init_zeros(size_t dimension, size_t dimension2);

	public:

		Matrix() : data() { }

		Matrix(Matrix && mat) : data(std::move(mat.data)) {}

		// ������������� ������� ������� ��� dimension*dimension � ��������� � ������
		BOOL init_zeros(size_t dimension)
		{
			return init_zeros(dimension, dimension);
		}

		// �������������� ������� ��� �������, �������� � �������, ���������� � �������� ���������
		// ������������ ����� ������-�������
		// ����������� ������� ������ ����������� ��������
		void initInverse(const Matrix<_T>& matrix);

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

		// ������������ � �������� �����
		void print() const;

	};

	typedef Matrix<BOOL> MatrixB;
	typedef Row<BOOL> RowB;


}