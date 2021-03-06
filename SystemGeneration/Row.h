#pragma once
#include <vector>
#include "BOOL.h"

namespace matrixes
{

	// ������ ����� ��������� ������ �������, ��������� �� 0 � 1
	// ����������� �������� ������ Row<bool> � Row<BOOL>

	template <class _T>
	class Row
	{

	private:
		std::vector<_T> elements;
		Row() = delete;

	public:

		Row(int length) : elements(length) {};
		Row(std::vector<_T> v) : elements(v) {};

		void toVector(std::vector<BOOL>& res) const
		{
			int sz = size();
			res = vector<BOOL>(sz);
			for (int i = 0; i < sz; i++)
			{
				res[i] = get(i);
			}
		}
		
		void xor(const Row<_T>& second)
		{
			int sz = size();
			if (sz != second.size())
				throw std::exception("For operation XOR vectors must have same dimension");

			for (int i = 0; i < sz; i++)
			{
				_T res = elements[i] ^ second.get(i);
				elements[i] = res;
			}
		}

		inline void set(int index, _T value)
		{
			elements[index] = value;
		}

		inline _T get(int index) const
		{
			return elements[index];
		}

		inline int size() const
		{
			return (int)elements.size();
		}

		auto begin() const
		{
			return elements.begin();
		}

		auto end() const
		{
			return elements.end();
		}



		void toString(
			std::string& output,
			std::string left_border = "{",
			std::string delimiter = ",",
			std::string right_border = "}") const;

		// ��� �������� ���������� �������
		std::string toString(
			std::string left_border = " {",
			std::string delimiter = ",",
			std::string right_border = "}") const
		{
			std::string s = "";
			toString(s, left_border, delimiter, right_border);
			return s;
		}

	};

}