#include "Transformation.h"
#include "DNFBuilder.h"
#include "TransformationBuilder.h"

using namespace transformations;
using namespace polynomials;
using namespace std;

void Transformation::operator() (const Transformation& F_inner, Transformation& G_result) const
{

	if (size() != F_inner.size())
		throw exception("For composition transformations must be co-dimensional");

	DNFBuilder pol_builder;
	TransformationBuilder trans_builder;
	const Polynomial* cur_pol;
	const Monomial* cur_mon;
	size_t i1, sz1, i2, sz2, i3, sz3;

	i1 = 0, sz1 = size();
	while (i1 < sz1)
	{
		cur_pol = &operator[](i1++);

		i2 = 0, sz2 = cur_pol->size();
		while (i2 < sz2)
		{
			cur_mon = &cur_pol->operator[](i2++);

			i3 = 0, sz3 = cur_mon->size();
			if (sz3 == 0)
				pol_builder << FREE_MEMBER;
			else
				while (i3 < sz3)
				{
					size_t pol_num = cur_mon->operator[](i3++);
					pol_builder << F_inner[pol_num];
				}

			pol_builder.push();
		}

		Polynomial built;
		pol_builder >> built;
		trans_builder << built;
	}

	trans_builder >> G_result;
}
