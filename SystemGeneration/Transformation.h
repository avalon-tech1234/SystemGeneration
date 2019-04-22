#pragma once
#include "Polynomial.h"

namespace transformations
{
	class Transformation
	{
	protected:
		// �������������� ������ ���������� �������� �������� ��� ���������
		std::vector<polynomials::Polynomial> coordinates;

	public:

		Transformation(std::vector<polynomials::Polynomial>& coordinates) : coordinates(coordinates) {}
		Transformation() {}
	};
}

