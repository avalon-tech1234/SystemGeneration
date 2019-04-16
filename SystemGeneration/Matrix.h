#pragma once
#include <vector>
#include "BOOL.h"
#include <iostream>

// ƒанный класс описывает строку матрицы, состо€щую из 0 и 1. Ќаследуетс€ от vector<BOOL>.
class Row : public std::vector<BOOL>
{
public:

	Row(size_t length) : std::vector<BOOL>(length, FALSE) {}
	Row() {}

};

// ƒанный класс описывает квадратную матрицу, состо€щую из 0 и 1. Ќаследуетс€ от vector<Row>.
class Matrix
{
private:
	std::vector<Row> data;

public:

	Matrix() {}

	// возвращает квадратную матрицу dimension*dimension, заполненную нул€ми
	Matrix(size_t dimension)
	{
		Row row = Row(dimension);
		data = std::vector<Row>(dimension);
		for (int i = 0; i < dimension; i++)
		{
			data[i] = row;
			if (i % 500 == 0)
				std::cout << i << std::endl;
		}
	}

};

template <class _T>
class Row2 : public std::vector<_T>
{
private:
	Row2() = delete;

public:

	Row2(size_t length) : std::vector<_T>(length) {
		//get_allocator().allocate(0);
		//reserve(length);
	}
};

template <class _T>
class Matrix2
{
	typedef _T t_vattype;
private:

public:
	std::vector<Row2 <_T> *> data;
	~Matrix2()
	{
		for (int i = 0; i < data.size(); i++)
		{
			delete data[i];
		}

		data.clear();
	}

	Matrix2() : data() { }

	Matrix2(Matrix2 && mat) : data(std::move(mat.data))
	{
	}

	// возвращает квадратную матрицу dimension*dimension, заполненную нул€ми
	BOOL Init(size_t dimension)
	{
		data.clear();
		data.reserve(dimension);

		Row2 <t_vattype> * row;
		data = std::vector<Row2 <t_vattype> *>(dimension);

		for (int i = 0; i < dimension; i++)
		{
			try {
				row = new Row2<t_vattype>(dimension);
			}
			catch (const std::exception&) {
				std::cout << "Ooooppps!";
				return FALSE;
			}
			
			//memset((void *)row->data(), 0, sizeof(t_vattype) * row->size()); // size -> capacity
			// в результате работы этой функции получаетс€ пустой Row (какой и был)
			// возможно, это св€зано с тем, что The behaviour of the function is undefined if count is greater than the size of dest (вз€то отсюда https://www.programiz.com/cpp-programming/library-function/cstring/memset)

			data[i] = row; // push_back -> [i]

			if (i % 500 == 0)
				std::cout << i << std::endl;
		}

		return TRUE;
	}

	Row2 <t_vattype>* getRow(size_t n)
	{
		return data[n];
	}

};

template <class _T>
void AllocateArray(_T *** arr, size_t sz) {
	(*arr) = new _T*[sz];
	for (size_t i = 0; i < sz; i++) {
		(*arr)[i] = new _T[sz];
		memset((*arr)[i], 0, sizeof(_T) * sz);
	}
};

template <class _T>
void DestroyArray(_T ** arr, size_t sz) {
	for (size_t i = 0; i < sz; i++) {
		delete[] arr[i];
	}
}

