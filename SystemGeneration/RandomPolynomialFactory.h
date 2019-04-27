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
		void addQuadraticPolynomial(polynomials::Polynomial&, int n);

		RandomPolynomialFactory(const std::mt19937& gen) : gen(gen) {}

	};
}