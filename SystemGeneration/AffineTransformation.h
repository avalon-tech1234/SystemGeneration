#pragma once
#include "Transformation.h"
#include "Matrix.h"
#include "Polynomial.h"

namespace transformations
{
	class AffineTransformation : public Transformation
	{
		// matrixes::MatrixB M; // ������� �������������
		// matrixes::RowB v; // ��������� ����� (� ����� �����)

	public:

		AffineTransformation(const matrixes::MatrixB& M, const matrixes::RowB& v);

		const polynomials::Polynomial& operator[] (int i) const
		{
			const std::vector<polynomials::Polynomial>& vect = coordinates;
			return vect[i];
		}

		int size() const
		{
			return coordinates.size();
		}

	};
}