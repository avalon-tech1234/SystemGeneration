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

		// ������������� ������� ������� ��� dimension*dimension � ��������� � ������
		BOOL init_zeros(int dimension)
		{
			return init_zeros(dimension, dimension);
		}

		/*
		�������������� ������� ��� �������, �������� � �������, ���������� � �������� ���������
		������������ ����� ������-�������
		����������� ������� �� ����������� (���� �� ��������, �� ������ �����-�� �������)
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

		// ���������� ���������� ����� (��� �� ���������� ��������) � �������
		inline int size() const
		{
			return (int)data.size();
		}

		// ������������ � �������� �����
		void print() const;

	};

	typedef Matrix<BOOL> MatrixB;
	typedef Row<BOOL> RowB;


}