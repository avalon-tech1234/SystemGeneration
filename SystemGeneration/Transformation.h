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

		Transformation(std::vector<polynomials::Polynomial>& coordinates)
			: coordinates(coordinates) {}
		Transformation() {}

		inline const polynomials::Polynomial& operator[] (size_t i) const
		{
			return coordinates[i];
		}

		inline size_t size() const
		{
			return coordinates.size();
		}

		// ���������� ���������� ����������� GoF = G(F(x))
		void operator()(const Transformation& F_inner, Transformation& G_result) const;
	};


}

