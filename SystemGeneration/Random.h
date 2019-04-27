#pragma once
#include <random> 

namespace random
{
	class Random
	{
	private:
		std::mt19937 gen; // ������� ��������� �����

	public:

		Random();

		const std::mt19937& getRandomEngine() const;

	};
}


