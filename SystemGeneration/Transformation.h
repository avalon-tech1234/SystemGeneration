#pragma once
#include "Polynomial.h"
#include "Matrix.h"

namespace transformations
{
	class Transformation
	{
	protected:
		// преобразование каждой координаты хранится отдельно как многочлен
		std::vector<polynomials::Polynomial> coordinates;

	public:

		Transformation(std::vector<polynomials::Polynomial>& coordinates)
			: coordinates(coordinates) {}
		Transformation() {}

		inline const polynomials::Polynomial& operator[] (int i) const
		{
			return coordinates[i];
		}

		inline int size() const
		{
			return (int)coordinates.size();
		}

		// вычисление композиции отображений GoF = G(F(x))
		void operator()(const Transformation& F_inner, Transformation& G_result) const;

		void substitute(const std::vector<BOOL>& in, std::vector<BOOL>& out) const;

		void normalize();
		
	};


}

