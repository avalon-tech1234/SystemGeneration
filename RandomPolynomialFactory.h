#pragma once
#include "Polynomial.h"
#include <random> 

namespace random
{
	class RandomPolynomialFactory
	{
	private:
		std::mt19937 gen; // ������� ��������� �����

	public:

		// ���������� � �������� ��������� ������������ �������
		// ��������� ���������� ����������
		void getQuadraticPolynomial(polynomials::Polynomial&, size_t n);

		RandomPolynomialFactory(const std::mt19937& gen) : gen(gen) {}

	};
}