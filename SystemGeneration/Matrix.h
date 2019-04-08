#pragma once
#include <vector>
#include "BOOL.h"
#include <iostream>

// ������ ����� ��������� ������ �������, ��������� �� 0 � 1. ����������� �� vector<BOOL>.
class Row : public std::vector<BOOL>
{
public:

	Row(int length) : std::vector<BOOL>(length, FALSE) {}
	Row() {}

};

// ������ ����� ��������� ���������� �������, ��������� �� 0 � 1. ����������� �� vector<Row>.
class Matrix
{
private:
	std::vector<Row> data;

public:

	Matrix() {}

	// ���������� ���������� ������� dimension*dimension, ����������� ������
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

