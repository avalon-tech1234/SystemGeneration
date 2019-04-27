#pragma once
#include "Transformation.h"
#include "Matrix.h"
#include "Polynomial.h"

namespace transformations
{
	class AffineTransformation : public Transformation
	{

	public:

		AffineTransformation(const matrixes::MatrixB& M, const matrixes::RowB& v);


	};
}