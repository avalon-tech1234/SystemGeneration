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
		Transformation(polynomials::Polynomial& p)
		{
			coordinates = std::vector<polynomials::Polynomial>(1, p);
		}
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
		void initComposition(const Transformation& F_inner, const Transformation& G_outer) ;

		void substitute(const std::vector<BOOL>& in, std::vector<BOOL>& out) const;

		void normalize();
		
	};


}

