#pragma once
#include "Transformation.h"


namespace transformations
{
	class TransformationBuilder
	{
	private:
		std::vector<polynomials::Polynomial> coords;
		
	public:

		void operator<<(const polynomials::Polynomial& pol)
		{
			coords.push_back(pol);
		}

		void operator>>(Transformation& out)
		{
			out = Transformation(coords);
			coords.clear();
		}

		~TransformationBuilder()
		{
			coords.clear();
			coords.shrink_to_fit();
		}

	};
}

