#include "Transformation.h"
#include "DNFBuilder.h"
#include "TransformationBuilder.h"

using namespace transformations;
using namespace polynomials;
using namespace std;

void Transformation::operator() (const Transformation& F_inner, Transformation& G_result) const
{

	// if (size() != F_inner.size()) throw exception("For composition transformations must be co-dimensional");

	DNFBuilder pol_builder;
	TransformationBuilder trans_builder;
	const Polynomial* cur_pol;
	const Monomial* cur_mon;

	int sz1 = size();
	for (int i1 = 0; i1 < sz1; i1++)
	{
		cur_pol = &operator[](i1);

		int sz2 = cur_pol->size();
		for (int i2 = 0; i2 < sz2; i2++)
		{
			cur_mon = &cur_pol->operator[](i2);

			int sz3 = cur_mon->size();
			if (sz3 == 0)
				pol_builder << FREE_MEMBER;
			else
				for (int i3 = 0; i3 < sz3; i3++)
				{
					int pol_num = cur_mon->operator[](i3);
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

void Transformation::substitute(const vector<BOOL>& in, vector<BOOL>& out) const
{
	int n = size();

	out.clear();
	if (in.size() != n) return;

	for (int i = 0; i < n; i++)
	{
		BOOL b = coordinates[i].substitute(in);
		out.push_back(b);
	}
}

void transformations::Transformation::normalize()
{
	int n_core = coordinates.size();


	// z - ����� ����������� � ����������
	int z = 0;
	for (int i = 0; i < n_core; i++)
	{
		if (coordinates[i].get_n_max() > z)
			z = coordinates[i].get_n_max();
	}
	z++;

	for (int i = 0; i < n_core; i++)
	{
		Polynomial Lr;
		auto beg = coordinates[i].begin();
		auto mark = beg; // ��������� �� ��������� ����������� ����� (����� �� �������)

		while
			(mark < coordinates[i].begin() + coordinates[i].size() - 1
				&& !(mark == coordinates[i].begin() + coordinates[i].size() - 2 && *(mark + 1) == FREE_MEMBER)
				&& !coordinates[i].is_standard())
		{
			Lr += *mark;
			Lr += Monomial(z);

			if (Lr.is_standard())
			{
				coordinates.push_back(Lr);
				Lr += Monomial(z);
				int sz = coordinates.size() - 1; // ��� ����������
				for (int j = 0; j < sz; j++)
					coordinates[j].replace(Lr, z);
				z++;

				mark = coordinates[i].begin();
				Lr.clear();
			}
			else
			{
				Lr += Monomial(z);
				mark++;
			}
		}

	}


}

