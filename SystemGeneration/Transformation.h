#pragma once
#include "Polynomial.h"

namespace transformations
{
	class Transformation
	{
	protected:
		// преобразование каждой координаты хранится отдельно как многочлен
		std::vector<polynomials::Polynomial> coordinates;

	public:

		Transformation(std::vector<polynomials::Polynomial>& coordinates) : coordinates(coordinates) {}
		Transformation() {}
	

	const polynomials::Polynomial& operator[] (size_t i) const
	{
		const std::vector<polynomials::Polynomial>& vect = coordinates;
		return vect[i];
	}

	size_t size() const
	{
		return coordinates.size();
	}

	};

}

