#pragma once
#include <vector>
#include "BOOL.h"
#include <iostream>

// Данный класс описывает строку матрицы, состоящую из 0 и 1. Наследуется от vector<BOOL>.
class Row : public std::vector<BOOL>
{
public:

	Row(int length) : std::vector<BOOL>(length, FALSE) {}
	Row() {}

};

// Данный класс описывает квадратную матрицу, состоящую из 0 и 1. Наследуется от vector<Row>.
class Matrix
{
private:
	std::vector<Row> data;

public:

	Matrix() {}

	// возвращает квадратную матрицу dimension*dimension, заполненную нулями
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

