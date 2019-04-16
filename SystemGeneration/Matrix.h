#pragma once
#include <vector>
#include "BOOL.h"
#include <iostream>


// ������ ����� ��������� ������ �������, ��������� �� 0 � 1
template <class _T>
class Row : private std::vector<_T>
{

private:
	Row() = delete;

public:

	Row(size_t length) : std::vector<_T>(length) {};

	_T& element(size_t index)
	{
		return (_T&)operator[](index);
	}

};

// ������ ����� ��������� ���������� �������, ��������� �� 0 � 1
// ����������� �������� ������ Matrix<bool> � Matrix<BOOL>
template <class _T>
class Matrix
{
	typedef _T t_vattype;
private:
	std::vector<Row <_T> *> data;

public:
	~Matrix()
	{
		for (size_t i = 0; i < data.size(); i++)
		{
			delete data[i];
		}

		data.clear();
	}

	Matrix() : data() { }

	Matrix(Matrix && mat) : data(std::move(mat.data)) {}

	BOOL Init(size_t dimension);

	inline Row <t_vattype>* row(size_t n)
	{
		return data[n];
	}

};


